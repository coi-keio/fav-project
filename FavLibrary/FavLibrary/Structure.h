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
    
    enum ColorMode{
        None,
        GrayScale,
        GrayScale16,
        RGB,
        RGBA,
        CMYK,
    };
    
    template<typename tVoxelMapType>
    class VoxelMap{
        
    public:
        VoxelMap(int size);
        void init();
        void setVoxel(int index_, int value_);
        tVoxelMapType getVoxel(int index_);
        
    private:
        unsigned int number_of_voxels;
        tVoxelMapType* data;
    };
    
    class Color{
    public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        unsigned char a;
        
        unsigned char c;
        unsigned char m;
        unsigned char y;
        unsigned char k;
        
        unsigned char k1;
        unsigned short k2;
    };
    
    class ColorRGB : public Color{
    public:
        ColorRGB(unsigned char r_, unsigned char g_, unsigned char b_){
            r = r_;
            g = g_;
            b = b_;
        };
        unsigned char r;
        unsigned char g;
        unsigned char b;
    };
    
    class ColorRGBA : public Color{
    public:
        ColorRGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned a_){
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
    
    class ColorCMYK : private Color{
    public:
        ColorCMYK(unsigned char c_, unsigned char m_, unsigned char y_, unsigned char k_){
            c = c_;
            m = m_;
            y = y_;
            k = k_;
        };
        unsigned char c;
        unsigned char m;
        unsigned char y;
        unsigned char k;
        
        void getC();
        void getM();
    };
    
    class ColorGrayScale : public Color{
    public:
        ColorGrayScale(unsigned char y_){
            y = y_;
        };
        unsigned char y;
    };
    
    class ColorGrayScale16 : public Color{
    public:
        ColorGrayScale16(unsigned short y_){
            y = y_;
        };
        unsigned short y;
    };
    
    
    class Structure{
    public:
        Structure();
        Structure(int bit_per_voxel_);
        Structure(int bit_per_voxel_, ColorMode color_mode_);
        ~Structure();
        
        void initVoxelMap();
        void setBitPerVoxel(int bit_per_voxel_);
        void setVoxel(Point p_, int value_);
        void setVoxel(int x_, int y_, int z_, int value_);
        int getVoxel(Point p_);
        int getVoxel(int x_, int y_, int z_);
        
        void initColorMap();
        void setColorMode(ColorMode color_mode_);
        void setColor(Point p_, class ColorRGB color_);
        void setColor(Point p_, class ColorRGBA color_);
        void setColor(Point p_, class ColorCMYK color_);
        void setColor(Point p_, class ColorGrayScale color_);
        void setColor(Point p_, class ColorGrayScale16 color_);
        void setColor(int x_, int y_, int z_, class ColorRGB color_);
        void setColor(int x_, int y_, int z_, class ColorRGBA color_);
        void setColor(int x_, int y_, int z_, class ColorCMYK color_);
        void setColor(int x_, int y_, int z_, class ColorGrayScale color_);
        void setColor(int x_, int y_, int z_, class ColorGrayScale16 color_);
        auto getColor(int x_, int y_, int z_);
        ColorRGBA getColorRGBA(int x_, int y_, int z_);
        ColorCMYK getColorCMYK(int x_, int y_, int z_);
        ColorGrayScale getColorGrayScale(int x_, int y_, int z_);
        ColorGrayScale16 getColorGrayScale16(int x_, int y_, int z_);

        void initLinkMap();
        unsigned int getLink(Point p1_, Point p2_);
        unsigned int getLink(int x1_, int y1_, int z1_, int x2_, int y2_, int z2_);
        
        int getBitPerVoxel(){ return bit_per_voxel; };
        ColorMode getColorMode(){ return color_mode; };
        int getNeighbors(){ return neighbours; };
        
        
    private:
        int getIndex(int x, int y, int z); //returns the index of the array from xyz indices
        
        Grid* grid;
        int bit_per_voxel;
        ColorMode color_mode;
        int neighbours;
        int number_of_voxels;
        
        VoxelMap<unsigned char>* voxel_map; //default voxel map
        VoxelMap<unsigned short>* voxel_map_16bit;// for 16bit voxel map
        
        unsigned char* color_map;
        unsigned short* color_map_16bit;
        
        float* link_map;
    };
}
#endif /* defined(__FavLibrary__Structure__) */
