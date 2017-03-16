#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Metadata.h"
#include "../Primitive/FavPrimitive.h"
#include "../FavSettings.h"

namespace FavLibrary
{
	enum class DllInterface MaterialType {
		material_name = 0,
		product_info = 1,
		iso_standard = 2,
	};

	class DllInterface MaterialSpec {
	public:
		virtual void dammy() {};
		MaterialSpec();
		~MaterialSpec();

		MaterialType materialType;
	};

	class DllInterface MaterialName : public MaterialSpec {
	public:

		MaterialName(std::string name_);
		std::string getMaterialName();
		void setMaterialName(std::string name_);

	private:
		std::string name;
	};

	class DllInterface ProductInfo : public MaterialSpec {
	public:

		ProductInfo(std::string manufacturer_, std::string product_name_, std::string url_);

		std::string getManufacturer();
		void setManufacturer(std::string manufacturer_);

		std::string getUrl();
		void setUrl(std::string url_);

		std::string getProductName();
		void setProductName(std::string product_name_);

	private:
		std::string manufacturer;
		std::string product_name;
		std::string url;
	};

	class DllInterface IsoStandard : public MaterialSpec {
	public:

		IsoStandard(std::string iso_id_, std::string iso_name_);
		std::string getIsoId();
		void setIsoId(std::string iso_id_);

		std::string getIsoName();
		void setIsoName(std::string iso_name_);

	private:
		std::string iso_id;
		std::string iso_name;
	};

	class DllInterface Material : public FavPrimitive, MetadataObject
	{
	public:
		Material();
		Material(unsigned int id_);
		Material(std::string name_);
		Material(unsigned int id_, std::string name_);
		~Material();

		std::list<MaterialSpec*> materials;

		bool hasMaterials();

		int getNumMaterials();
		//std::map<int, MaterialSpec*> getMaterials();
		//std::vector<MaterialSpec*> getMaterials();

		void addMaterialName(std::string material_name_);
		void addMaterialName(MaterialName* material_name_);

		void addProductInfo(std::string manufacturer_, std::string product_name_, std::string url_);
		void addProductInfo(ProductInfo* product_info_);

		void addIsoStandard(std::string iso_id_, std::string iso_name_);
		void addIsoStandard(IsoStandard* iso_standard_);

	private:
	};


}