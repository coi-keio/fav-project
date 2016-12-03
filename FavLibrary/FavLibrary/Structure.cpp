//
//  Structure.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/02.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "Structure.h"
using namespace DEV;


DEV::Structure::Structure(int bit_per_voxel_){
    
    bit_per_voxel = bit_per_voxel_;
    number_of_voxels = 1000;
    
    if(bit_per_voxel == 4 || bit_per_voxel == 8) {
        voxel_map = new VoxelMap<unsigned char>(number_of_voxels);
        voxel_map->initVoxelMap();
    }else if(bit_per_voxel == 16){
        voxel_map_16bit = new VoxelMap<unsigned short>(number_of_voxels);
        voxel_map_16bit->initVoxelMap();
    }
    
};

DEV::Structure::Structure(int bit_per_voxel_, ColorMode color_mode_){
    
    bit_per_voxel = bit_per_voxel_;
    color_mode = color_mode_;
    number_of_voxels = 1000;
    
    if(bit_per_voxel == 4 || bit_per_voxel == 8) {
        voxel_map = new VoxelMap<unsigned char>(number_of_voxels);
        voxel_map->initVoxelMap();
    }else if(bit_per_voxel == 16){
        voxel_map_16bit = new VoxelMap<unsigned short>(number_of_voxels);
        voxel_map_16bit->initVoxelMap();
    }
    
    if(color_mode == ColorMode::RGB) color_map = new unsigned char[number_of_voxels*3];
    else if(color_mode == ColorMode::RGBA) color_map = new unsigned char[number_of_voxels*4];
    else if(color_mode == ColorMode::CMYK) color_map = new unsigned char[number_of_voxels*4];
    else if(color_mode == ColorMode::GrayScale) color_map = new unsigned char[number_of_voxels];
    else if(color_mode == ColorMode::GrayScale16) color_map_16bit = new unsigned short[number_of_voxels];
};


void DEV::Structure::setVoxel(Point p_, int value_){};
void DEV::Structure::setVoxel(int x_, int y_, int z_, int value_){
    
    int index = getIndex(x_, y_, z_);
    
    if(bit_per_voxel == 4 || bit_per_voxel == 8) voxel_map->setVoxel(index, value_);
    else if(bit_per_voxel == 16) voxel_map_16bit->setVoxel(index, value_);
    
};

//int DEV::Structure::getVoxel(Point p_){};
int DEV::Structure::getVoxel(int x_, int y_, int z_){
    
    int index = getIndex(x_, y_, z_);
    int value;
    if(bit_per_voxel == 4 || bit_per_voxel == 8) value = voxel_map->getVoxel(index);
    else if(bit_per_voxel == 16) value = voxel_map_16bit->getVoxel(index);
    
    return value;
};

int DEV::Structure::getIndex(int x_, int y_, int z_){
    
    return 0;
//    return x_ + grid->dimension.getX() * y_ + grid->dimension.getX() * grid->dimension.getY() * z_;
}