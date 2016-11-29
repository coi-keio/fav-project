//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include "Object.h"


Structure::Structure(int dim_x_, int dim_y_, int dim_z_){
    dimension_x = dim_x_;
    dimension_y = dim_y_;
    dimension_z = dim_z_;
}

int Structure::getIndex(int x_, int y_, int z_){

    return x_ + dimension_x * y_ + dimension_x * dimension_y * z_;

}