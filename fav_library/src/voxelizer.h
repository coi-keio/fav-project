//
//  voxelize.h
//  Voxelizer
//
//  Created by atsmsmr on 2015/10/31.
//  Copyright (c) 2015年 Atsushi Masumori. All rights reserved.
//

#ifndef __Voxelizer__voxelize__
#define __Voxelizer__voxelize__

//#include <stdlib.h>
//#define NOMINMAX
//#include <windows.h>

#include<iostream>
#include<fstream>
#include <vector>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>


class Voxelizer
{
private:
    float* getAABB(float* vertices, int num_vertices);
    float* getTriAABB(float vertices[3][3]);
    float* getTargetIndexInAABB(float* aabb, float* start_position, float* voxel_size);
    void fillInside();
    
    // Define states of cells
    unsigned static const int Empty_Cell = 0;
    unsigned static const int Collision_Cell = 1;
    unsigned static const int Surface_Cell = 2;
    unsigned static const int Inner_Cell = 3;
    unsigned static const int Pre_Process_Cell = 4;
    unsigned static const int Processing_Cell = 5;
    unsigned static const int Processed_Cell = 6;
    
public:
	Voxelizer();
	~Voxelizer();
    int* voxelize(float* vertices, int num_vertices, float num_voxel[3], bool is_fill_inside = false);
    int getIndex(int x, int y, int z);

    int voxel_num[3];
    float voxel_origin[3];
    float voxel_size[3];
    int* voxel_data;
};


class collision_detection
{
private:
    void SUB(float* dest, float v1[3], float v2[3]);
    void CROSS(float* dest, float v1[3], float v2[3]);
    float DOT(float v1[3], float v2[3]);
    
    bool AXISTEST_X01(float a, float b, float fa, float fb);
    bool AXISTEST_X2(float a, float b, float fa, float fb);
    bool AXISTEST_Y02(float a, float b, float fa, float fb);
    bool AXISTEST_Y1(float a, float b, float fa, float fb);
    bool AXISTEST_Z12(float a, float b, float fa, float fb);
    bool AXISTEST_Z0(float a, float b, float fa, float fb);
    
    bool planeBoxOverlap(float normal[3], float vert[3], float maxbox[3]);
    
    float v0[3],v1[3],v2[3];
    float min,max,p0,p1,p2,rad,fex,fey,fez;		// -NJMP- "d" local variable removed
    float normal[3],e0[3],e1[3],e2[3];
    float boxhalfsize[3];
    
public:
    collision_detection();
    ~collision_detection();
    bool is_collision(float* boxcenter, float* unit_voxel, float triverts[3][3]);
};


#endif /* defined(__Voxelizer__voxelize__) */
