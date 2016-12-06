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
    
    Fav fav_test;
    fav_test.read("/Users/atsmsmr/Downloads/FAVSample_v1_(1).fav");
    fav_test.write("/Users/atsmsmr/Downloads/testomato200.xml", "1.0");
    return 0;
}
