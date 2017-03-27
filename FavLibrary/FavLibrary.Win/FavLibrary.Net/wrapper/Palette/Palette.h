#pragma once

#include <algorithm>
#include <stdio.h>
#include <vector>
#include <map>
#include "Geometry.h"
#include "Material.h"
#include "../FavSettings.h"

namespace FavLibraryDotNet
{

	public ref class Palette {

	public:
		Palette();
		~Palette();

		Geometry getGeometryById(unsigned int id_);
		//	std::vector<Geometry> getGeometriesByName(System::String^ name_);
		void addGeometry(Geometry geometry_);
		void removeGeometry(unsigned int id_);

		Material getMaterialById(unsigned int id_);
		//	std::vector<Material> getMaterialsByName(System::String^ name_);
		void addMaterial(Material material_);
		void removeMaterial(unsigned int id_);

		int getNumberOfGeometries();
		int getNumberOfMaterials();

	private:
		std::map<unsigned int, Geometry> geometries;
		std::map<unsigned int, Material> materials;
		std::vector<unsigned int> geometry_id_list;
		std::vector<unsigned int> material_id_list;

		std::map<System::String^, std::vector<Geometry>> geometriesName;
		std::map<System::String^, std::vector<Material>> materialsName;

		unsigned int number_of_materials;
		unsigned int number_of_geometries;

#ifdef DotNet
		Palette^ pPalette;
#endif

	};
}
#endif /* defined(__FavLibraryDotNet__Palette__) */
