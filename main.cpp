#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include "src/Helpers.h"
#include "src/PictureReducer.h"
#include "src/Curve.h"

int main()
{
	// Open picture
	const auto filePath = "../test_pictures/Tesla_circa_1890.jpeg";
	bool done = false;

	auto loadedContent = Helpers::loadImg(filePath);

	if (!loadedContent.has_value()) {
		return 1;
	}
	// TODO: Optional was not as pretty as I hoped
	auto originalImage = loadedContent.value_or(cv::Mat());

	PictureReducer reducer(originalImage);

	std::cout << "Use adjustment window to adjust image\nPress n when satisfied\n";

	while (!done) {
		char c = (char) cv::waitKey(1);
		if (c == 27 || c == 'q' || c == 'Q') //Allow ESC to quit
		{
			done = true;
		}
		else if (c == 'n')
		{
			const auto reducedImg = reducer.getReducedImage();
			reducer.closeAdjustmentWindow();
			Curve curve(reducedImg);
			auto curveImg = curve.curveToImg();
			cv::imshow("Curve img", curveImg);
		}
	}
	return 0;
}
