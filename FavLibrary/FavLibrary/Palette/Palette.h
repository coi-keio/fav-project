//
//  Palette.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//
#pragma once

#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include "Geometry.h"
#include "Material.h"


namespace FavLibrary
{

	class IDll Palette {

	public:
		Palette();
        ~Palette();
		Geometry getGeometryById(unsigned int id_);
		void addGeometry(Geometry geometry_);
		void removeGeometry(unsigned int id_);

		Material getMaterialById(unsigned int id_);
		void addMaterial(Material material_);
		void removeMaterial(unsigned int id_);

		int getNumberOfGeometries();
		int getNumberOfMaterials();

	private:
		std::map<unsigned int, Geometry> geometries;
		std::map<unsigned int, Material> materials;
		std::vector<unsigned int> geometry_id_list;
		std::vector<unsigned int> material_id_list;

		unsigned int number_of_materials;
		unsigned int number_of_geometries;

//		Palette* pPalette;
	};
}
