//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include <iostream>
#include "Fav.h"
#include "Structure.h"

class data8bit{
public:
    int value;
    int vl;
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    
    DEV::Structure* test_str = new DEV::Structure(4, DEV::ColorMode::RGB);
    test_str->setVoxel(1,2,3, 250);
    test_str->setColor(1,2,3, DEV::ColorRGB(100,100,100));
//    test_str->getColor(1,2,3);
//    int test_ = test_str->getColor(1,2,3).r;

    delete test_str;
//    std::cout << "color:" <<  (unsigned int) test_ << std::endl;

//    unsigned char* temp = test_str->getVoxelMap();
//    unsigned char* temp2 = test_str->getVoxelMap();

//    delete test_str;
//    test_str = nullptr;
//    std::cout << test_str->getVoxel(1,2,3) << std::endl;
//    delete test_str;
    test_str = nullptr;
    std::cout << (unsigned int)((unsigned char)257) << std::endl;

//
//    free(ip);
//    int num = 100000;
//    DEV::Structure gust = *new DEV::Structure(4);
//    for(int i=0; i<num; i++){
//        test.push_back(new DEV::Structure(4));
//    }
    
//    int num = 1000;
//    unsigned char test[num][num];
//    std::cout << sizeof(test) << std::endl;
    
//    (test_str.getVoxel(0, 0, 0));
    
//    data8bit* testt;
//    std::cout << sizeof(testt) << std::endl;

    
//    Fav fav_test;
//    fav_test.read("/Users/atsmsmr/Downloads/FAVSample_v1_(1).fav");
//    fav_test.write("//Users/atsmsmr/Downloads/testoshine.xml");
    return 0;
}
