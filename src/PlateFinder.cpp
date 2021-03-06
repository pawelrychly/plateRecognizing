/*
 * PlateFinder.cpp
 *
 *  Created on: 15-08-2013
 *      Author: Pawe�
 */

#include "PlateFinder.h"

//using namespace tesseract;

PlateFinder::PlateFinder(string file_name) {
	this->src = cv::imread(file_name);
}

PlateFinder::~PlateFinder() {
	// TODO Auto-generated destructor stub
}

void PlateFinder::removeDarkBlue(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(130, 110 , 0), cv::Scalar(255, 150,100), mask);
	bitwise_or(res, mask, res);
	//bitwise_not(mask,mask);
	//src.copyTo(res, mask);
}

void PlateFinder::removeBlue(Mat src, Mat &res){
	Mat mask;

	inRange(src, cv::Scalar(130, 70 , 0), cv::Scalar(255, 110,75), mask);
	//bitwise_not(mask,mask);
	//src.copyTo(res, mask);

	bitwise_or(res, mask, res);
	//res = mask.clone();
	/*
	vector<vector<Point> > contours;
			vector<Vec4i> hierarchy;

			//namedWindow( "a3", CV_WINDOW_AUTOSIZE );
			//imshow( "a3",bw );
			findContours( bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
			//cv::cvtColor(bw, bw, CV_GRAY2BGR);

			std::vector<RotatedRect> founded;
			Mat new_bw = Mat::zeros(bw.size(), CV_8U);
			cv::cvtColor(new_bw, new_bw, CV_GRAY2BGR);
			vector<RotatedRect> minRect( contours.size() );
			std::cout<< contours.size() << std::endl;
			for( unsigned j = 0; j< contours.size(); j++ )
			{
			   std::vector<Point> rectangle(4);
			   minRect[j] = minAreaRect( Mat(contours[j]) );
			   Point2f rect_points[4];
			   minRect[j].points( rect_points );
			   float width = minRect[j].size.width > minRect[j].size.height ? minRect[j].size.width : minRect[j].size.height;
			   float height = minRect[j].size.width > minRect[j].size.height ? minRect[j].size.height : minRect[j].size.width;



			   if ((width > (bw.cols * 0.3f)) && (height > (bw.rows * 0.3f) ) && is_rectangle_in_mat(minRect[j], bw)) {
				   founded.push_back(minRect[j]);
			   }
			   			//drawContours( new_bw, contours, i, CV_RGB(100,180,180), 2, 8, hierarchy, 0, Point() );
			}*/
}


std::vector<Mat> PlateFinder::find_plates(){
	std::vector<Mat> candidatesMat;
	std::vector<RotatedRect> candidates;
	cv::Mat test1;
	cv::Mat test2;
	cv::Mat light;
	cv::Mat src_with_candidates = src.clone();
	if (src.empty())
		return candidatesMat;
	//Size size = Size(700.0, 500.0);
/*	if ((src.rows > 700)) {
		cv::resize( src, src, Size(0,0), 0.5, 0.5) ;
	}*/
	cv::Mat bw;
	cv::cvtColor(src, bw, CV_BGR2GRAY);
	//cv::blur(bw, bw, cv::Size(2, 2));
	//equalizeHist( bw, bw );
	//cv::blur(bw, bw, cv::Size(3, 3));


	/*
	medianBlur(bw, light, 161);

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
	//dilate(bw, bw, Mat::ones(2, 10, CV_8U), Point(-1,1), 2);

	//namedWindow( "eroded", CV_WINDOW_AUTOSIZE );
	//		imshow( "eroded",bw );
/*	close_img(bw, bw, horizontal(3), Point(-1,1), 3 );     //GOOD
	open_img(bw, bw, horizontal(3), Point(-1,1), 3 );  //GOOD
*/

	//close_img(bw, bw, Mat::ones(2,10,CV_8U), Point(-1,1), 3 );
	//open_img(bw, bw, Mat::ones(2,10,CV_8U) , Point(-1,1), 3 );



	//std::cout << Mat::ones(2,2, CV_8U);

	//cv::Canny(bw, bw, 50, 200, 3, true);

	int scale = 1;
	int delta = 0;
	int ddepth = CV_8U;

	//cv::blur(bw, bw, cv::Size(2,2));
	cv::Sobel( bw, bw, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );

	//cv::Sobel( bw, bw, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
	cv::blur(bw, bw, cv::Size(40,4));
	dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 5);
	equalizeHist( bw, bw );
	////namedWindow( "canny", CV_WINDOW_AUTOSIZE );
	////	imshow( "canny",bw );
	threshold(bw, bw, 220, 255, THRESH_BINARY);
	//cv::blur(bw, bw, cv::Size(3,3));

	//close_img(bw, bw, Mat::ones(2,10, CV_8U), Point(-1,1), 2 );
