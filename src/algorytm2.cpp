
/**
 * Automatic perspective correction for quadrilateral objects. See the tutorial at
 * http://opencv-code.com/tutorials/automatic-perspective-correction-for-quadrilateral-objects/
 */
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>
using namespace cv;
cv::Point2f center(0,0);

cv::Point2f computeIntersect(cv::Vec4i a,
                             cv::Vec4i b)
{
	int x1 = a[0], y1 = a[1], x2 = a[2], y2 = a[3], x3 = b[0], y3 = b[1], x4 = b[2], y4 = b[3];

	if (float d = ((float)(x1 - x2) * (y3 - y4)) - ((y1 - y2) * (x3 - x4)))
	{
		cv::Point2f pt;
		pt.x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
		pt.y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;
		return pt;
	}
	else
		return cv::Point2f(-1, -1);
}

double angle( cv::Point pt1, cv::Point pt2, cv::Point pt0 ) {
    double dx1 = pt1.x - pt0.x;
    double dy1 = pt1.y - pt0.y;
    double dx2 = pt2.x - pt0.x;
    double dy2 = pt2.y - pt0.y;
    return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
}

void find_squares(Mat& image, vector<vector<Point> >& squares)
{
    // blur will enhance edge detection
    Mat blurred(image);
    medianBlur(image, blurred,15);

    Mat gray0(blurred.size(), CV_8U), gray;
    vector<vector<Point> > contours;

    // find squares in every color plane of the image
    for (unsigned c = 0; c < 3; c++)
    {
        int ch[] = {c, 0};
        mixChannels(&blurred, 1, &gray0, 1, ch, 1);

        // try several threshold levels
        const int threshold_level = 10;//2;
        for (int l = 0; l < threshold_level; l++)
        {
            // Use Canny instead of zero threshold level!
            // Canny helps to catch squares with gradient shading
            if (l == 0)
            {
                Canny(gray0, gray, 100, 100, 3); //

                // Dilate helps to remove potential holes between edge segments
                dilate(gray, gray, Mat(), Point(-1,-1));
            }
            else
            {
                    gray = gray0 >= (l+1) * 255 / threshold_level;
            }

            // Find contours and store them in a list
            findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);

            // Test contours
            vector<Point> approx;
            for (size_t i = 0; i < contours.size(); i++)
            {
                    // approximate contour with accuracy proportional
                    // to the contour perimeter
                    approxPolyDP(Mat(contours[i]), approx, arcLength(Mat(contours[i]), true)*0.02, true);

                    // Note: absolute value of an area is used because
                    // area may be positive or negative - in accordance with the
                    // contour orientation
                    if (approx.size() == 4 &&
                            fabs(contourArea(Mat(approx))) > 1000 &&
                            isContourConvex(Mat(approx)))
                    {
                            double maxCosine = 0;

                            for (int j = 2; j < 5; j++)
                            {
                                    double cosine = fabs(angle(approx[j%4], approx[j-2], approx[j-1]));
                                    maxCosine = MAX(maxCosine, cosine);
                            }

                            if (maxCosine < 0.3)
                                    squares.push_back(approx);
                    }
            }
        }
    }
}

void sortCorners(std::vector<cv::Point2f>& corners,
                 cv::Point2f center)
{
	std::vector<cv::Point2f> top, bot;

	for (unsigned i = 0; i < corners.size(); i++)
	{
		if (corners[i].y < center.y)
			top.push_back(corners[i]);
		else
			bot.push_back(corners[i]);
	}

	cv::Point2f tl = top[0].x > top[1].x ? top[1] : top[0];
	cv::Point2f tr = top[0].x > top[1].x ? top[0] : top[1];
	cv::Point2f bl = bot[0].x > bot[1].x ? bot[1] : bot[0];
	cv::Point2f br = bot[0].x > bot[1].x ? bot[0] : bot[1];

	corners.clear();
	corners.push_back(tl);
	corners.push_back(tr);
	corners.push_back(br);
	corners.push_back(bl);
}

