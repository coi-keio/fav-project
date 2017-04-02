//
//  Palette.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "Palette.h"

namespace FavLibrary
{
	Palette::Palette() {
		number_of_geometries = 0;
		number_of_materials = 0;
	};
    
    Palette::~Palette() {
//        for(std::map<unsigned int, Material*>::iterator it = materials.begin(); it != materials.end();){
//            if(it->second != NULL){
//                delete it->second;
//                it->second = nullptr;
//            }
//            it++;
//        }
    };

	Geometry Palette::getGeometryById(unsigned int id_)
	{
		Geometry res = NULL;
		if (geometries.count(id_) > 0)
			res = geometries[id_];

		return res;
	};
	void Palette::addGeometry(Geometry geometry_)
	{
		geometries[geometry_.getId()] = geometry_;
	};
	void Palette::removeGeometry(unsigned int id_)
	{
		geometries.erase(id_);
	}



	Material Palette::getMaterialById(unsigned int id_)
	{
		Material res = NULL;
		if (materials.count(id_) > 0)
			res = materials[id_];

		return res;
	}
	void Palette::addMaterial(Material material_)
	{
		materials[material_.getId()] = material_;
	};
	void Palette::removeMaterial(unsigned int id_)
	{
		materials.erase(id_);
	}

	int Palette::getNumberOfGeometries() { return int(geometries.size()); };
	int Palette::getNumberOfMaterials() { return int(materials.size()); };
}