/*
	 int scale = 1;
	 int delta = 0;
	 int ddepth = CV_8U;

	    /// Gradient X
	 cv::Canny(bw, bw, 50, 200, 3, true);
	 cv::Sobel( bw, bw, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
	 dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 2);
	 erode(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 1);
*/
	//cv::Canny(bw, bw, 50, 200, 3, true);


	//close_img(bw, bw, Mat::ones(2,10, CV_8U), Point(-1,1), 2 );     //GOOD

	//open_img(bw, bw, Mat::ones(2,2, CV_8U), Point(-1,1), 1 );  //GOOD
	//medianBlur(bw, bw, 3);
	//dilate(bw, bw, Mat::ones(2, 5, CV_8U), Point(-1,1), 2);
	//cv::Canny(bw, bw, 50, 200, 3, true);
	//close_img(bw, bw, horizontal(9), Point(-1,1), 5 );
	//dilate(bw, bw, Mat::ones(2, 5, CV_8U), Point(-1,1), 2);
	//open_img(bw, bw, horizontal(3), Point(-1,1), 5 );
    //open_img(bw, bw, horizontal(9), Point(-1,1), 1 );
	//erode(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 1);
	//dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 3);
	//dilate(bw, bw, Mat::ones(2, 20, CV_8U), Point(-1,1), 1);
	////namedWindow( "closed", CV_WINDOW_AUTOSIZE );
	////imshow( "closed",bw );
	//medianBlur(bw, bw, 3);
	//open_img(bw, bw, horizontal(5), Point(-1,1), 3 );
	//close_img(bw, bw, Mat::ones(4, 2, CV_8U), Point(-1,1), 1 );     //GOOD
	//open_img(bw, bw, Mat::ones(4, 2, CV_8U), Point(-1,1), 2 );  //GOOD
	//medianBlur(bw, bw, 3);
	//cv::Sobel( bw, bw, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );
	//close_img(bw, bw, Mat::ones(2, 10, CV_8U), Point(-1,1), 1 );
	//medianBlur(bw, bw, 9);
	//close_img(bw, bw, Mat::ones(2, 4, CV_8U), Point(-1,1), 20);
	//open_img(bw, bw, Mat::ones(2, 4, CV_8U), Point(-1,1), 10 );
	//close_img(bw, bw, Mat::ones(2, 4, CV_8U), Point(-1,1), 10 );     //GOOD
	//    open_img(bw, bw, Mat::ones(8, 3, CV_8U), Point(-1,1), 1 );  //GOOD

	//cv::Sobel( bw, bw, ddepth, 0, 1, 3, scale, delta, cv::BORDER_DEFAULT );

	//POPRAWNE!!!
	//open_img(bw, bw, Mat::ones(2, 10, CV_8U), Point(-1,1), 5 );
	//close_img(bw, bw, Mat::ones(2, 10, CV_8U), Point(-1,1), 5 );

	//TESTOWE
	open_img(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 5 );
	close_img(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 5 );

	cv::Canny(bw, bw, 50, 200, 3, true);
	//dilate(bw, bw, Mat::ones(4, 4, CV_8U), Point(-1,1),2);



	//dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 2);

	//medianBlur(bw, bw, 3);



	/*int i = 1;
	while (i < 10) {
		dilate(bw, bw, Mat::ones(2, 4, CV_8U), Point(-1,1),  1 );

		namedWindow( "cannyTRUE", CV_WINDOW_AUTOSIZE );
		imshow( "cannyTRUE",bw );
		cv::waitKey();
		i++;
	}*/
	std::vector<cv::Vec4i> lines;


	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	  /// Detect edges using canny
	  /// Find contours

	findContours( bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	cv::cvtColor(bw, bw, CV_GRAY2BGR);
	vector<RotatedRect> minRect( contours.size() );

	std::cout << "Cont: " << contours.size() << std::endl;
	for( unsigned i = 0; i< contours.size(); i++ )
	{
	   std::vector<Point> rectangle(4);
	   minRect[i] = minAreaRect( Mat(contours[i]) );
	   Point2f rect_points[4];
	   minRect[i].points( rect_points );

	   for (int k = 0; k < 4; k++) {
		   rectangle[k] = rect_points[k];
	   }
	   float area_of_contour = contourArea(contours[i]);
	   float area_of_rect = contourArea(rectangle);
	   bool is_horizontal = true;
	   if (is_horizontal_rectangle(minRect[i]) == false) {
		   is_horizontal = false;
	   }

	   float regular = area_of_rect / area_of_contour;
	   if (((minRect[i].size.width > 50) || (minRect[i].size.height > 50)) && (regular <=1.6f) ) {



		   //drawing rect
		   Size size = minRect[i].size;
		   std::stringstream stream;
		   stream << regular << std::endl ;

		   putText(bw, stream.str(), Point(rect_points[0].x, rect_points[0].y+30), FONT_HERSHEY_SIMPLEX , 0.4f, CV_RGB(255,0,0));
		   //std::cout << stream.str() << std::endl;
		   if (check_proportions(size.width, size.height, 2.0f)) {
			   RotatedRect new_rect = minRect[i];
			   new_rect.center = Point2f(minRect[i].center.x, minRect[i].center.y - 10);
			   new_rect.size = Size2f(minRect[i].size.width * 1.5f, minRect[i].size.height * 1.5f);
			   if (!is_subarea_of_another_candidate(candidates, new_rect)) {


				   new_rect.points( rect_points );

				   candidates.push_back(new_rect);
				   for( int j = 0; j < 4; j++ )
				   {
					   if (is_horizontal==true){
						   line( src_with_candidates, rect_points[j], rect_points[(j+1)%4],  CV_RGB(255,0,0), 1, 8 );
					   }
				   }
			   }

		   } /*else {
			   for( int j = 0; j < 4; j++ ) {
				   if (is_horizontal == true) {
					   line( src, rect_points[j], rect_points[(j+1)%4],  CV_RGB(0,0,255), 1, 8 );
				   } else {
					   line( src, rect_points[j], rect_points[(j+1)%4],  CV_RGB(255,255,0), 1, 8 );
				   }
			   }
		   }*/
		   //drawContours( bw, contours, i, CV_RGB(255,255,255), 2, 8, hierarchy, 0, Point() );



	   }
	}

	for (unsigned i = 0; i < candidates.size(); i++) {
		candidatesMat.push_back(get_subimage(candidates[i], src));
	}

	namedWindow( "candidates", CV_WINDOW_AUTOSIZE );
	imshow( "candidates",src );

	//std::cout << candidatesMat.size();
	candidatesMat = filter_candidates(candidatesMat);

	for (unsigned i = 0; i < candidatesMat.size(); i++) {
		Mat bw = candidatesMat[i].clone();

		Mat result = Mat::zeros(bw.size(), CV_8U);
		removeBlue(bw, result);
		//namedWindow( "blue", CV_WINDOW_AUTOSIZE );
		//imshow( "blue", result );
		removeDarkBlue(bw, result);
		//open_img(result, result, Mat::ones(2, 10, CV_8U), Point(-1,1), 5 );
		medianBlur(result, result, 9);
		//std::cout<< "Size: " << result.size() << ", " << result.rows << ", " << result.cols << std::endl;
		dilate(result, result, Mat::ones( 3, 3, CV_8U), Point(-1,1), 3);
		/*
		Mat nowa = Mat::zeros(5,5, CV_8U);
		nowa.at<unsigned char>(3,1)  = 255;
		std::cout<< nowa << std::endl;
		std::cout<<nowa.cols;
		std::cout<<nowa.rows;

		namedWindow( "nowa", CV_WINDOW_AUTOSIZE );
		imshow( "nowa", nowa );
		cv::waitKey();
		*/
		//result.at<unsigned char>(50, 50) = 128;
		//for (int b = 0; b < result.rows; b++) {

		//			}

		for(int a = 0; a < result.cols; a++)
		{

			int b = 0;
			int index = 0;
			while ((b < result.rows) && (index < result.rows /10)) {
				if (result.at<unsigned char>(b,a) > 0) {
					//std::cout << (int) result.at<unsigned char>(b,a) << ";";
					index++;
				}
				b++;
			}
			if (index >= result.rows /10) {

				for (int c = 0; c < result.rows; c++) {

					result.at<unsigned char>(c,a) = 255;
				}
			}
		}

		//dilate(result, result, Mat::ones( result.size().height, 3, CV_8U), Point(-1,1), 3);
		//close_img(result, result, Mat::ones(4, 3, CV_8U), Point(-1,1), 5 );
		//cv::blur(result, result, cv::Size(70, 5));

		namedWindow( "blue", CV_WINDOW_AUTOSIZE );
		imshow( "blue", result );
		//removeDarkBlue(bw, bw);
		//namedWindow( "darkblue", CV_WINDOW_AUTOSIZE );
		//imshow( "darkblue", result2   );
		cv::cvtColor(bw, bw, CV_BGR2GRAY);

		/*namedWindow( "1 ", CV_WINDOW_AUTOSIZE );
		imshow( "1 ", bw );
		cv::blur(bw, light, cv::Size(70, 1));
		bw = 2.0 *bw;

		namedWindow( "2 ", CV_WINDOW_AUTOSIZE );
		imshow( "2 ", bw );

		erode(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1),1);
		medianBlur(bw, bw, 3);
		//equalizeHist( bw, bw );
		//threshold(bw, bw, 235, 255, THRESH_BINARY);
		//open_img(bw, bw, Mat::ones(4,2,CV_8U), Point(-1,1), 1 );
		//cv::Canny(bw, bw, 10, 250, 3, true);
		equalizeHist( bw, bw );
*/


//#TRESH DATA
		bw = thresh_plate(bw);
		bw = remove_frame(bw);
		remove_small_object(bw);
		namedWindow( "filter", CV_WINDOW_AUTOSIZE );
		imshow( "filter", bw );
		/*for(int a = 0; a < bw.cols; a++)
		{
			for (int b=0; b < bw.rows; b++) {
				result.at<unsigned char>(b,a) = 255;
			}
		}*/
//##

		//threshold(bw, bw, 235, 255, THRESH_BINARY);
		//bitwise_or(bw, result, bw);
		//cv::Sobel( bw, bw, ddepth, 1, 0, 3, scale, delta, cv::BORDER_DEFAULT );
		//bw = remove_blue_element(bw);
		//namedWindow( "new1", CV_WINDOW_AUTOSIZE );
		//imshow( "new1", bw );
		//
		/* OCR
        TessBaseAPI *myOCR = new TessBaseAPI();

		if (myOCR->Init(NULL, "eng")) {
			printf("Could not initialize tesseract.\n");
			exit(1);
		}

		myOCR->SetVariable( "tessedit_char_whitelist", "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" );
		myOCR->TesseractRect(bw.data,1,bw.step1(),0,0,bw.cols,bw.rows);
		const char * text1=myOCR->GetUTF8Text();

		string t1(text1);
		printf("Text:\n");
		printf("%s",t1.c_str());

		delete myOCR;
         
         */

		//imshow( "can", candidatesMat[i] );
		cv::waitKey();
	}
	return candidatesMat;
	//cv::HoughLinesP(bw, lines, 1, CV_PI/180, 40, 40, 10);//CV_PI/180


/*	Mat new_bw = Mat::zeros(bw.size(), CV_8U);
	for (unsigned i = 0; i < lines.size(); i++)
	{
			cv::Vec4i v = lines[i];
			cv::line(new_bw, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), 255, 1);
	}
	//dilate(new_bw, new_bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 2);
	dilate(new_bw, new_bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 1);
	lines.clear();

	namedWindow( "new_bw", CV_WINDOW_AUTOSIZE );
		imshow( "new_bw",new_bw );


	cv::HoughLinesP(new_bw, lines, 1, CV_PI/180, 50, 40, 10);//CV_PI/180
*/
/*
	for (unsigned i = 0; i < lines.size(); i++)
	{
		cv::Vec4i v = lines[i];
		cv::line(bw, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(0,255,0));
	}
	candidates = find_candidates(lines, src, 0.1f);  //BEFORE GOOD CONF. 0.5f
	for (unsigned i = 0; i < candidates.size(); i++)
	{
		cv::Vec4i v = candidates[i];
		cv::line(bw, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]), CV_RGB(255,0,0));
	}
	printf("\n LINES: %d", lines.size());
	printf("\nCANDIDATES %d\n", candidates.size());
	namedWindow( "candidates", CV_WINDOW_AUTOSIZE );
	imshow( "candidates",bw );
	cv::waitKey();
	//Sobel( bw, bw, bw.depth(), 0, 1, 9);
//	namedWindow( "cannyTRUE", CV_WINDOW_AUTOSIZE );
//	imshow( "cannyTRUE",bw );
	return candidates;*/
}