cv::Mat debugSquares( std::vector<std::vector<cv::Point> > squares, cv::Mat image )
{
    for ( unsigned i = 0; i< squares.size(); i++ ) {
        // draw contour
        cv::drawContours(image, squares, i, cv::Scalar(255,0,0), 1, 8, std::vector<cv::Vec4i>(), 0, cv::Point());

        // draw bounding rect
        cv::Rect rect = boundingRect(cv::Mat(squares[i]));
        cv::rectangle(image, rect.tl(), rect.br(), cv::Scalar(0,255,0), 2, 8, 0);

        // draw rotated rect
        cv::RotatedRect minRect = minAreaRect(cv::Mat(squares[i]));
        cv::Point2f rect_points[4];
        minRect.points( rect_points );
        for ( int j = 0; j < 4; j++ ) {
            cv::line( image, rect_points[j], rect_points[(j+1)%4], cv::Scalar(0,0,255), 1, 8 ); // blue
        }
    }

    return image;
}

void open_img(Mat src, Mat &dst, Mat element, Point point = Point(-1,1), int iterations = 1 ){
	erode(src, dst, element, point, iterations);
	dilate(dst, dst, element, point, iterations);
}

void close_img(Mat src, Mat &dst, Mat element, Point point = Point(-1,1), int iterations = 1 ){
	dilate(src, dst, element, point, iterations);
	erode(dst, dst, element, point, iterations);
}

void white_top_hat(Mat src, Mat &dst, Mat element ){
	open_img(src, dst, element);
	dst = src - dst;
}

void black_top_hat(Mat src, Mat &dst, Mat element ){

	close_img(src, dst, element);
	dst = dst - src;
}




Mat horizontal(int size){
	Mat src = Mat::ones(size, size, CV_8U);

	for(int i = 0; i < src.rows; i++)
	{
		for(int j = 0; j < src.cols; j++)
		{
			if ((i < (src.rows * 0.2f )) || (i > (src.rows * 0.8f ))) {
				src.at<char>(i,j) = 0;
			}
		}
	}
	std::cout << src;
	return src;
}

int distance(Point p1, Point p2){
	return sqrt(((p1.x - p2.x) * (p1.x - p2.x))+((p1.y - p2.y)*(p1.y - p2.y)));
}

bool has_similar_length(Point p1, Point p2, Point p3, Point p4, float precision = 0.15f ) {
	int l1_length = distance(p1, p3);
	int l2_length = distance(p2, p4);
	float length_avg = ( l1_length + l2_length ) / 2.0f;
	if (abs(l1_length - l2_length) < round(precision * length_avg) ) {
		return true;
	} else {
		return false;
	}
}





std::vector<cv::Vec4i> find_candidates(std::vector<cv::Vec4i> lines, Mat &src, float precision = 0.15f) {
	std::vector<cv::Vec4i> results;
	for (unsigned i = 0; i < lines.size(); i++)
	{
		for (unsigned j = 0; j < lines.size(); j++) {
			if (i!=j) {
				cv::Vec4i l1 = lines[i];  //main lines
				cv::Vec4i l2 = lines[j];
				Point p1 = cv::Point(l1[0], l1[1]);
				Point p2 = cv::Point(l1[2], l1[3]);
				Point p3 = cv::Point(l2[0], l2[1]);
				Point p4 = cv::Point(l2[2], l2[3]);


				if (has_similar_length(p1, p2, p3, p4, precision)) {  //lines are similar
					//Czy kt�tsze boki s� podobne
					bool is_similar_to_rectangle = false;
					float avg_long_dist = (distance(p1, p2) + distance(p3,p4) /1.0f);
					float avg_short_dist = 1.0f;
					bool first = false;
					if ((distance(p1,p3) + distance(p2, p4)) < (distance(p1,p4) + distance(p2, p3) )) {
						is_similar_to_rectangle = has_similar_length(p1, p3, p2, p4, precision);
						avg_short_dist = (distance(p1, p3) + distance(p2,p4) /2.0f);
						first = true;
					} else {
						is_similar_to_rectangle = has_similar_length(p1, p4, p2, p3, precision);
						avg_short_dist = (distance(p1, p4) + distance(p2,p3) /2.0f);
						first = false;
					}
					if (avg_long_dist > avg_short_dist) {
						//printf("=------=\n");
						//printf("short : %f \n", avg_short_dist );
						//printf("long : %f \n", avg_long_dist );

						//cv::line(src, cv::Point(l1[0], l1[1]), cv::Point(l1[2], l1[3]), CV_RGB(255,0,0));
						//cv::line(src, cv::Point(l2[0], l2[1]), cv::Point(l2[2], l2[3]), CV_RGB(255,0,0));
						//namedWindow( "debug", CV_WINDOW_AUTOSIZE );
						//imshow( "debug",src );
						//cv::waitKey();

					}

					if ((is_similar_to_rectangle) && (fabs((avg_long_dist / avg_short_dist) - 5.0) < 1.0f/*2.0f*/)) {
						results.push_back(l1);
						results.push_back(l2);
						if (first) {
							results.push_back(Vec4i(p1.x,p1.y,p3.x, p3.y));
							results.push_back(Vec4i(p2.x,p2.y,p4.x, p4.y));
						}	else {
							results.push_back(Vec4i(p1.x,p1.y,p4.x, p4.y));
							results.push_back(Vec4i(p2.x,p2.y,p3.x, p3.y));
						}

					}
				}
			}
		}
	}

	return results;
}

