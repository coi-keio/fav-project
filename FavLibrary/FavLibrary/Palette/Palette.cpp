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
		Geometry res;// = nullptr; //am
		if (geometries.count(id_) > 0 && !geometries[id_].isRemoved())
			res = geometries[id_];

		return res;
	};
	//	std::vector<Geometry> Palette::getGeometriesByName(std::string name_)
	//	{
	//		std::vector<Geometry> res;
	//		if (geometriesName.count(name_) > 0)
	//			res = std::copy_if(geometriesName.begin(), geometriesName.end(), res,
	//				[name_](Geometry g) { return g.getName() == name_ && !g.isRemoved(); });
	//		
	//		return res;
	//	};
	void Palette::addGeometry(Geometry geometry_)
	{
		geometries[geometry_.getId()] = geometry_;
		geometriesName[geometry_.getName()].push_back(geometry_);
	};
	void Palette::removeGeometry(unsigned int id_)
	{
		geometries[id_].remove();
	}



	Material Palette::getMaterialById(unsigned int id_)
	{
		Material res;// = nullptr;
					 //		if (materials.count(id_) > 0 && !materials[id_].isRemoved())
		res = materials[id_];

		return res;
	};
	//	std::vector<Material> Palette::getMaterialsByName(std::string name_)
	//	{
	//		std::vector<Material> res;
	//		if (materialsName.count(name_) > 0)
	//			res = std::copy_if(materialsName.begin(), materialsName.end(), res,
	//				[name_](Material m) { return m.getName() == name_ && !m.isRemoved(); });
	//	};
	void Palette::addMaterial(Material material_)
	{
		materials[material_.getId()] = material_;
		materialsName[material_.getName()].push_back(material_);
	};
	void Palette::removeMaterial(unsigned int id_)
	{
		materials[id_].remove();
	}

	int Palette::getNumberOfGeometries() { return int(geometries.size()); };
	int Palette::getNumberOfMaterials() { return int(materials.size()); };
}