void PlateFinder::remove_small_object(Mat &src) {
	 Mat src_temp = src.clone();
	 int area = src.rows * src.cols;
	 vector<vector<Point> > contours;
	 vector<vector<Point> > result_contours;
	 vector<Vec4i> hierarchy;
	 findContours( src_temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

	  //vector<vector<Point> > contours_poly( contours.size() );
	  vector<Rect> boundRect( contours.size() );
	  vector<float>radius( contours.size() );

	  for(unsigned int i = 0; i < contours.size(); i++ )
	  {
		  boundRect[i] = boundingRect( Mat(contours[i]) );
		  double object_area = boundRect[i].height * boundRect[i].width;
		  if (object_area < (0.01 * area)) {
			  result_contours.push_back(contours[i]);
		  }
		  /*approxPolyDP( Mat(contours[i]), contours_poly[i], 3, true );
		  double area0 = contourArea(contour);
		  //  boundRect[i] = boundingRect( Mat(contours_poly[i]) );

		   */
	  }

	  /// Draw polygonal contour + bonding rects + circles
	  //Mat drawing = Mat::zeros( src.size(), CV_8U);
	  for( unsigned int i = 0; i<  result_contours.size(); i++ )
	  {
	      drawContours( src,  result_contours, i, 255, CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
	      //rectangle( drawing, boundRect[i].tl(), boundRect[i].br(), 255, 2, 8, 0 );
	  }

	  //bitwise_or(src, drawing, src);


}

Mat PlateFinder::thresh_plate(Mat src) {
	double size = (double) src.cols * (double) src.rows;
	double sum = 0;
	for(int a = 0; a < src.cols; a++)
	{
		for (int b=0; b < src.rows; b++) {
			sum = sum + (double) src.at<unsigned char>(b,a);
		}
	}
	double avg = sum / size;
	std::cout <<"avg: ";
	std::cout << avg << std::endl;
	int thresh = (int)avg;
	//int thresh = 150 + ((avg/255.0) * 105);
	std::cout <<"thresh: ";
	std::cout << thresh << std::endl;
	threshold(src, src, thresh, 255, THRESH_BINARY);
	namedWindow( "before close", CV_WINDOW_AUTOSIZE );

/*
	namedWindow( "after thresh", CV_WINDOW_AUTOSIZE );
	imshow( "after thresh", src );*/
	return src;
}


void PlateFinder::remove_neighborhood(Mat &src, int x, int y) {
	int right_x = src.cols * 19/20.0;
	int left_x = src.cols * 1/10.0;
	int top_y = src.rows * 1/10.0;
	int bottom_y = src.rows * 8/10.0;

	if ((src.at<unsigned char>(y,x) == 0) &&
		((x > right_x) || ( x < left_x ) ||
			(y > bottom_y) || (y < top_y)))
		{
		src.at<unsigned char>(y,x) = 255;
		if (x > 0) {
			remove_neighborhood(src, x-1, y);
		}
		if (x < (src.cols -1)) {
			remove_neighborhood(src, x+1, y);
		}
		if (y > 0) {
			remove_neighborhood(src, x, y-1);
		}
		if (y < (src.rows -1)) {
			remove_neighborhood(src, x, y+1);
		}
	}
	return;
}
/*
void PlateFinder::mark_possible_ends_of_frame(Mat &src) {
	int y = 0;
	//int x = 0;
	//detect top line

	Mat copy_of_src = src.clone();
	//dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 2);
	//erode(copy_of_src, copy_of_src, Mat::ones(5, 9, CV_8U), Point(-1,1), 1);
	//close_img(copy_of_src, copy_of_src, Mat::ones(9,9,CV_8U), Point(-1,1), 1 );
	namedWindow( "copy", CV_WINDOW_AUTOSIZE );
	imshow( "copy", copy_of_src );


	bool found = false;
	int num_of_changes = 0;
	unsigned char prev_init = src.at<unsigned char>(0,0);
	unsigned char prev = prev_init;
	while ((!found) && (y < src.rows)) {
		num_of_changes = 0;
		for(int a = 0; a< copy_of_src.cols; a++) {
			if (copy_of_src.at<unsigned char>(y, a) != prev) {
				num_of_changes++;
			}
			prev = copy_of_src.at<unsigned char>(y, a);
		}
		if (num_of_changes > 7) {  //draw vertical line
			for(int a = 0; a< src.cols; a++) {
				src.at<unsigned char>(y, a) = 255;
			}
			found = true;
		}
		y++;
	}
	found = false;
	prev = prev_init;
	y = src.rows-1;
	while ((!found) && (y > 0)) {
		num_of_changes = 0;
		for(int a = 0; a< copy_of_src.cols; a++) {
			if (copy_of_src.at<unsigned char>(y, a) != prev) {
				num_of_changes++;
			}
			prev = copy_of_src.at<unsigned char>(y, a);
		}
		if (num_of_changes > 7) {  //draw vertical line
			for(int a = 0; a< src.cols; a++) {
				src.at<unsigned char>(y, a) = 255;
			}
			found = true;
		}
		y--;
	}
}
*/
Mat PlateFinder::remove_frame(Mat src) {
	//y == 0
	//y == max
	for (int x = 0; x < src.cols; x++) {
		remove_neighborhood(src, x, 0);
		remove_neighborhood(src, x, src.rows-1);
	}
	//x == 0
	//x == max
	for (int y = 0; y < src.rows; y++) {
		remove_neighborhood(src, 0, y);
		remove_neighborhood(src, src.cols-1, y);
	}


	//mark_possible_ends_of_frame(src);
	//remove_neighborhood(src, src.cols /2, 0);
	//remove_neighborhood(src, src.cols /2, src.rows-1);
/*	remove_neighborhood(src, 0, src.rows / 2);
	remove_neighborhood(src, src.cols -1,  src.rows / 2 );
*/
	//Mat filter_element = table.clone();

	return src;
}

std::vector<Mat> PlateFinder::filter_candidates(std::vector<Mat> candidatesMat) {

		/* GOOD WORKING
		 *
		 * Mat img = candidatesMat[i];
		Mat bw;
		cv::resize( img, img, Size(0,0), 2, 2) ;

		cv::cvtColor(img, bw, CV_BGR2GRAY);
		//cv::blur(bw, bw, cv::Size(1,5));
		medianBlur(bw, bw, 3);
		namedWindow( "a1", CV_WINDOW_AUTOSIZE );
		imshow( "a1",bw );
		medianBlur(bw, bw, 3);
		namedWindow( "a2", CV_WINDOW_AUTOSIZE );
		imshow( "a2",bw );
		bw = bw * 2;
		threshold(bw, bw, 200, 255, THRESH_BINARY);
		open_img(bw, bw, Mat::ones(5,5,CV_8U), Point(-1,1), 1 );
		close_img(bw, bw, Mat::ones(5,5,CV_8U), Point(-1,1), 1 );
		namedWindow( "a3", CV_WINDOW_AUTOSIZE );
		imshow( "a3",bw );
		 */



	std::cout<< "START" << std::endl;
	std::vector<Mat> goodCandidates;

	std::vector<cv::Vec4i> lines;
	for (unsigned i = 0; i < candidatesMat.size(); i++) {
		//namedWindow( "Candidate1", CV_WINDOW_AUTOSIZE );

		Mat img = candidatesMat[i];
		Mat bw;
		cv::resize( img, img, Size(0,0), 2, 2) ;

		cv::cvtColor(img, bw, CV_BGR2GRAY);
		//cv::blur(bw, bw, cv::Size(1,5));
		//medianBlur(bw, bw, 3);
		//namedWindow( "a1", CV_WINDOW_AUTOSIZE );
		//imshow( "a1",bw );
		medianBlur(bw, bw, 3);
		//namedWindow( "a2", CV_WINDOW_AUTOSIZE );
		//imshow( "a2",bw );
		bw = bw * 2;
		threshold(bw, bw, 200, 255, THRESH_BINARY);
		open_img(bw, bw, Mat::ones(2,2,CV_8U), Point(-1,1), 1 );
		close_img(bw, bw, Mat::ones(2,2,CV_8U), Point(-1,1), 1 );
		cv::Canny(bw, bw, 50, 250, 3, true);
		//dilate(bw, bw, Mat::ones(2, 2, CV_8U), Point(-1,1), 1);
		//close_img(bw, bw, Mat::ones(2,2,CV_8U), Point(-1,1), 20);
		vector<vector<Point> > contours;
		vector<Vec4i> hierarchy;

		//namedWindow( "a3", CV_WINDOW_AUTOSIZE );
		//imshow( "a3",bw );
		findContours( bw, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
		//cv::cvtColor(bw, bw, CV_GRAY2BGR);

		std::vector<RotatedRect> founded;
		Mat new_bw = Mat::zeros(bw.size(), CV_8U);
		cv::cvtColor(new_bw, new_bw, CV_GRAY2BGR);
		vector<RotatedRect> minRect( contours.size() );
		std::cout<< contours.size() << std::endl;
		for( unsigned j = 0; j< contours.size(); j++ )
		{
		   std::vector<Point> rectangle(4);
		   minRect[j] = minAreaRect( Mat(contours[j]) );
		   Point2f rect_points[4];
		   minRect[j].points( rect_points );
		   float width = minRect[j].size.width > minRect[j].size.height ? minRect[j].size.width : minRect[j].size.height;
		   float height = minRect[j].size.width > minRect[j].size.height ? minRect[j].size.height : minRect[j].size.width;



		   if ((width > (bw.cols * 0.3f)) && (height > (bw.rows * 0.3f) ) && is_rectangle_in_mat(minRect[j], bw)) {
			   founded.push_back(minRect[j]);
		   }
		   			//drawContours( new_bw, contours, i, CV_RGB(100,180,180), 2, 8, hierarchy, 0, Point() );
		}

		//Usuwanie obszarow zawierajacych mniejsze obszary - zostawienie mozliwie najdokladniejszego oszacowania pozycji tablicy
		std::vector<RotatedRect> candidates_temp;
		std::cout<<founded.size();
		bool checked_flags[founded.size()];
		for (unsigned l = 0; l < founded.size(); l++) {
			checked_flags[l] = false;
		}
		for (unsigned l = 0; l < founded.size(); l++) {
			bool smaller_exist = false;
			RotatedRect rect1 = founded[l];

			for (unsigned m = 0; m < founded.size(); m++ ) {
				if (l != m) {
					if (checked_flags[m] == false) {
						RotatedRect rect2 = founded[m];
						if (is_subarea_of(rect2, rect1)) {
							checked_flags[l] = true;
							std::cout <<"TRUE";
							std::cout << "area:" << rect1.size << " subarea:  " << rect2.size << std::endl;

							smaller_exist = true;
							break;
						}
					}
				}
			}
			if (!smaller_exist) {
				candidates_temp.push_back(rect1);
			}
		}

		for( unsigned j = 0; j< candidates_temp.size(); j++ ) {

		   Point2f rect_points[4];
		   candidates_temp[j].points( rect_points );
		   for( unsigned k = 0; k < 4; k++ )
 		   {

		        line( new_bw, rect_points[k], rect_points[(k+1)%4],  CV_RGB(255,0,0), 1, 8 );

		   }
				   			//drawContours( new_bw, contours, i, CV_RGB(100,180,180), 2, 8, hierarchy, 0, Point() );
		}



		for (unsigned i = 0; i < candidates_temp.size(); i++) {
			goodCandidates.push_back(get_subimage(candidates_temp[i], img));
		}
		candidates_temp.clear();
		//namedWindow( "contours", CV_WINDOW_AUTOSIZE );
		//imshow( "contours",new_bw );

	}
	return goodCandidates;
}

bool PlateFinder::is_rectangle_in_mat(RotatedRect rect, Mat mat) {

	Point2f rect_points[4];
	rect.points( rect_points );
	for (int i = 0; i < 4; i++) {
		if ((rect_points[i].x > mat.cols) || (rect_points[i].x < 0)
				|| (rect_points[i].y > mat.rows) || (rect_points[i].y < 0)) {

			return false;
		}
	}
	return true;

}


bool PlateFinder::is_horizontal_rectangle(RotatedRect rect) {

	Point2f rect_points[4];
	rect.points( rect_points );
	Point2f first = rect_points[0];
	int min_distance = distance(first, rect_points[1]);
	int max_distance = distance(first, rect_points[1]);;
	Point min = rect_points[1];
	Point max = rect_points[1];
	Point medium = rect_points[1];
	for (int i = 2; i < 4; i++) {
		int dist = distance(first, rect_points[i]);
		if (dist > max_distance) {
			medium = max;
			max_distance = dist;
			max = rect_points[i];
		} else if(dist < min_distance) {
			medium = min;
			min_distance = dist;
			min = rect_points[i];
		} else {
			medium = rect_points[i];
		}
	}

	float tga = 0;
	tga = fabs(medium.y - first.y) / fabs(medium.x - first.x);
	if (tga > 0.8f) {
		return false;
	}

	return true;
}



bool PlateFinder::check_proportions(float width, float height, float precision = 1.0f){
	float greater = width;
	float smaller = height;
	if (width < height) {
		greater = height;
		smaller = width;
	}
	if (fabs((greater / smaller) - 4.56) < precision)
	{
		return true;
	}
	return false;
}






void PlateFinder::open_img(Mat src, Mat &dst, Mat element, Point point = Point(-1,1), int iterations = 1 ){
	erode(src, dst, element, point, iterations);
	dilate(dst, dst, element, point, iterations);
}

void PlateFinder::close_img(Mat src, Mat &dst, Mat element, Point point = Point(-1,1), int iterations = 1 ){
	dilate(src, dst, element, point, iterations);
	erode(dst, dst, element, point, iterations);
}

void PlateFinder::white_top_hat(Mat src, Mat &dst, Mat element ){
	open_img(src, dst, element);
	dst = src - dst;
}

void PlateFinder::black_top_hat(Mat src, Mat &dst, Mat element ){

	close_img(src, dst, element);
	dst = dst - src;
}

std::vector<cv::Vec4i> PlateFinder::find_candidates(std::vector<cv::Vec4i> lines, Mat &src, float precision = 0.15f) {
	std::vector<cv::Vec4i> results;
	for (unsigned i = 0; i < lines.size(); i++)
	{
		/*cv::Vec4i v = lines[i];
		cv::line(src, cv::Point(v[0], v[1]), cv::Point(v[2], v[3]),CV_RGB(255,0,0) , 1);
		namedWindow( "cannyTRUE", CV_WINDOW_AUTOSIZE );
		imshow( "cannyTRUE",src );
		cv::waitKey();
		 */
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

					if ((is_similar_to_rectangle) && (fabs((avg_long_dist / avg_short_dist) - 4.56) < 0.5f/*2.0f*/)) {
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

Mat PlateFinder::horizontal(int size){
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

int PlateFinder::distance(Point p1, Point p2){
	return sqrt(((p1.x - p2.x) * (p1.x - p2.x))+((p1.y - p2.y)*(p1.y - p2.y)));
}

bool PlateFinder::has_similar_length(Point p1, Point p2, Point p3, Point p4, float precision = 0.15f ) {
	int l1_length = distance(p1, p3);
	int l2_length = distance(p2, p4);
	float length_avg = ( l1_length + l2_length ) / 2.0f;
	if (abs(l1_length - l2_length) < round(precision * length_avg) ) {
		return true;
	} else {
		return false;
	}
}

Mat PlateFinder::get_subimage(RotatedRect rect, Mat src) {
    Mat M, rotated, cropped;
	float angle = rect.angle;
	//float width = rect.size.width - 20.0f;
	float width = rect.size.width;
	/*if (width > 100) {
		width = width - (width / 12.0);
	}*/
	Size rect_size(width, rect.size.height);

	if (rect.angle < -45.0f) {
		angle += 90.0f;
		int width = rect_size.width;
		rect_size.width = rect_size.height;
		rect_size.height = width;
	}
	// get the rotation matrix
	M = getRotationMatrix2D(rect.center, angle, 1.0);
	// perform the affine transformation
	warpAffine(src, rotated, M, src.size(), INTER_CUBIC);
	// crop the resulting image
	getRectSubPix(rotated, rect_size, rect.center, cropped);
	return cropped;
}



bool PlateFinder::is_subarea_of(RotatedRect rect1, RotatedRect rect2) {

	Point2f rect_points[4];
	rect1.points(rect_points);

	Point2f candidate_points[4];
	rect2.points( candidate_points );
	std::vector<Point2f> cont;
	for (int i = 0; i <= 3; i++) {
		cont.push_back(candidate_points[i]);
	}
	bool is_in = true;

	for (unsigned i = 0; i <= 3; i++) {


		if (pointPolygonTest(cont, rect_points[i], false) < 0) {
			is_in = false;
		}
	}
	if (is_in) {
		return true;
	}
	return false;
}

bool PlateFinder::is_subarea_of_another_candidate(std::vector<RotatedRect> candidates, RotatedRect rect) {


	for (unsigned j = 0; j < candidates.size(); j++ ) {

		if (is_subarea_of(rect, candidates[j])) {
			return true;
		}
	}

	return false;
}


/*
bool PlateFinder::is_subarea_of_another_candidate(std::vector<RotatedRect> candidates, RotatedRect rect) {

	Point2f rect_points[4];
	rect.points(rect_points);

	for (unsigned j = 0; j < candidates.size(); j++ ) {
		Point2f candidate_points[4];
		candidates[j].points( candidate_points );
		std::vector<Point2f> cont;
		for (int i = 0; i <= 3; i++) {
			cont.push_back(candidate_points[i]);
		}
		bool is_in = true;

		for (unsigned i = 0; i <= 3; i++) {


			if (pointPolygonTest(cont, rect_points[i], false) < 0) {
				is_in = false;
			}
		}
		if (is_in) {
			return true;
		}
	}

	return false;
}
*/

