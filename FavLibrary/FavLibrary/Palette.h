//
//  Palette.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__Palette__
#define __FavLibrary__Palette__

#include <stdio.h>
#include <vector>
#include "Geometry.h"
#include "Material.h"

class Palette {

public:
	Geometry* getGeometry(int id_) {
		Geometry* res = nullptr;

		std::vector<Geometry*>::iterator itr
			= std::find(geometries.begin(), geometries.end(),
				[id_](Geometry* const& g) { return g->getId() == id_; });

		if (itr != geometries.end())
		{
			auto index = std::distance(geometries.begin(), itr);
			res = geometries.at(index);
		}

		return res;
	};
	
	void addGeometry(Geometry *geometry_) { geometries.push_back(geometry_); };
	void removeGeometry(int id_)
	{
		free(getGeometry(id_));
	}

	Material* getMaterial(int id_)
	{
		Material* res = nullptr;

		std::vector<Material*>::iterator itr
			= std::find(materials.begin(), materials.end(),
				[id_](Material* const& g) { return g->getId() == id_; });

		if (itr != materials.end())
		{
			auto index = std::distance(materials.begin(), itr);
			res = materials.at(index);
		}

		return res;
	};

	void addMaterial(Material *material_) { materials.push_back(material_); };
	void removeMaterial(int id_)
	{
		free(getMaterial(id_));
	}

	int getNumberOfGeometries(){ return int(geometries.size()); };
    int getNumberOfMaterials(){ return int(materials.size()); };

private:
    std::vector<Geometry*> geometries;
    std::vector<Material*> materials;
};

#endif /* defined(__FavLibrary__Palette__) */
