//
//  ImagePatchPicker.cpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/23.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#include "ImagePatchPicker.hpp"
#include <opencv2/opencv.hpp>
#include <thread>

using namespace cv;

ImagePatchPicker::ImagePatchPicker(std::string imagePath): onPicking(false) {
    image = cv::imread(imagePath);
    if (image.empty()) {
      cout << "can not load " << imagePath << endl;
    }
}

std::vector<cv::Rect>
ImagePatchPicker::pick() {
    cv::namedWindow("pick", cv::WINDOW_NORMAL|cv::WINDOW_KEEPRATIO);
    cv::resizeWindow("pick", 800, 800);
    cv::setMouseCallback("pick", onMouseEvent, this);

    cv::Mat buffer = image;
    cv::imshow("pick", buffer);
    
    bool isPicking = false;
    while (true) {
        int key = cv::waitKey(15);
        if (key == (int) 's') {
            break;
        } else if (key == (int) 'c') {
            patches.clear();
            buffer = image;
            cv::imshow("pick", buffer);
        }
        
        if (!isPicking && !onPicking) { // idle
            continue;
        }
        
        cv::Mat temp = buffer;
        if (pickingPatch.area() > 0) {
            temp = draw(buffer, pickingPatch);
        }
        cv::imshow("pick", temp);
        
        if (!isPicking && onPicking) { // start of picking
            isPicking = true;
        } else if (isPicking && !onPicking) { // end of picking
            if (pickingPatch.area() > 0) {
                patches.push_back(pickingPatch);
                pickingPatch = Rect();
            }
            isPicking = false;
            buffer = temp;
        }
    }
    
    cv::destroyWindow("pick");
    
    return patches;
}

cv::Mat
ImagePatchPicker::draw(cv::Mat image, cv::Rect box) {
    cv::Mat buffer;
    image.copyTo(buffer);
    if (box.area() > 0) {
        cv::rectangle(buffer, box.tl(), box.br(), cv::Scalar(0xff, 0xff, 0xff), 5);
    }
    
    return buffer;
}

void
ImagePatchPicker::onMouseEvent(int event, int x, int y, int flags, void* param) {
    ImagePatchPicker* picker = (ImagePatchPicker*) param;
    
    switch (event) {
        case cv::EVENT_MOUSEMOVE:
            if (picker->onPicking) {
                picker->pickingPatch.width = x - picker->pickingPatch.x;
                picker->pickingPatch.height = y - picker->pickingPatch.y;
            } else {
                Vec3b intensity = picker->image.at<Vec3b>(y, x);
                int blue = intensity.val[0];
                int green = intensity.val[1];
                int red = intensity.val[2];
                cout << "R" << red << " G" << green << " B" << blue << endl;
                
                Mat3b hsv;
                cvtColor(Mat3b(intensity), hsv, cv::COLOR_BGR2HSV);
                int hue = hsv.at<Vec3b>(0, 0).val[0];
                int saturation = hsv.at<Vec3b>(0, 0).val[1];
                int value = hsv.at<Vec3b>(0, 0).val[2];
                cout << "H" << hue << " S" << saturation << " V" << value << endl;
            }
            break;
            
        case cv::EVENT_LBUTTONDOWN:
            picker->onPicking = true;
            picker->pickingPatch = cv::Rect(x, y, 0, 0);
            break;
        
        case cv::EVENT_LBUTTONUP:
            picker->onPicking = false;
            if (picker->pickingPatch.width < 0) {
                picker->pickingPatch.x += picker->pickingPatch.width;
                picker->pickingPatch.width *= -1;
            }
            if (picker->pickingPatch.height < 0) {
                picker->pickingPatch.y += picker->pickingPatch.height;
                picker->pickingPatch.height *= -1;
            }
            break;
    }
}

