//
//  Palette.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__Palette__
#define __FavLibrary__Palette__

#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include "Geometry.h"
#include "Material.h"

class Palette {

public:
    Palette(){
        number_of_geometries = 0;
        number_of_materials = 0;
    };
    
	Geometry getGeometryById(unsigned int id_)
	{
        Geometry res;// = nullptr; //am
		if (geometries.count(id_) > 0 && !geometries[id_].isRemoved())
			res = geometries[id_];

		return res;
	};
//	std::vector<Geometry> getGeometriesByName(std::string name_)
//	{
//		std::vector<Geometry> res;
//		if (geometriesName.count(name_) > 0)
//			res = std::copy_if(geometriesName.begin(), geometriesName.end(), res,
//				[name_](Geometry g) { return g.getName() == name_ && !g.isRemoved(); });
//		
//		return res;
//	};
	void addGeometry(Geometry geometry_)
	{
		geometries[geometry_.getId()] = geometry_; 
		geometriesName[geometry_.getName()].push_back(geometry_);
	};
	void removeGeometry(unsigned int id_)
	{
		geometries[id_].remove();
	}

    
    
	Material getMaterialById(unsigned int id_)
	{
        Material res;// = nullptr;
//		if (materials.count(id_) > 0 && !materials[id_].isRemoved())
			res = materials[id_];

		return res;
	};
//	std::vector<Material> getMaterialsByName(std::string name_)
//	{
//		std::vector<Material> res;
//		if (materialsName.count(name_) > 0)
//			res = std::copy_if(materialsName.begin(), materialsName.end(), res,
//				[name_](Material m) { return m.getName() == name_ && !m.isRemoved(); });
//	};
	void addMaterial(Material material_)
	{ 
		materials[material_.getId()] = material_; 
		materialsName[material_.getName()].push_back(material_);
	};
	void removeMaterial(unsigned int id_)
	{
		materials[id_].remove();
	}

	int getNumberOfGeometries(){ return int(geometries.size()); };
    int getNumberOfMaterials(){ return int(materials.size()); };

private:
	std::map<unsigned int, Geometry> geometries;
	std::map<unsigned int, Material> materials;
    std::vector<unsigned int> geometry_id_list;
    std::vector<unsigned int> material_id_list;

	std::map<std::string, std::vector<Geometry>> geometriesName;
	std::map<std::string, std::vector<Material>> materialsName;
    
    unsigned int number_of_materials;
    unsigned int number_of_geometries;
};

#endif /* defined(__FavLibrary__Palette__) */
