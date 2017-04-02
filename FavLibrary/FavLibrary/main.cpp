//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include <iostream>
#include "Fav.h"
#include "./Object/Structure.h"
#include "./Object/Object.h"
#include "./Object/Grid.h"
#include "./Palette/Palette.h"
#include "./Palette/Material.h"
#include "./Palette/Geometry.h"

int main(int argc, const char * argv[]) {

//    FavLibrary::Structure* structure = new FavLibrary::Structure;
//    FavLibrary::Object* object = new FavLibrary::Object;
//    FavLibrary::Palette* pal = new FavLibrary::Palette;
//    FavLibrary::Grid* grid = new FavLibrary::Grid;
//    FavLibrary::Material* mat = new FavLibrary::Material;
//    FavLibrary::Geometry* geo = new FavLibrary::Geometry;
//    
////    pal->addGeometry(FavLibrary::Geometry(1,"test"));
//    
//    delete structure;
//    delete object;
//    delete pal;
//    delete grid;
//    delete mat;
//    delete geo;
    
    FavLibrary::Fav fav_test;
    fav_test.read("/Users/atsmsmr/Downloads/sample_validation_error.fav");
//    fav_test.read("/Users/atsmsmr/Downloads/testomato200_base64.xml");
    fav_test.write("/Users/atsmsmr/Downloads/testomato200_4.xml", FavLibrary::CompressionMode::none);
    
    return 0;
}
