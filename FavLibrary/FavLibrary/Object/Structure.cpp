//
//  Structure.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/02.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "Structure.h"
#include "Object.h"

using namespace DEV;

template <typename tVoxelMapType>
DEV::VoxelMap<tVoxelMapType>::VoxelMap(int size){
    number_of_voxels = size;
    data = new tVoxelMapType[size];
};

template <typename tVoxelMapType>
void DEV::VoxelMap<tVoxelMapType>::init(){
    data = new tVoxelMapType[number_of_voxels];
    for(int i=0; i<number_of_voxels; ++i){
        data[i] = (tVoxelMapType)20;
    }
};

template <typename tVoxelMapType>
void DEV::VoxelMap<tVoxelMapType>::setVoxel(int index_, int value_){
    data[index_] = (tVoxelMapType)value_;
};

template <typename tVoxelMapType>
tVoxelMapType DEV::VoxelMap<tVoxelMapType>::getVoxel(int index_){
    return data[index_];
}

DEV::Structure::Structure(Grida* grid_){
    grid = grid_;
    number_of_voxels = grid->dimension.getX() * grid->dimension.getY() * grid->dimension.getZ();
}

DEV::Structure::Structure(int bit_per_voxel_){
    
    bit_per_voxel = bit_per_voxel_;
    number_of_voxels = 100000;
    
    initVoxelMap();
    color_mode = DEV::ColorMode::None;
    
};

DEV::Structure::Structure(int bit_per_voxel_, ColorMode color_mode_){
    
    bit_per_voxel = bit_per_voxel_;
    color_mode = color_mode_;
    number_of_voxels = 100000000;
    
    initVoxelMap();
    initColorMap();
    
};

DEV::Structure::~Structure(){
    delete[] voxel_map;
    voxel_map = nullptr;
}

void DEV::Structure::initVoxelMap(){
    
    if(bit_per_voxel == 4 || bit_per_voxel == 8) {
        voxel_map = new VoxelMap<unsigned char>(number_of_voxels);
        voxel_map->init();
    }else if(bit_per_voxel == 16){
        voxel_map_16bit = new VoxelMap<unsigned short>(number_of_voxels);
        voxel_map_16bit->init();
    }

}

void DEV::Structure::initColorMap(ColorMode color_mode_){
    color_mode = color_mode_;
    initColorMap();
}

void DEV::Structure::initColorMap(){
    
    if(color_mode == ColorMode::RGB) color_map = new unsigned char[number_of_voxels*3];
    else if(color_mode == ColorMode::RGBA) {color_map = new unsigned char[number_of_voxels*3]; alpha_map = new unsigned char[number_of_voxels];}
    else if(color_mode == ColorMode::CMYK) color_map = new unsigned char[number_of_voxels*4];
    else if(color_mode == ColorMode::GrayScale) color_map = new unsigned char[number_of_voxels];
    else if(color_mode == ColorMode::GrayScale16) color_map_16bit = new unsigned short[number_of_voxels];

}

void DEV::Structure::setVoxel(int index_, int value_){
    voxel_map->setVoxel(index_, value_);
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
    if(bit_per_voxel == 4 || bit_per_voxel == 8) {
        value = voxel_map->getVoxel(index);
    }
    else if(bit_per_voxel == 16) value = voxel_map_16bit->getVoxel(index);
    
    return (int)value;
};

void DEV::Structure::setColor(int x_, int y_, int z_, class ColorRGB color_){
    int index = getIndex(x_, y_, z_);
    if(color_mode != DEV::ColorMode::RGB){
        std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
    }else{
        color_map[index*3]   = color_.r;
        color_map[index*3+1] = color_.g;
        color_map[index*3+2] = color_.b;
    }
};

void DEV::Structure::setColor(int x_, int y_, int z_, class ColorRGBA color_){
    int index = getIndex(x_, y_, z_);
    if(color_mode != DEV::ColorMode::RGBA){
        std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
    }else{
        color_map[index*4]   = color_.r;
        color_map[index*4+1] = color_.g;
        color_map[index*4+2] = color_.b;
        color_map[index*4+3] = color_.a;
    }
};

void DEV::Structure::setColor(int x_, int y_, int z_, class ColorCMYK color_){
    int index = getIndex(x_, y_, z_);
    if(color_mode != DEV::ColorMode::CMYK){
        std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
    }else{
        color_map[index*4]   = color_.c;
        color_map[index*4+1] = color_.m;
        color_map[index*4+2] = color_.y;
        color_map[index*4+3] = color_.k;
    }
};

void DEV::Structure::setColor(int x_, int y_, int z_, class ColorGrayScale color_){
    int index = getIndex(x_, y_, z_);
    if(color_mode != DEV::ColorMode::GrayScale){
        std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
    }else{
        color_map[index]   = color_.k;
    }
};

void DEV::Structure::setColor(int x_, int y_, int z_, class ColorGrayScale16 color_){
    int index = getIndex(x_, y_, z_);
    if(color_mode != DEV::ColorMode::GrayScale16){
        std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
    }else{
        color_map[index]   = color_.k;
    }
};


DEV::ColorRGB DEV::Structure::getColorRGB(int x_, int y_, int z_){
    int index = getIndex(x_, y_, z_);
    return ColorRGB(color_map[index*3], color_map[index*3+1], color_map[index*3+2]);
};

//DEV::ColorRGBA DEV::Structure::getColorRGBA(int x_, int y_, int z_){
//    int index = getIndex(x_, y_, z_);
//    return ColorRGBA(color_map[index*4], color_map[index*4+1], color_map[index*4+2], color_map[index*4+3]);
//};

DEV::ColorCMYK DEV::Structure::getColorCMYK(int x_, int y_, int z_){
    int index = getIndex(x_, y_, z_);
    return ColorCMYK(color_map[index*4], color_map[index*4+1], color_map[index*4+2], color_map[index*4+3]);
};

//DEV::ColorGrayScale DEV::Structure::getColorGrayScale(int x_, int y_, int z_){
//    int index = getIndex(x_, y_, z_);
//    return ColorGrayScale(color_map[index]);
//};

int DEV::Structure::getIndex(int x_, int y_, int z_){
    int ret = x_ + grid->dimension.getX() * y_ + grid->dimension.getX() * grid->dimension.getY() * z_;
    return ret;
//    return x_ + grid->dimension.getX() * y_ + grid->dimension.getX() * grid->dimension.getY() * z_;
}