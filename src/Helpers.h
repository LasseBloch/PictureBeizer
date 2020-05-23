//
// Created by Lasse Bloch Lauritsen on 22/05/2020.
//

#ifndef PICTUREBEIZER_HELPERS_H
#define PICTUREBEIZER_HELPERS_H
#include <string>
#include <opencv2/opencv.hpp>

namespace Helpers {
	std::optional<cv::Mat> loadImg(const std::string& filePath);
}

#endif //PICTUREBEIZER_HELPERS_H
