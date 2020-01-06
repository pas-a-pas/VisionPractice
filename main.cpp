//
//  main.cpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/11/25.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#include "HistogramRunner.hpp"
#include "SkinDetector.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[]) {
    HistogramRunner runner;
    cv::Mat histogram = runner.run("/* path to an image or a directory */");
    
    SkinDetector detector(histogram);
    detector.detect("/* path to an image or a directory */");
    
    return 0;
}
