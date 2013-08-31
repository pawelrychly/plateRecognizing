/*
 * PlateFinder.h
 *
 *  Created on: 15-08-2013
 *      Author: Pawe³
 */

#ifndef PLATEFINDER_H_
#define PLATEFINDER_H_


#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdio.h>
#include <math.h>

using namespace cv;

class PlateFinder {
public:
	PlateFinder(string file_name);
	virtual ~PlateFinder();
	void open_img(Mat src, Mat &dst, Mat element, Point point, int iterations );
	std::vector<Mat> find_plates();
private:
	Mat src;
	void close_img(Mat src, Mat &dst, Mat element, Point point, int iterations);
	void white_top_hat(Mat src, Mat &dst, Mat element );
	void black_top_hat(Mat src, Mat &dst, Mat element );
	bool check_proportions(float width, float height, float precision);
	Mat horizontal(int size);
	int distance(Point p1, Point p2);
	bool has_similar_length(Point p1, Point p2, Point p3, Point p4, float precision);
	std::vector<cv::Vec4i> find_candidates(std::vector<cv::Vec4i> lines, Mat &src, float precision );
	bool is_horizontal_rectangle(RotatedRect rect);
	Mat get_subimage(RotatedRect rect, Mat src);
	bool is_subarea_of_another_candidate(std::vector<RotatedRect> candidates, RotatedRect rect);
	bool is_subarea_of(RotatedRect rect1, RotatedRect rect2);
	std::vector<Mat> filter_candidates(std::vector<Mat> candidatesMat);
	bool is_rectangle_in_mat(RotatedRect rect, Mat mat);
};

#endif /* PLATEFINDER_H_ */
