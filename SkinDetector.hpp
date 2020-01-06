//
//  SkinDetector.hpp
//  VisionPractice
//
//  Created by Hyunmi on 2020/01/02.
//  Copyright © 2020 Hyunmi. All rights reserved.
//

#ifndef SkinDetector_hpp
#define SkinDetector_hpp

#include <opencv2/opencv.hpp>
#include <stdio.h>

using namespace cv;

class SkinDetector {
public:
    SkinDetector(cv::Mat histogram);
    
    void detect(const std::string& imagePath);

private:
    static void onEachImage(const std::string& imageName, void* params);

    cv::Mat backProject(cv::Mat image);
        
    cv::Mat histogram;
};
#endif /* SkinDetector_hpp */
