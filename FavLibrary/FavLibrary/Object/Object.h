//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#pragma once

#include <string>
#include "Structure.h"
#include "Grid.h"
#include "../Metadata.h"
#include "../Primitive/FavPrimitive.h"

class Object : public FavPrimitive, MetadataObject
{

public:
	Object() { identifier = ++counter; };
	Object(std::string name_) 
	{
		Object();
		name = name_;
	};
    
    void setStructure(Structure* structure_new_){ structure = structure_new_; };

	/// この辺はStructureのメソッド呼ぶだけのショートカット
	//int* getVoxelMap();
	//int* getColorMap();
	//int* getLinkMap();

	//void setVoxelMap(int* voxel_map_); //grid infoと合わないデータが来た場合はエラーを返す。
	//void setColorMap(int* color_map_);
	//void setLinkMap(int* link_map_);
    
    Grid* grid;
    Structure* structure;
private:
    static unsigned int counter;

};

/// Structureの実態はStructure.cpp/.h で定義されているから，ここは消していい遺産？
//
//class Structure{
//public:
//    Structure();
//    Structure(int dim_x_, int dim_y_, int dim_z_);
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
//
//private:
//
//    int dimension_x;
//    int dimension_y;
//    int dimension_z;
//    
//    int bit_per_voxel;
//    int bytes_per_color;
//    std::string color_mode;
//    int neighbours;
//    
//    int* voxel_map;
//    int* color_map;
//    int* color_map_r;
//    int* color_map_g;
//    int* color_map_b;
//    int* color_map_a;
//    int* link_map;
//
////    char* voxel_map;
////    char* color_map;
////    char* link_map;
//};

