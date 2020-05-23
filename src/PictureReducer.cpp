//
// Created by Lasse Bloch Lauritsen on 22/05/2020.
//

#include "PictureReducer.h"

#include <utility>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <cstdlib>
#include <ctime>

typedef uint8_t GrepScalePixel;


void trackbarAdoptiveConstantCallback(int pos, void* ptr)
{
	auto* obj = reinterpret_cast<PictureReducer*>(ptr);
	obj->setAdaptiveConstant(pos);
	obj->updateImage();
}

void trackbarAdoptivBlockSizeCallback(int pos, void* ptr)
{
	auto* obj = reinterpret_cast<PictureReducer*>(ptr);
	// Must be odd numbers

	if (pos > 1) {
		bool odd = pos % 2 == 1;
		if (!odd) {
			pos++;
		}
		obj->setAdaptiveBlockSize(pos);
		obj->updateImage();
	}
}

void trackbarReductionCallback(int pos, void* ptr)
{
	auto* obj = reinterpret_cast<PictureReducer*>(ptr);
	obj->setReductionPercentage(pos);
	obj->updateImage();
}


PictureReducer::PictureReducer(cv::Mat img)
{
	cv::cvtColor(img, greyImg, cv::COLOR_BGR2GRAY);
	cv::namedWindow(windowTitle);
	cv::imshow(windowTitle, greyImg);
	bwImg = greyImg.clone();
	addAdjustmentTrackbars();
	updateImage();

	/* initialize random seed: */
	srand(time(NULL));
}

void PictureReducer::updateImage()
{
	adaptiveThreshold(greyImg, bwImg, 255,
			cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, adaptiveBlockSize, adaptiveConstant);
	reducePixels();
	cv::imshow(windowTitle, reducedImg);
}

void PictureReducer::addAdjustmentTrackbars()
{
	cv::createTrackbar("Adaptive constant", windowTitle, &adaptiveConstant, 40, trackbarAdoptiveConstantCallback, static_cast<void*>(this));
	cv::createTrackbar("Adaptive block size", windowTitle, &adaptiveBlockSize, 100, trackbarAdoptivBlockSizeCallback, static_cast<void*>(this));
	cv::createTrackbar("Reduce pixels", windowTitle, &reductionPercentage, 100, trackbarReductionCallback, static_cast<void*>(this));
}

void PictureReducer::setAdaptiveConstant(int newConstant)
{
	adaptiveConstant = newConstant;
}

void PictureReducer::setAdaptiveBlockSize(int newBlockSize)
{
	adaptiveBlockSize = newBlockSize;
	std::cout << adaptiveBlockSize << '\n';
}

void PictureReducer::setReductionPercentage(int percentage)
{
	reductionPercentage = percentage;
}

void PictureReducer::reducePixels()
{
	// Using opencv for each for performance (will be multi threaded)
	reducedImg = bwImg.clone();
	reducedImg.forEach<GrepScalePixel>([&](GrepScalePixel &p, const int * position) -> void {
		// if reductionPercentage dont do any thing
		int keepPercentage = 100 - reductionPercentage;
		if (keepPercentage != 100) {
			bool keeper =  (rand() % 100) < keepPercentage;
			if (!keeper) {
				p = 255;
			}
	    }
	});
}

cv::Mat PictureReducer::getReducedImage() const
{
	return reducedImg;
}

void PictureReducer::closeAdjustmentWindow()
{
	cv::destroyWindow(windowTitle);
}

