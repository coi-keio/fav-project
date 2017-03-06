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

namespace FavLibrary
{

	class Palette {

	public:
		Palette();

		Geometry getGeometryById(unsigned int id_);
		//	std::vector<Geometry> getGeometriesByName(std::string name_);
		void addGeometry(Geometry geometry_);
		void removeGeometry(unsigned int id_);

		Material getMaterialById(unsigned int id_);
		//	std::vector<Material> getMaterialsByName(std::string name_);
		void addMaterial(Material material_);
		void removeMaterial(unsigned int id_);

		int getNumberOfGeometries();
		int getNumberOfMaterials();

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
}
#endif /* defined(__FavLibrary__Palette__) */