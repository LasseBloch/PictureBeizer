//
// Created by Lasse Bloch Lauritsen on 22/05/2020.
//

// Various helper/wrapper free standing functions
#include <iostream>
#include <optional>
#include <filesystem>
#include "Helpers.h"


namespace Helpers {
	std::optional<cv::Mat> loadImg(const std::string& filePath)
	{
		if (! std::filesystem::exists(filePath)) {
			std::cout << "File: " << filePath << " could not be found";
			return std::nullopt;
		}
		return cv::imread(filePath);
	}
}