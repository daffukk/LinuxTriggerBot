#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

bool differentpixels(std::string clipPath, std::string actionPath) {

  cv::Mat clip = cv::imread(clipPath ,cv::IMREAD_GRAYSCALE);
  cv::Mat action = cv::imread(actionPath, cv::IMREAD_GRAYSCALE);

  if(clip.empty() || action.empty()) return false;

  cv::Mat diff;
  cv::bitwise_xor(clip, action, diff);

  int counter = cv::countNonZero(diff);

  std::cout << diff << std::endl;
  return counter > 40;
}
