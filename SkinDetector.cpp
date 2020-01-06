//
//  SkinDetector.cpp
//  VisionPractice
//
//  Created by Hyunmi on 2020/01/02.
//  Copyright © 2020 Hyunmi. All rights reserved.
//

#include "SkinDetector.hpp"
#include "FileUtils.hpp"

using namespace std;

SkinDetector::SkinDetector(cv::Mat histogram): histogram(histogram) {
}

void
SkinDetector::detect(const std::string& imagePath) {
    if (FileUtils::isDirectory(imagePath)) {
        FileUtils::listFiles(imagePath, onEachImage, this);
    } else {
        onEachImage(imagePath, this);
    }
}

cv::Mat
SkinDetector::backProject(cv::Mat image) {
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);

    cv::Mat result;
    float rangeHue[] = {0, 180}; //[0, 180)
    float rangeSaturation[] = {0, 256}; // [0, 256)
    const float* ranges[] = {rangeHue, rangeSaturation};
    int ch[] = {0, 1};
    cv::calcBackProject(&hsv, 1, ch, histogram, result, ranges);
    
    return result;
}

void
SkinDetector::onEachImage(const std::string& imageName, void* params) {
    cv::Mat image = cv::imread(imageName);
    
    cv::namedWindow("SkinDetector", cv::WINDOW_NORMAL|cv::WINDOW_KEEPRATIO);
    cv::resizeWindow("SkinDetector", 800, 800);
    cv::imshow("SkinDetector", image);
    waitKey();

    SkinDetector* pThis = (SkinDetector*) params;
    cv::Mat project = pThis->backProject(image);
    cv::imshow("SkinDetector", project);
    waitKey();
}
