//
//  HsvHistogram.cpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/26.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#include "HsvHistogram.hpp"

using namespace std;

HsvHistogram::HsvHistogram(int binHue, int binSaturation)
    : binHue(binHue), binSaturation(binSaturation) {
}

void
HsvHistogram::run(cv::Mat image, cv::Mat& histogram, bool accumulate, bool normalize, bool interactive) {
    if (interactive) {
        showAndWait(image);
    }
    
    cv::Mat hsv;
    cv::cvtColor(image, hsv, cv::COLOR_BGR2HSV);
    
    int size[] = {binHue, binSaturation};
    float rangeHue[] = {0, 180}; //[0, 180)
    float rangeSaturation[] = {0, 256}; // [0, 256)
    const float* ranges[] = {rangeHue, rangeSaturation};
    int ch[] = {0, 1};
    
    cv::calcHist(&hsv, 1, ch, noArray(), histogram, 2, size, ranges, true, accumulate);
    if(normalize) {
        cv::normalize(histogram, histogram, 0, 255, NORM_MINMAX);
    }
}

void
HsvHistogram::chart(cv::Mat historam) {
    int scale = 10;
    Mat histImage = cv::Mat::zeros(binSaturation * scale, binHue * scale, CV_8UC3);
    for (int h = 0; h < binHue; h++) {
        for (int s = 0; s < binSaturation; s++) {
            float value = historam.at<float>(h, s);
            cv::Scalar color = toColor(h, s, value, binHue, binSaturation);
            cv::rectangle(histImage, cv::Rect(h * scale, s * scale, scale, scale), color, -1);
        }
    }
    
    showAndWait(histImage);
}

void
HsvHistogram::chartTest(int binHue, int binSaturation) {
    int scale = 10;
    Mat histImage = cv::Mat::zeros(binSaturation * scale, binHue * scale, CV_8UC3);
    for (int h = 0; h < binHue; h++) {
        for (int s = 0; s < binSaturation; s++) {
            cv::Scalar color = toColor(h, s, 255, binHue, binSaturation);
            cv::rectangle(histImage, cv::Rect(h * scale, s * scale, scale, scale), color, -1);
        }
    }
    
    showAndWait(histImage);
}

cv::Scalar
HsvHistogram::toColor(int hueIndex, int saturationIndex, int intensity, int binSizeHue, int binSizeSaturation) {
    Vec3b hsv;
    hsv.val[0] = hueIndex * 180.f / (float) binSizeHue;
    hsv.val[1] = saturationIndex * 256.f / (float) binSizeSaturation;
    hsv.val[2] = intensity;
    
    Mat3b bgr;
    cvtColor(Mat3b(hsv), bgr, cv::COLOR_HSV2BGR);
    cv::Scalar color(bgr.at<Vec3b>(0, 0).val[0],
                     bgr.at<Vec3b>(0, 0).val[1],
                     bgr.at<Vec3b>(0, 0).val[2]);
    
    return color;
}

void
HsvHistogram::showAndWait(cv::Mat image) {
    cv::namedWindow("HsvHistogram", cv::WINDOW_NORMAL);
    imshow("HsvHistogram", image);
    waitKey();
    cv::destroyWindow("HsvHistogram");
}
