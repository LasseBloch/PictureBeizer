//
// Created by Lasse Bloch Lauritsen on 22/05/2020.
//

#ifndef PICTUREBEIZER_PICTUREREDUCER_H
#define PICTUREBEIZER_PICTUREREDUCER_H

#include <opencv2/core/mat.hpp>

class PictureReducer {
public:
	explicit PictureReducer(cv::Mat img);
	void updateImage();
	void addAdjustmentTrackbars();
	void setAdaptiveConstant(int newConstant);
	void setAdaptiveBlockSize(int newBlockSize);
	void setReductionPercentage(int percentage);
	void reducePixels();
	[[nodiscard]] cv::Mat getReducedImage() const;
	void closeAdjustmentWindow();
private:
	cv::Mat greyImg;
	cv::Mat bwImg;
	cv::Mat reducedImg;
	const std::string windowTitle{"Adjustments"};
	// Amount to be subtracted from wighted sum of neighbourhood pixels
	int adaptiveConstant{0};
	int adaptiveBlockSize{11};
	int reductionPercentage{0};
};

#endif //PICTUREBEIZER_PICTUREREDUCER_H
