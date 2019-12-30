//
//  ImagePatchPicker.hpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/23.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#ifndef ImagePatchPicker_hpp
#define ImagePatchPicker_hpp

#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <iostream>
#include <vector>

using namespace cv;
using namespace std;

class ImagePatchPicker {
public:
    ImagePatchPicker(std::string imagePath);
    
    std::vector<cv::Rect> pick();

private:
    static cv::Mat draw(cv::Mat image, cv::Rect box = Rect());
        
    static void onMouseEvent(int event, int x, int y, int flags, void* param);
        
    bool onPicking;
    
    cv::Mat image;
        
    cv::Rect pickingPatch;
    
    std::vector<cv::Rect> patches;
};
#endif /* ImagePatchPicker_hpp */
