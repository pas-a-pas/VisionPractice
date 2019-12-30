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
    void run(std::string imageDirectory);
    
private:
    static void onEachImage(const std::string& directory, const std::string& imageName, void* params);
    
    void pick(std::string imageDirectory, std::string patchFile);
    
    void analyze(std::string patchFile);
    
    cv::FileStorage fileStorage;
};

#endif /* HistogramRunner_hpp */
