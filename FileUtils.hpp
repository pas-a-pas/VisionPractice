//
//  Utils.hpp
//  VisionPractice
//
//  Created by Hyunmi on 2019/12/26.
//  Copyright © 2019 Hyunmi. All rights reserved.
//

#ifndef Utils_hpp
#define Utils_hpp

#include <iostream>

using namespace std;

class FileUtils {
public:
    static void listFiles(const std::string& path, std::function<void(const std::string&, const std::string&, void*)> cb, void* params);
};
#endif /* Utils_hpp */
