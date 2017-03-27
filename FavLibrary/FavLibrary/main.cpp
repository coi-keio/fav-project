//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include <iostream>
#include "Fav.h"


int main(int argc, const char * argv[]) {
    
    FavLibrary::Fav fav_test;
    fav_test.read("/Users/atsmsmr/Downloads/sample_validation_error.fav");
//    fav_test.read("/Users/atsmsmr/Downloads/testomato200_base64.xml");
    fav_test.write("/Users/atsmsmr/Downloads/testomato200_4.xml", FavLibrary::CompressionMode::base64);
    
    return 0;
}
