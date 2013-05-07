#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;
using namespace std;


/*int getQuartile(Mat img) {

	for(int i = 0; i < img.rows; i++)
	{
	    for(int j = 0; j < img.cols; j++)
	    {
	    	unsigned char value = img.at<unsigned char>(i, j);

	        // do something with BGR values...
	    }
	}
}*/

Mat horizontal(int size){
	Mat src = Mat::ones(size, size, CV_8U);

	for(int i = 0; i < src.rows; i++)
	{
		for(int j = 0; j < src.cols; j++)
		{
			if ((i < (src.rows * 0.4f )) || (i > (src.rows * 0.5f ))) {
				src.at<char>(i,j) = 0;
			}
		}
	}
	cout << src;
	return src;
}
/*
void maxNeighbour(Mat img, Mat &dst) {

	for(int i = 0; i < img.rows; i++)
	{
	    for(int j = 0; j < img.cols; j++)
	    {

	        // do something with BGR values...
	    }
	}
}*/

void open_img(Mat src, Mat &dst, Mat element ){
	erode(src, dst, element);
	dilate(dst, dst, element);
}

void close_img(Mat src, Mat &dst, Mat element ){
	dilate(src, dst, element);
	erode(dst, dst, element);
}

void white_top_hat(Mat src, Mat &dst, Mat element ){
	open_img(src, dst, element);
	dst = src - dst;
}

void black_top_hat(Mat src, Mat &dst, Mat element ){

	close_img(src, dst, element);
	dst = dst - src;
}
/*
void removeGreen(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(100, 110, 0), cv::Scalar(255, 255,160), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}*/










void removeDarkBlue(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(30, 0, 0), cv::Scalar(255, 40,40), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}

void removeBlue(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(130, 0, 0), cv::Scalar(255, 140,100), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}

void removeLightBlue(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(200, 50, 50), cv::Scalar(255, 185,185), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}

/*void removeNotWhiteAndBlack(Mat src, Mat &res){
	Mat mask;
	Mat

	inRange(src, cv::Scalar(30, 30, 30), cv::Scalar(200, 200, 200), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}*/







/*
void removeLowRed(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(150, 10, 10), cv::Scalar(255, 40,40), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}

void removeLowBlue(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(0, 0, 0), cv::Scalar(40, 255,255), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}

void removeLowGreen(Mat src, Mat &res){
	Mat mask;
	inRange(src, cv::Scalar(0, 0, 0), cv::Scalar(255, 40,255), mask);
	bitwise_not(mask,mask);
	src.copyTo(res, mask);
}
*/

/** @function main */
int main( int argc, char** argv )
{

  Mat mask;
  Mat res;
  Mat res2;
  Mat res3;
  Mat res4;
  Mat im_gray;
  Mat bth;
  Mat src = imread( argv[1], CV_LOAD_IMAGE_COLOR );
 // removeGreen(src, res);
  removeDarkBlue(src, res);
  removeBlue(res, res2);
  removeLightBlue(res2, res3);
 // removeNotWhiteAndBlack(src, res3);
//  cvtColor(src,im_gray,CV_RGB2GRAY);

 // cvtColor(im_gray, res3,CV_GRAY2RGB);
  //medianBlur(im_gray, res4, 3);

  //res4 = src - res3;
  Mat ones = Mat::ones(9, 9, CV_8U);
 // black_top_hat(res3, bth, ones );
  //removeLowRed(res, res2 );
  //removeLowBlue(res2, res3);
  //removeLowGreen(res3, res4);
  namedWindow( "Source", CV_WINDOW_AUTOSIZE );
  imshow( "Source", src );
  namedWindow( "remove_green", CV_WINDOW_AUTOSIZE );
  imshow( "remove_green", res3 );
  //namedWindow( "diff", CV_WINDOW_AUTOSIZE );
  //imshow( "diff", res4 );

  // namedWindow( "brown", CV_WINDOW_AUTOSIZE );
 // imshow( "brown", res4 );

  //bitwise_and(src, mask, src);
  //Mat im_gray;
  //cvtColor(src,im_gray,CV_RGB2GRAY);
  //Mat hor = horizontal(9);
  //Mat vertical_ones = Mat::ones(1, 15, CV_8U);

  //cout << vertical_ones;
  //cout << vertical_ones;
  //equalizeHist(src, src);
  //dilate(src, bth, three_square);
  /// Gradient X
  //Sobel( src, grad_x, ddepth, 1, 0, 3 );
  /// Gradient Y
  //Sobel( src, grad_y, ddepth, 0, 1, 3 );
  //threshold(grad_x, grad_x, 128, 255, THRESH_OTSU);
 // medianBlur(grad_x, grad_x, 3);
  //dilate(grad_x, grad_x, vertical_ones);
  //dilate(grad_y, grad_y, vertical_ones);
  //threshold(grad_x, grad_x, 128, 255, THRESH_OTSU);
  //threshold(grad_y, grad_y, 128, 255, THRESH_OTSU);
  //grad_xy = grad_x + grad_y;
  //bitwise_and(grad_x, grad_y, grad_xy);
 // equalizeHist(src_minus_light, hist);

  //erozja dylatacji - src

 /* black_top_hat(src, bth, ones );
  black_top_hat(bth, dst, ones_2);
*/

  //black_top_hat(src, bth, horizontal(15) );
  //black_top_hat(bth, dst, horizontal(3));
//  medianBlur(dst, thresh, 19);
  //equalizeHist(dst, thresh);
  //threshold(dst, thresh, 64, 255, THRESH_BINARY);
  //Sobel( bth, grad_x, ddepth, 1, 0, 3 );
  //dilate(grad_x, dst, three_square);
  //equalizeHist(bth, dst);

  //threshold(dst, dst, 128, 255, THRESH_OTSU);
  //white_top_hat(src, wth, ones);
  //equalizeHist(bth, bth);
  //equalizeHist(bth, bth);

 // namedWindow( "bth_1", CV_WINDOW_AUTOSIZE );
  //imshow( "bth_1", bth);
  //namedWindow( "bth_2", CV_WINDOW_AUTOSIZE );
  //imshow( "bth_2", dst);
//  namedWindow( "thresh", CV_WINDOW_AUTOSIZE );
//  imshow( "thresh", thresh );
 /* namedWindow( "WTH", CV_WINDOW_AUTOSIZE );
  imshow( "WTH", wth );
 */
  //medianBlur(grad_x, grad_x, 9);

//  namedWindow( "sX", CV_WINDOW_AUTOSIZE );
//  imshow( "sX", grad_x);

  //threshold(grad_x, grad_x, 128, 255, THRESH_OTSU);
 // namedWindow( "sY", CV_WINDOW_AUTOSIZE );
//  imshow( "sY", grad_y);

 // namedWindow( "sXY", CV_WINDOW_AUTOSIZE );
 // imshow( "sXY", grad_xy);

 /* namedWindow( "Source", CV_WINDOW_AUTOSIZE );
  imshow( "Source", src );
  namedWindow( "Median", CV_WINDOW_AUTOSIZE );
  imshow( "Median", src_minus_light);
 */
  //namedWindow( "Destination", CV_WINDOW_AUTOSIZE );
  //imshow( "Destination", dst);
 /* namedWindow( "Hist", CV_WINDOW_AUTOSIZE );
  imshow( "Hist", hist);
  namedWindow( "2_src", CV_WINDOW_AUTOSIZE );
  imshow( "2_src", src_median_2 );
*/
  waitKey(0);
  return(0);
}
