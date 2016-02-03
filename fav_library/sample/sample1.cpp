//
//  main.cpp
//  fav_converter
//
//  Created by atsmsmr on 2016/01/15.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//
#include <iostream>
//#include <GLUT/glut.h>
#include "../src/Fav.h"
#include "../src/file_io.h"
#include "../src/voxelizer.h"
#include "Viewer.h"

float g_angle = 0.0f;
int g_prevX = -1;

int zoom = -100;
int slice = 0;
bool is_voxel = false;
bool is_mesh = true;
bool is_path = false;

int main(int argc, char **argv)
{
    
    char* filepath = "/Users/atsmsmr/Downloads/bunny-ascii.stl";
    
    float voxel_size[3] = {1.2,2.02,2.02};
    int resolution[3] = {100,100,100};
    
    FabAbleVoxel fav;
    if(fav.importSTL(filepath)){
//        fav.objects[0]->mesh->translateToOrigin();
        fav.voxelize(fav.objects[0], resolution);
    }
    
    Viewer viewer;
    viewer.setupGlut(&fav);

    // set continuous-transition color
    for(int z=0; z<fav.objects[0]->voxel->voxel_num[2]; z++){
        for(int y=0; y<fav.objects[0]->voxel->voxel_num[1]; y++){
            for(int x=0; x<fav.objects[0]->voxel->voxel_num[0]; x++){
                int index = viewer.getIndex(x,y,z);
                fav.objects[0]->voxel->data[index].color.r = (float)x/fav.objects[0]->voxel->voxel_num[0];
                fav.objects[0]->voxel->data[index].color.g = (float)y/fav.objects[0]->voxel->voxel_num[1];
                fav.objects[0]->voxel->data[index].color.b = (float)z/fav.objects[0]->voxel->voxel_num[2];
            }
        }
    }
    
    viewer.run();

    return 0;
}
