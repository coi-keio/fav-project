//
//  main.cpp
//  fav_converter
//
//  Created by atsmsmr on 2016/01/15.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//
#include <iostream>
#include "../src/Fav.h"
#include "../src/file_io.h"
#include "../src/voxelizer.h"

int main(int argc, char **argv)
{
    
    char* filepath = "/Users/atsmsmr/Downloads/bunny-ascii.stl";
    float voxel_size[3] = {0.8,0.8,0.8};
    
    FabAbleVoxel fav;
    fav.importSTL(filepath);
    fav.voxelize(fav.objects[0], voxel_size);
    
    int total_num = fav.objects[0]->voxel->voxel_num[0]*fav.objects[0]->voxel->voxel_num[1]*fav.objects[0]->voxel->voxel_num[2];
    for(int i=0; i<total_num; i++){
        std::cout << fav.objects[0]->voxel->data[i].state;
    }
    
    return 0;
}
