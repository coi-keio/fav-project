#include "Stdafx.h"
#include "Palette.h"

namespace FavLibraryDotNet
{
	Palette::Palette() {
		number_of_geometries = 0;
		number_of_materials = 0;
	};

	Geometry Palette::getGeometryById(unsigned int id_)
	{
		Geometry res;// = nullptr; //am
		if (geometries.count(id_) > 0 && !geometries[id_].isRemoved())
			res = geometries[id_];

		return res;
	};
	//	std::vector<Geometry> Palette::getGeometriesByNameSystem::String^ name_)
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
	//	std::vector<Material> Palette::getMaterialsByNameSystem::String^ name_)
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