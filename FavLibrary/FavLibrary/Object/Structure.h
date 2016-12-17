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
#include "../Primitive/Point3D.h"
#include "../Primitive/Color.h"

class Grid;

enum class BitPerVoxel{
    FourBit,
    EightBit,
    SixteenBit,
};

enum class Compression{
    None,
    Zlib,
    Base64,
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

//class ColorRGB {
//public:
//    ColorRGB(unsigned char r_, unsigned char g_, unsigned char b_){
//        r = r_;
//        g = g_;
//        b = b_;
//    };
//    unsigned char r;
//    unsigned char g;
//    unsigned char b;
//};
//
//class ColorRGBA {
//public:
//    ColorRGBA(unsigned char r_, unsigned char g_, unsigned char b_, unsigned a_){
//        r = r_;
//        g = g_;
//        b = b_;
//        a = a_;
//    };
//    unsigned char r;
//    unsigned char g;
//    unsigned char b;
//    unsigned char a;
//};
//
//class ColorCMYK {
//public:
//    ColorCMYK(unsigned char c_, unsigned char m_, unsigned char y_, unsigned char k_){
//        c = c_;
//        m = m_;
//        y = y_;
//        k = k_;
//    };
//    unsigned char c;
//    unsigned char m;
//    unsigned char y;
//    unsigned char k;
//};
//
//class ColorGrayScale{
//public:
//    ColorGrayScale(unsigned char k_){
//        k = k_;
//    };
//    unsigned char k;
//};
//
//class ColorGrayScale16 {
//public:
//    ColorGrayScale16(unsigned short k_){
//        k = k_;
//    };
//    unsigned short k;
//};


class Structure{
public:
    Structure(Grid* grid_);
    Structure(int bit_per_voxel_);
    Structure(int bit_per_voxel_, ColorMode color_mode_);
    ~Structure();
    void setCompression(Compression compression_);
    Compression getCompression();
    
    void initVoxelMap();
    void setBitPerVoxel(int bit_per_voxel_){ bit_per_voxel = bit_per_voxel_; };
    void setVoxel(int index_, int value_);
    void setVoxel(Point3D p_, int value_);
    void setVoxel(int x_, int y_, int z_, int value_);
    int getBitPerVoxel(){ return bit_per_voxel; };
    int getVoxel(int index_){ return voxel_map->getVoxel(index_); };
    int getVoxel(Point3D p_);
    int getVoxel(int x_, int y_, int z_);
    
    void initColorMap();
    void initColorMap(ColorMode color_mode_);
    void setColorMode(ColorMode color_mode_);
    void setColor(Point3D p_, class ColorRGB color_);
    void setColor(Point3D p_, class ColorRGBA color_);
    void setColor(Point3D p_, class ColorCMYK color_);
    void setColor(Point3D p_, class ColorGrayScale color_);
    void setColor(Point3D p_, class ColorGrayScale16 color_);
    void setColor(int x_, int y_, int z_, class ColorRGB color_);
    void setColor(int x_, int y_, int z_, class ColorRGBA color_);
    void setColor(int x_, int y_, int z_, class ColorCMYK color_);
    void setColor(int x_, int y_, int z_, class ColorGrayscale color_);
    void setColor(int x_, int y_, int z_, class ColorGrayscale16 color_);
    void setColorRGB(Point3D p_, int r_, int g_, int b_);
    void setColorRGBA(Point3D p_, int r_, int g_, int b_, int a_);
    void setColorCMYK(Point3D p_, int c_, int m_, int cy_, int k_);
    void setColortGrayScale(Point3D p_, int k);
    void setColortGrayScale16(Point3D p_, int k);
    void setColorAlpha(Point3D p_, int a_);
    void setColorRGB(int x_, int y_, int z_, int r_, int g_, int b_);
    void setColorRGBA(int x_, int y_, int z_, int r_, int g_, int b_, int a_);
    void setColorCMYK(int x_, int y_, int z_, int c_, int m_, int cy_, int k_);
    void setColorGrayScale(int x_, int y_, int z_, int k);
    void setColorGrayScale16(int x_, int y_, int z_, int k);
    void setColorAlpha(int x_, int y_, int z_, int a_);
    
    int getColorRed(Point3D p_);
    int getColorGreen(Point3D p_);
    int getColorBlue(Point3D p_);
    int getColorCyan(Point3D p_);
    int getColorMagenta(Point3D p_);
    int getColorYellow(Point3D p_);
    int getColorKeyPlate(Point3D p_);
    int getColorGrayScale(Point3D p_);
    int getColorGrayScale16(Point3D p_);
    int getColorAlpha(Point3D p_);
    int getColorRed(int x_, int y_, int z_){ return color_map[getIndex(x_, y_, z_)]; };
    int getColorGreen(int x_, int y_, int z_);
    int getColorBlue(int x_, int y_, int z_);
    int getColorCyan(int x_, int y_, int z_);
    int getColorMagenta(int x_, int y_, int z_);
    int getColorYellow(int x_, int y_, int z_);
    int getColorKeyPlate(int x_, int y_, int z_);
    int getColorGrayScale(int x_, int y_, int z_);
    int getColorGrayScale16(int x_, int y_, int z_);
    int getColorAlpha(int x_, int y_, int z_);
    
    ColorMode getColorMode(){ return color_mode; };
    ColorRGB getColorRGB(int x_, int y_, int z_);
    ColorCMYK getColorCMYK(int x_, int y_, int z_);
    
    int getDimensionX();
    int getDimensionY();
    int getDimensionZ();
    
    //        ColorGrayScale getColorGrayScale(int x_, int y_, int z_);
    //        ColorGrayScale16 getColorGrayScale16(int x_, int y_, int z_);
    
    //        // Link map is under development
    //        void initLinkMap();
    //        unsigned int getLink(Point3D p1_, Point3D p2_);
    //        unsigned int getLink(int x1_, int y1_, int z1_, int x2_, int y2_, int z2_);
    //        int getNeighbors(){ return neighbours; };
    
    Grid* grid;
    
private:
    void changeColorMapToRGB(){
        if(color_mode == ColorMode::RGB){
            return;
        }else if(color_mode == ColorMode::RGBA){
            
        }
    };
    //        void changeColorMapToRGBA();
    void changeColorMapToCMYK();
    void changeColorMatToGrayScale();
    void changeColorMatToGrayScale16();
    
    int getIndex(int x, int y, int z); //returns the index of the array from xyz indices
    
    int bit_per_voxel;
    ColorMode color_mode;
    Compression compression;
    int number_of_voxels;
    
    VoxelMap<unsigned char>* voxel_map; //default voxel map
    VoxelMap<unsigned short>* voxel_map_16bit;// for 16bit voxel map
    unsigned char* alpha_map;
    unsigned char* color_map;
    unsigned short* color_map_16bit;
    
    //        // Link map is under development
    //        float* link_map;
    //        int neighbours;
};
#endif /* defined(__FavLibrary__Structure__) */
