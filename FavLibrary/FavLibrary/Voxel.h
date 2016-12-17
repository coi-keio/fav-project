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
#include <map>
#include "Metadata.h"
#include "./Primitive/FavPrimitive.h"
#include "./Primitive/Color.h"


class VoxelInfo {
public:
    VoxelInfo() {};
    VoxelInfo(unsigned int id_) { identifier = id_; };
    ~VoxelInfo() {};
    
    unsigned int getId() { return identifier; };
    void setId(unsigned int id_) { identifier = id_; };
    
private:
    unsigned int identifier;
};

class GeometryInfo : public VoxelInfo {
public:
    GeometryInfo() : VoxelInfo() {};
    GeometryInfo(unsigned int id_) : VoxelInfo(id_) {};
    ~GeometryInfo() {};
};

class MaterialInfo : public VoxelInfo {
public:
    MaterialInfo() : VoxelInfo() {};
    MaterialInfo(unsigned int id_) : VoxelInfo(id_) { };
    MaterialInfo(unsigned int id_, double ratio_) : VoxelInfo(id_) { ratio = ratio_; };
    ~MaterialInfo() {};
    
    double getRatio() { return ratio; };
    void setRatio(double ratio_) { ratio = ratio_; };
    
private:
    double ratio = 1.0;
};

class Voxel : public FavPrimitive, MetadataObject
{    
public:
	Voxel() { identifier = ++counter; };
    Voxel(std::string name_) 
	{
		Voxel();
		name = name_; 
	};

	void setGeometryInfo(unsigned int id_){ geometry_info.setId(id_); };
	unsigned int getGeometryInfo() { return geometry_info.getId(); }

	std::vector<MaterialInfo> getMaterialInfo()
	{
		std::vector<MaterialInfo> res;
//		std::for_each(material_info.begin(), material_info.end(),
//			[&](const std::pair<const MaterialInfo, MaterialInfo>& ref) { res.push_back(ref.second); });
		return res;
	};
	MaterialInfo getMaterialInfo(unsigned int id_) { return *material_info[id_]; };
	void addMaterialInfo(unsigned int id_, double ratio_) { material_info[id_] = new MaterialInfo(ratio_); };
	void unpdateMaterialInfo(unsigned int id_, double ratio_) { material_info[id_]->setRatio(ratio_); };
	void removeMaterialInfo(unsigned int id_) { material_info.erase(id_); }
	bool existsMaterialInfo(unsigned int id_) { return material_info.count(id_) > 0; }
    
	ColorRGBA getDisplay() { return display; };
	void setDisplay(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) { display.setColorRBGA(r_, g_, b_, a_); };
	void setDisplay(ColorRGBA color_) { display.setColorRBGA(color_.getR(), color_.getG(), color_.getB(), color_.getA()); };

	unsigned char getDisplayR() { return display.getR(); };
	void setDisplayR(unsigned char r_) { display.setR(r_); };
	unsigned char getDisplayG() { return display.getG(); };
	void setDisplayG(unsigned char g_) { display.setG(g_); };
	unsigned char getDisplayB() { return display.getB(); };
	void setDisplayB(unsigned char b_) { display.setB(b_); };
	unsigned char getDisplayA() { return display.getA(); };
	void setDisplayA(unsigned char a_) { display.setA(a_); };

	std::string getApplicationNote() { return application_note; };
	void setApplicationNote(std::string note_) { application_note = note_; };

private:
    GeometryInfo geometry_info;
    std::map<unsigned int, MaterialInfo*> material_info;
    ColorRGBA display;
	std::string application_note;
    
    static unsigned int counter;
};


#endif /* defined(__FavLibrary__Voxel__) */
