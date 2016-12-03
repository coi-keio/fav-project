//
//  Structure.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/02.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__Structure__
#define __FavLibrary__Structure__

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

#include "Object.h"

namespace DEV {
    
    class Point{
        
    };
    
//    class Color{
//        
//    };
    
    class data8bit{
    public:
        data8bit(unsigned char value_){
            value = value_;
            std::cout << sizeof(value) << std::endl;
        };
        unsigned char value;
    };
    
    struct data16bit{
        data16bit(unsigned short value_){
            value = value_;
        };
        unsigned short value;
    };
    
    class VoxelData{
    public:
        VoxelData();
        VoxelData(void* data_ptr_){
            data = data_ptr_;
        };
        void setVoxelData(void* value_);
        
        void* data; //4bit,8bitの場合はunsigned char型, 16bitの場合はunsigned short型
        Color* color;
        int* link;
    };
    
    enum PlaneType {
        XY,
        YZ,
        ZX,
    };
    
    enum ColorMode{
        GrayScale,
        GrayScale16,
        RGB,
        RGBA,
        CMYK,
    };
    
    template<typename tVoxelMapType = unsigned char>
    class VoxelMap{
        
    public:
        VoxelMap(int size){
            data = new tVoxelMapType[size];
        };
        
        void initVoxelMap(){
            data = new tVoxelMapType[number_of_voxels];
            for(int i=0; i<number_of_voxels; ++i){
                data[i] = (tVoxelMapType)20;
            }
        };
        
        void setVoxel(int index_, int value_){
            data[index_] = (tVoxelMapType)value_;
        };
        
        unsigned int getVoxel(int index_){
            return (unsigned int)data[index_];
        }

        unsigned int number_of_voxels;
        unsigned short bit_per_voxel;
        tVoxelMapType* data;
    };
    
    class Color{
    public:
        Color(unsigned char r_, unsigned char g_, unsigned char b_){
            r = r_;
            g = g_;
            b = b_;
        };
        
        Color(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_){
            r = r_;
            g = g_;
            b = b_;
            a = a_;
        };
        
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
    };
    
    
    class Structure{
    public:
        struct VoxelMap8bit{
            VoxelMap8bit(int num){
                data = new unsigned char[num];
            };
            unsigned char* data;
        };
        struct VoxelMap16bit{
            VoxelMap16bit(int num){
                data = new unsigned short[num];
            };
            unsigned short* data;
        };
        typedef VoxelMap8bit VoxelType;
        Structure();
        ~Structure(){
            delete[] voxel_map;
            voxel_map = nullptr;
        }
        
        
        Structure(int bit_per_voxel_);
        Structure(int bit_per_voxel_, ColorMode color_mode_);
        
        void setVoxel(Point p_, int value_);
        void setVoxel(int x_, int y_, int z_, int value_);
        
        int getVoxel(Point p_);
        int getVoxel(int x_, int y_, int z_);
        
        unsigned char* getColorMap8bit();
        unsigned short* getColorMap16bit();
        unsigned char* getColorPlane8bit(PlaneType PLANE_TYPE, int layer);
        unsigned short* getColorPlane16bit(PlaneType PLANE_TYPE, int layer);
//        Color getColor(int x, int y, int z);
        
        void setColor(int x_, int y_, int z_, Color color_){
            int index = getIndex(x_, y_, z_);
            color_map[index] = color_.r;
        };
        
        Color* getColor(int x_, int y_, int z_){
            int index = getIndex(x_, y_, z_);
            return new Color(color_map[index], 0, 0);
        };
        
        unsigned char* getLinkMap8bit();
        unsigned short* getLinkMap16bit();
        unsigned char* getLinkPlane8bit(PlaneType PLANE_TYPE, int layer);
        unsigned short* getLinkPlane16bit(PlaneType PLANE_TYPE, int layer);
        unsigned int getLink(Point p1_, Point p2_);
        unsigned int getLink(int x1_, int y1_, int z1_, int x2_, int y2_, int z2_);
        
        int getBitPerVoxel(){ return bit_per_voxel; };
        ColorMode getColorMode(){ return color_mode; };
        int getNeighbors(){ return neighbours; };
        
        
        //    void initVoxelMap(){ voxel_map = new int[dimension_x*dimension_y*dimension_z]; };
        //    void initColorMap(std::string color_mode)
        //    {
        //        if(color_mode == "RGB") bytes_per_color = 3;
        //        else if(color_mode == "RGBA") bytes_per_color = 4;
        //        color_map = new int[dimension_x*dimension_y*dimension_z*bytes_per_color];
        //    };
        //    void initLinkMap();
        //
        //    int getBitPerVoxel(){ return bit_per_voxel; };
        //    std::string getColorMode(){ return color_mode; };
        //    int getNeighbors(){ return neighbours; };
        //
        //    void setVoxel(int index_, int value_){ voxel_map[index_] = value_; };
        //    void setColor(int index_, int r_, int g_, int b_){
        //        setColorR(index_, r_);
        //        setColorG(index_, r_);
        //        setColorB(index_, r_);
        //    };
        //    void setColor(int index_, int r_, int g_, int b_, int a_);
        //    void setColorR(int index_, int value_){ color_map[index_*bytes_per_color] = value_; };
        //    void setColorG(int index_, int value_){ color_map[index_*bytes_per_color + 1] = value_; };
        //    void setColorB(int index_, int value_){ color_map[index_*bytes_per_color + 2] = value_; };
        //    void setColorA(int index_, int value_){ color_map[index_*bytes_per_color + 3] = value_; };
        //    void setLink(int index_, int value_) { link_map[index_]  = value_; };
        //
        //    int* getVoxelMap();
        //    int* getColorMap();
        //    int* getLinkMap();
        //
        //    void loadVoxelMap(int* voxel_map_); //grid infoと合わないデータが来た場合はエラーを返す。
        //    void loadColorMap(int* color_map_);
        //    void loadLinkMap(int* link_map_);
        //
        //    inline int& getVoxel(int index_) {if (true) return voxel_map[index_];};
        //    inline int& getVoxel(int x, int y, int z) { return getVoxel(getIndex(x, y, z));};
        //    inline int& getColorR(int index_){ return color_map[index_*bytes_per_color]; };
        //    inline int& getColorG(int index_);
        //    inline int& getColorB(int index_);
        //    inline int& getColorA(int index_);
        //    inline int& getColorR(int x, int y, int z);
        //    inline int& getColorG(int x, int y, int z);
        //    inline int& getColorB(int x, int y, int z);
        //    inline int& getColorA(int x, int y, int z);
        //    inline int& getLink(int index_);
        //    inline int& getLink(int id_1, int id_2);
        //    
        //    int getIndex(int x, int y, int z); //returns the index of the array from xyz indices
        
    private:
        int getIndex(int x, int y, int z); //returns the index of the array from xyz indices
        
        Grid* grid;
        int bit_per_voxel;
        ColorMode color_mode;
        int neighbours;
        int number_of_voxels;
        
        VoxelMap<unsigned char>* voxel_map; //default voxel map
        VoxelMap<unsigned short>* voxel_map_16bit;// for 16bit voxel map
        
        unsigned char* voxel_map_8bit;
//        unsigned short* voxel_map_16bit;
        unsigned char* color_map;
        unsigned short* color_map_16bit;
        float* link_map;
        
    };
}
#endif /* defined(__FavLibrary__Structure__) */
