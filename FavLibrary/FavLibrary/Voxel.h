//
//  Voxel.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__Voxel__
#define __FavLibrary__Voxel__

#include <stdio.h>
#include <string>
#include <vector>
#include "Metadata.h"
#include "Object.h"

class GeometryInfo{
    
public:
    int getId(){ return index; };
    void setId(int index_){ index = index_; };
private:
    int index;
};

class MaterialInfo{
    
public:
    MaterialInfo(int index_, double ratio_){ index = index_; ratio = ratio_; };
    int getId(){ return index; };
    double getRatio(){ return ratio; };
    void setId(int index_){ index = index_; };
    void setRatio(double ratio_){ ratio = ratio_; };

private:
    int index;
    double ratio;
};

class Voxel{
    
public:
    Voxel(){ number_of_material_info = 0; has_meta_data = false; };
    Voxel(int index_, std::string name_){ index = index_; name = name_; };
    int getId();
    std::string getName();
    void setId(int index_){ index = index_; };
    void setName(std::string name_){ name = name_; };
    void setGeometryInfo(int index_){ geometry_info.setId(index_); };
    void addMaterialInfo(int index_, double ratio_){
        material_info.push_back(*new MaterialInfo(index_, ratio_));
        number_of_material_info++;
    };
    void setDisplay(int r_, int g_, int b_, int a_){ display.setR(r_); display.setR(g_); display.setR(b_); display.setR(a_);};
    void setMetadata(Metadata metadata_){ metadata = &metadata_; has_meta_data = true; };

    
private:
    int index;
    std::string name;
    GeometryInfo geometry_info;
    std::vector<MaterialInfo> material_info;
    Color display;
    Metadata* metadata;
    int number_of_material_info;
    bool has_meta_data;
};


#endif /* defined(__FavLibrary__Voxel__) */