int temp(char** argv)//main( int argc, char** argv )
{
	cv::Mat src = cv::imread(argv[1]);
    cv::Mat test1;
    cv::Mat test2;
    cv::Mat light;
	if (src.empty())
		return -1;



	cv::resize( src, src, Size(700.0, 500.0)) ;
	//std::vector<std::vector<cv::Point> > squares;
	cv::Mat bw;

	cv::cvtColor(src, bw, CV_BGR2GRAY);

	/*namedWindow( "SIMPLE-1", CV_WINDOW_AUTOSIZE );
    imshow( "SIMPLE-1",bw );


	medianBlur(bw, light,161);

	namedWindow( "bw", CV_WINDOW_AUTOSIZE );
		imshow( "bw",bw );

	bw = bw - light;

	namedWindow( "bwlight-1", CV_WINDOW_AUTOSIZE );
	imshow( "bwlight-1",bw );
	norm(bw,bw);
	//equalizeHist( bw, bw );
	medianBlur(bw, bw,3);
	namedWindow( "bwhist-2", CV_WINDOW_AUTOSIZE );
	imshow( "bwhist-2",bw );
	namedWindow( "light", CV_WINDOW_AUTOSIZE );
	imshow( "light",light );

*/
	//equalizeHist( bw, bw );
	/*namedWindow( "gray", CV_WINDOW_AUTOSIZE );
	imshow( "gray",bw );
	equalizeHist( bw, bw );
	namedWindow( "light", CV_WINDOW_AUTOSIZE );
	imshow( "light",bw );*/
/*
	bw = bw - light;
	namedWindow( "after", CV_WINDOW_AUTOSIZE );
	imshow( "after",bw );
*/

	close_img(bw, bw, horizontal(3), Point(-1,1), 3 );     //GOOD
	open_img(bw, bw, horizontal(3), Point(-1,1), 3 );  //GOOD
	//close_img(bw, bw, Mat::ones(2,10,CV_8U), Point(-1,1), 3 );
	//open_img(bw, bw, Mat::ones(2,10,CV_8U) , Point(-1,1), 3 );


	//std::cout << Mat::ones(2,2, CV_8U);
	namedWindow( "OPEN", CV_WINDOW_AUTOSIZE );
    imshow( "OPEN",bw );

	cv::blur(bw, bw, cv::Size(3, 3));
	equalizeHist( bw, bw );
	cv::blur(bw, bw, cv::Size(3, 3));
	cv::Canny(bw, bw, 50, 200, 3, true);
	//dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1),  1 );
	//dilate(bw, test1, horizontal(5), Point(-1,1),  2 );
	//close_img(bw, bw, horizontal(5), Point(-1,1), 2 );
	//dilate(bw, bw, Mat::ones(2, 3, CV_8U), Point(-1,1), 3 );  //ADDED
	//erode(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1),  2 );
	//namedWindow( "dilate", CV_WINDOW_AUTOSIZE );
	//imshow( "dilate",test1 );

	std::vector<cv::Vec4i> lines;
	std::vector<cv::Vec4i> candidates;
    cv::HoughLinesP(bw, lines, 1, CV_PI/180, 40, 40, 20);//CV_PI/180

    for (unsigned i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		cv::line(src, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(0,255,0));
	}

    candidates = find_candidates(lines, src, 0.2f);  //BEFORE GOOD CONF. 0.5f
    for (unsigned i = 0; i < candidates.size(); i++)
	{
		cv::Vec4i v = candidates[i];
		cv::line(src, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(255,0,0));
	}
    printf("\n LINES: %d", lines.size());
    printf("\nCANDIDATES %d\n", candidates.size());

	namedWindow( "close", CV_WINDOW_AUTOSIZE );
	imshow( "close",bw );

	namedWindow( "cannyTRUE", CV_WINDOW_AUTOSIZE );
    imshow( "cannyTRUE",src );
	cv::waitKey();
	return 0;


	namedWindow( "cannyTRUE", CV_WINDOW_AUTOSIZE );
	imshow( "cannyTRUE",bw );

	//Sobel( bw, bw, bw.depth(), 0, 1, 9);



//	namedWindow( "cannyTRUE", CV_WINDOW_AUTOSIZE );
//	imshow( "cannyTRUE",bw );


	cv::waitKey();
	return 0;
	//std::vector<cv::Vec4i> lines;
	//cv::HoughLinesP(bw, lines, 1, CV_PI/180, 50, 100, 10);

	// Expand the lines
	/*for (int i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		lines[i][0] = 0;
		lines[i][1] = ((float)v[1] - v[3]) / (v[0] - v[2]) * -v[0] + v[1];
		lines[i][2] = src.cols;
		lines[i][3] = ((float)v[1] - v[3]) / (v[0] - v[2]) * (src.cols - v[2]) + v[3];
	}*/

	std::vector<cv::Point2f> corners;
	for (unsigned i = 0; i < lines.size(); i++)
	{
		for (unsigned j = i+1; j < lines.size(); j++)
		{
			cv::Point2f pt = computeIntersect(lines[i], lines[j]);
			if (pt.x >= 0 && pt.y >= 0)
				corners.push_back(pt);
		}
	}

	std::vector<cv::Point2f> approx;
	cv::approxPolyDP(cv::Mat(corners), approx, cv::arcLength(cv::Mat(corners), true) * 0.02, true);

/*	if (approx.size() != 4)
	{
		std::cout << "The object is not quadrilateral!" << std::endl;
		return -1;
	}*/

	// Get mass center
	for (unsigned i = 0; i < corners.size(); i++)
		center += corners[i];
	center *= (1. / corners.size());

	sortCorners(corners, center);

	cv::Mat dst = src.clone();

	// Draw lines
	for (unsigned i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		cv::line(dst, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(0,255,0));
	}

	// Draw corner points
	cv::circle(dst, corners[0], 3, CV_RGB(255,0,0), 2);
	cv::circle(dst, corners[1], 3, CV_RGB(0,255,0), 2);
	cv::circle(dst, corners[2], 3, CV_RGB(0,0,255), 2);
	cv::circle(dst, corners[3], 3, CV_RGB(255,255,255), 2);

	// Draw mass center
	cv::circle(dst, center, 3, CV_RGB(255,255,0), 2);

	cv::Mat quad = cv::Mat::zeros(300, 220, CV_8UC3);

	std::vector<cv::Point2f> quad_pts;
	quad_pts.push_back(cv::Point2f(0, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, 0));
	quad_pts.push_back(cv::Point2f(quad.cols, quad.rows));
	quad_pts.push_back(cv::Point2f(0, quad.rows));

	cv::Mat transmtx = cv::getPerspectiveTransform(corners, quad_pts);
	cv::warpPerspective(src, quad, transmtx, quad.size());

	cv::imshow("image", dst);
	cv::imshow("quadrilateral", quad);
	cv::waitKey();
	return 0;
}
