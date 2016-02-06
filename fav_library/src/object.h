//
//  object.h
//  fav_converter
//
//  Created by atsmsmr on 2016/01/30.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//

#ifndef __fav_converter__object__
#define __fav_converter__object__

#include <iostream>
#include <vector>
#define _USE_MATH_DEFINES
#include <math.h>
//#include "mesh_data.h"

//struct Vector3f
//{
//    float x;
//    float y;
//    float z;
//};

struct ColorRGBA
{
    float r;
    float g;
    float b;
    float a;
};

class Material
{
private:
public:
    unsigned int index;
    float cte;
};

class Voxel
{
    
private:
    
public:
    Voxel(){};
    ~Voxel(){};
    unsigned int state;
    unsigned int id_material;
    float position[3];
    ColorRGBA color;
};

class VoxelData
{
    
private:

    
public:
    VoxelData(){};
    ~VoxelData(){delete data; data=nullptr;};
    void scale(float magni);
    void expand(float magni);
    void reduct(float magni);

    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void translate(float* destination);
    
    int getNeighbors(int x, int y, int z);
    int getIndex(int x, int y, int z);
    void setPosition();

    unsigned int voxel_num[3];
    float voxel_size[3];
    float voxel_origin[3];
    Voxel* data;
};

struct Box
{
    float position[3];
    float length[3];
    float max_length;
};

struct BoundingBox
{
    float position[3];
    float length[3];
    float max_length;
};

class MeshData
{
private:
    
    float* getCenter();
    
public:
	MeshData(){};
	~MeshData(){
        delete vertices;
        delete normals;
        delete faces;
    };
    
    void fillHole();
    void scale(float magni);
    void rotateX(float angle);
    void rotateY(float angle);
    void rotateZ(float angle);
    void translate(float* destination);
    void translateToOrigin();
    void setAABB();
    
    float *vertices;
    float *normals;
    unsigned int *faces;
    unsigned int number_of_vertices;
    unsigned int number_of_faces;
    float origin[3];
    BoundingBox bounding_box;
};

class Object
{
    
private:
    
    
public:
    Object(){};
    ~Object(){
        delete mesh; mesh = nullptr;
        delete voxel; voxel = nullptr;
    }
    void deleteMesh();
    void deleteVoxel();
    
    MeshData* mesh;
    VoxelData* voxel;
    bool has_mesh;
    bool has_voxel;
    
    std::vector<Material*> mateial_list;
    std::vector<Voxel*> voxel_list;
};

#endif /* defined(__fav_converter__object__) */
