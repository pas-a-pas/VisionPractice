//
//  HistogramRunner.hpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/30.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#ifndef HistogramRunner_hpp
#define HistogramRunner_hpp

#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

class HistogramRunner {
public:
    cv::Mat run(const std::string& imageDirectory);
    
private:
    static void onEachImage(const std::string& imageName, void* params);
    
    void pick(const std::string& imageDirectory, const std::string& patchFile);
    
    cv::Mat analyze(const std::string& patchFile);
    
    cv::FileStorage fileStorage;
};

#endif /* HistogramRunner_hpp */
