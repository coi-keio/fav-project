//
//  Fav.h
//  fav_converter
//
//  Created by atsmsmr on 2016/01/15.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//

#ifndef __fav_converter__Fav__
#define __fav_converter__Fav__

#include <iostream>
#include <vector>
#include "object.h"
#include "file_io.h"
#include "voxelizer.h"

class FabAbleVoxel
{

private:
    unsigned int number_of_object;
    
public:
    FabAbleVoxel();
    ~FabAbleVoxel();
    bool importSTL(const char* filepath);
    bool importOBJ(const char* filepath);
    bool importFAV(const char* filepath);
    bool exportFAV();
    bool exportFAV(std::vector<Object*> objects);
    
    bool voxelize(Object* object, float voxel_size[3]);
    bool voxelize(Object* object, int voxel_num[3]);

    void deleteObject(Object* object);
    int  getNumberOfObject();
    
    std::vector<Object*> objects;
};




#endif /* defined(__fav_converter__Fav__) */
