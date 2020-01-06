//
//  Utils.cpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/26.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#include "FileUtils.hpp"

#include <string>
#include <functional>
#include <dirent.h>

void
FileUtils::listFiles(const std::string& path, std::function<void(const std::string&, void*)> cb, void* params) {
    if (auto dir = opendir(path.c_str())) {
        while (auto f = readdir(dir)) {
            if (!f->d_name || f->d_name[0] == '.') continue;
            if (f->d_type == DT_DIR)
                listFiles(path + f->d_name + "/", cb, params);

            if (f->d_type == DT_REG)
                cb(path + f->d_name, params);
        }
        closedir(dir);
    }
}

bool
FileUtils::isDirectory(const std::string& path) {
    bool ret = false;
    if (auto dir = opendir(path.c_str())) {
        ret = true;
        closedir(dir);
    }
    
    return ret;
}
