//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#pragma once

#include <string>
#include "Metadata.h"

class Vector3D{
public:
    Vector3D(){ x = 0.0; y = 0.0; z = 0.0; };
    float getX(){ return x; };
    float getY(){ return y; };
    float getZ(){ return z; };
    void set(int x_, int y_, int z_){ x=x_; y=y_; z=z_;};
    void setX(int x_){ x = x_; };
    void setY(int y_){ y = y_; };
    void setZ(int z_){ z = z_; };
    
private:
    double x;
    double y;
    double z;
};

class Color{
public:
    int getR();
    int getG();
    int getB();
    int getA();
    void setR(int r);
    void setG(int g);
    void setB(int b);
    void setA(int a);
    
private:
    int color_mode;
    
    int r;
    int g;
    int b;
    int a;
    
    int c;
    int m;
    int y;
    int k;
};

//    class Dimension{
//    public:
//        float getX(){ return x; };
//        float getY(){ return y; };
//        float getZ(){ return z; };
//        void set(int x_, int y_, int z_){ x=x_; y=y_; z=z_;};
//        void setX(int x_){ x = x_; };
//        void setY(int y_){ y = y_; };
//        void setZ(int z_){ z = z_; };
//    private:
//        double x;
//        double y;
//        double z;
//    };
//    
//    class Unit{
//    public:
//        Unit(){ x = 1.0; y = 1.0; z = 1.0; };
//        float getX();
//        float getY();
//        float getZ();
//        void set(int x_, int y_, int z_){ x = x_; y = y_; z = z_;};
//        void setX();
//        void setY();
//        void setZ();
//    private:
//        double x;
//        double y;
//        double z;
//    };


class Grid{
    
public:
    float getOriginX();
    float getOriginY();
    float getOriginZ();
    int   getDimensionX();
    int   getDimensionY();
    int   getDimensionZ();
    float getUnitX();
    float getUnitY();
    float getUnitZ();
    
    void setOrigin();
    void setOriginX();
    void setOriginY();
    void setOriginZ();
    void setDimension();
    void setDimensionX();
    void setDimensionY();
    void setDimensionZ();
    void setUnit();
    void setUnitX();
    void setUnitY();
    void setUnitZ();
    
    Vector3D origin;
    Vector3D dimension;
    Vector3D unit;
    
private:

};

class Structure{
public:
    Structure();
    Structure(int dim_x_, int dim_y_, int dim_z_);
    void initVoxelMap(){ voxel_map = new int[dimension_x*dimension_y*dimension_z]; };
    void initColorMap(std::string color_mode)
    {
        if(color_mode == "RGB") bytes_per_color = 3;
        else if(color_mode == "RGBA") bytes_per_color = 4;
        color_map = new int[dimension_x*dimension_y*dimension_z*bytes_per_color];
    };
    void initLinkMap();
    
    int getBitPerVoxel(){ return bit_per_voxel; };
    std::string getColorMode(){ return color_mode; };
    int getNeighbors(){ return neighbours; };
    
    void setVoxel(int index_, int value_){ voxel_map[index_] = value_; };
    void setColor(int index_, int r_, int g_, int b_){
        setColorR(index_, r_);
        setColorG(index_, r_);
        setColorB(index_, r_);
    };
    void setColor(int index_, int r_, int g_, int b_, int a_);
    void setColorR(int index_, int value_){ color_map[index_*bytes_per_color] = value_; };
    void setColorG(int index_, int value_){ color_map[index_*bytes_per_color + 1] = value_; };
    void setColorB(int index_, int value_){ color_map[index_*bytes_per_color + 2] = value_; };
    void setColorA(int index_, int value_){ color_map[index_*bytes_per_color + 3] = value_; };
    void setLink(int index_, int value_) { link_map[index_]  = value_; };
    
    int* getVoxelMap();
    int* getColorMap();
    int* getLinkMap();
    
    void loadVoxelMap(int* voxel_map_); //grid infoと合わないデータが来た場合はエラーを返す。
    void loadColorMap(int* color_map_);
    void loadLinkMap(int* link_map_);
    
    inline int& getVoxel(int index_) {if (true) return voxel_map[index_];};
    inline int& getVoxel(int x, int y, int z) { return getVoxel(getIndex(x, y, z));};
    inline int& getColorR(int index_){ return color_map[index_*bytes_per_color]; };
    inline int& getColorG(int index_);
    inline int& getColorB(int index_);
    inline int& getColorA(int index_);
    inline int& getColorR(int x, int y, int z);
    inline int& getColorG(int x, int y, int z);
    inline int& getColorB(int x, int y, int z);
    inline int& getColorA(int x, int y, int z);
    inline int& getLink(int index_);
    inline int& getLink(int id_1, int id_2);
    
    int getIndex(int x, int y, int z); //returns the index of the array from xyz indices

private:

    int dimension_x;
    int dimension_y;
    int dimension_z;
    
    int bit_per_voxel;
    int bytes_per_color;
    std::string color_mode;
    int neighbours;
    
    int* voxel_map;
    int* color_map;
    int* color_map_r;
    int* color_map_g;
    int* color_map_b;
    int* color_map_a;
    int* link_map;

//    char* voxel_map;
//    char* color_map;
//    char* link_map;
};

class Object{
    
public:
    Object(){};
    Object(int index_, std::string name_){ index = index_; name = name_; };
    
    int getId();
    std::string getName();
    void setId();
    void setName();
    bool hasMetadata();
    
    int* getVoxelMap();
    int* getColorMap();
    int* getLinkMap();
    
    void setVoxelMap(int* voxel_map_); //grid infoと合わないデータが来た場合はエラーを返す。
    void setColorMap(int* color_map_);
    void setLinkMap(int* link_map_);
    
    Grid* grid;
    Structure* structure;
    Metadata* metadata;
    
private:
    int index;
    std::string name;

    
};
