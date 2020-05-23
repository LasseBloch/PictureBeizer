//
// Created by Lasse Bloch Lauritsen on 23/05/2020.
//

#include <iostream>
#include <random>
#include "Curve.h"
#include <opencv2/opencv.hpp>
typedef uint8_t GrepScalePixel;

Curve::Curve(const cv::Mat& img)
{
	// Loop through image and add points to path
	for (int y = 0; y < img.rows; y++) {
		for (int x = 0; x < img.cols; x++) {
			// if pixel is black add to path
			cv::Point point(x,y);
			if (img.at<uchar>(point) == 0) {
				addPoint(point);
			}
		}
	}

	pathImage = img.clone();
}

void Curve::addPoint(int x, int y)
{
	path.emplace_back(x, y);
}

void Curve::addPoint(const cv::Point2i& point)
{
	path.push_back(point);
}

void Curve::shufflePath()
{
	// shuffle array
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(path.begin(), path.end(), g);
}

cv::Mat Curve::curveToImg()
{
	pathImage.forEach<GrepScalePixel>([](GrepScalePixel &p, const int * position) -> void {
		// if reductionPercentage dont do any thing
		p = 255;
	});


	path = sortPath();
	for(const auto& point: path) {
		//pathImage.at<uchar>(point) = 150;
	}

	while(!path.empty()) {
		if (path.size() > 2) {
			// POP two points (the third is reused)
			auto p1 = path.back();
			path.pop_back();
			auto p2 = path.back();
			path.pop_back();
			auto p3 = path.back();
			bezierQuadratic(p1, p2, p3);
		}
		else {
			break;
		}

	}
	return pathImage;
}

int Curve::bezierInterpolate(int val1, int val2, float percentage) const
{
	int diff = val2 - val1;
	return val1 + (diff * percentage);
}

// See https://stackoverflow.com/questions/785097/how-do-i-implement-a-b%C3%A9zier-curve-in-c
void Curve::bezierQuadratic(cv::Point p1, cv::Point p2, cv::Point p3)
{
	for(float i = 0 ; i < 1 ; i += 0.00001)
	{
		// The Green Line
		int xa = bezierInterpolate(p1.x, p2.x, i);
		int ya = bezierInterpolate(p1.y, p2.y, i);
		int xb = bezierInterpolate(p2.x, p3.x, i);
		int yb = bezierInterpolate(p2.y, p3.y, i);

		// The Black Dot
		int x = bezierInterpolate(xa, xb, i);
		int y = bezierInterpolate(ya, yb, i);

		pathImage.at<uchar>(y, x) = 0;
	}
}

cv::Point2i Curve::getNearestPoint(const cv::Point& startingPoint, std::vector<cv::Point>& possiblePoints) const
{
	cv::Point result;
	double minDistance = std::numeric_limits<double>::max();
	for (int index = 0; index < possiblePoints.size(); index ++) {
		const auto diff = startingPoint - possiblePoints[index];
		double distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
		if (distance < minDistance) {
			minDistance = distance;
			result = possiblePoints[index];
		}
	}
	return result;
}

std::vector<cv::Point> Curve::sortPath()
{
	std::vector<cv::Point> newPath;

	auto& currentPoint = path.back();
	path.pop_back();
	newPath.push_back(currentPoint);

	while (!path.empty()) {
		currentPoint = getNearestPoint(currentPoint, path);
		newPath.push_back(currentPoint);
		// Remove the found point from imgPoints
		auto position = std::find(path.begin(), path.end(), currentPoint);
		if (position != path.end()) {
			path.erase(position);
		}
		else {
			std::cout << "Could not find point\n";
		}
	}
	return newPath;
}

