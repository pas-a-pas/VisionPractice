//
//  HsvHistogram.hpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/26.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#ifndef HsvHistogram_hpp
#define HsvHistogram_hpp

#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

class HsvHistogram {
public:
    HsvHistogram(int binHue, int binSaturation);
    
    void run(cv::Mat image, cv::Mat& histogram, bool accumulate = false, bool normalize = true, bool interactive = false);

    void chart(cv::Mat historam);

private:
    static void chartTest(int binHue, int binSaturation);

    static cv::Scalar toColor(int hueIndex, int saturationIndex, int intensity, int binHue, int binSaturation);

    static void showAndWait(cv::Mat image);
    
    int binHue;
    
    int binSaturation;
};
#endif /* HsvHistogram_hpp */
