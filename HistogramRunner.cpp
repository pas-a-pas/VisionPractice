//
//  HistogramRunner.cpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/30.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#include "HistogramRunner.hpp"
#include "ImagePatchPicker.hpp"
#include "HsvHistogram.hpp"
#include "FileUtils.hpp"

#include <opencv2/opencv.hpp>

using namespace cv;

cv::Mat
HistogramRunner::run(const std::string& imageDirectory) {
    cv::Mat histogram;
    
    std::string patchFile("patches.yml");
    pick(imageDirectory, patchFile);
    histogram = analyze(patchFile);
    
    return histogram;
}
    
void
HistogramRunner::onEachImage(const std::string& imageName, void* params) {
    HistogramRunner* runner = (HistogramRunner*) params;
                
    ImagePatchPicker picker(imageName);
    std::vector<cv::Rect> patches = picker.pick();
    if (patches.size() == 0) {
        return;
    }
    runner->fileStorage << "{";
    runner->fileStorage << "imagePath" << imageName;
    runner->fileStorage << "data" << "[";
    for (std::vector<cv::Rect>::iterator it = patches.begin(); it != patches.end(); ++it) {
        cv::Rect patch = *it;
        runner->fileStorage << patch;
    }
    runner->fileStorage << "]";
    runner->fileStorage << "}";
}

void
HistogramRunner::pick(const std::string& imageDirectory, const std::string& patchFile) {
    fileStorage.open(patchFile, cv::FileStorage::WRITE);
    fileStorage << "patches" << "[";
    
    if (FileUtils::isDirectory(imageDirectory)) {
        FileUtils::listFiles(imageDirectory, onEachImage, this);
    } else {
        onEachImage(imageDirectory, this);
    }
    fileStorage << "]";
    fileStorage.release();
}
    
cv::Mat
HistogramRunner::analyze(const std::string& patchFile) {
    cv::Mat result;
    HsvHistogram histogram(64, 64);
    
    fileStorage.open(patchFile, cv::FileStorage::READ);
    cv::FileNode patches = fileStorage["patches"];
    cv::FileNodeIterator it = patches.begin();
    for (; it != patches.end(); it++) {
        std::string imagePath;
        (*it)["imagePath"] >> imagePath;
        cv::Mat image = imread(imagePath);
        
        cv::FileNode data = (*it)["data"];
        cv::FileNodeIterator innerIt = data.begin();
        for (; innerIt != data.end(); innerIt++) {
            cv::Rect patch;
            *innerIt >> patch;
            cv::Mat patchImage = image(patch);
            
            histogram.run(patchImage, result, true, false, false);
        }
    }
    fileStorage.release();

    cv::normalize(result, result, 0, 255, NORM_MINMAX);
    histogram.chart(result);
    
    return result;
}
