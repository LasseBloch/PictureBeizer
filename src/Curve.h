//
// Created by Lasse Bloch Lauritsen on 23/05/2020.
//

#ifndef PICTUREBEIZER_CURVE_H
#define PICTUREBEIZER_CURVE_H

#include <opencv2/core/mat.hpp>

class Curve {
public:
	// Create curve from image
    explicit Curve(const cv::Mat& img);
	void addPoint(const cv::Point& point);
	void addPoint(int x, int y);
	cv::Mat curveToImg();

private:
	std::vector<cv::Point> path;
	cv::Mat pathImage;
	void shufflePath();
	int bezierInterpolate(int val1 , int val2 , float percentage) const;
	void bezierQuadratic(cv::Point p1, cv::Point p2, cv::Point p3);
	cv::Point getNearestPoint(const cv::Point& startingPoint, std::vector<cv::Point>& possiblePoints) const;
	// TODO: Rename
	std::vector<cv::Point> sortPath();
};

#endif //PICTUREBEIZER_CURVE_H
