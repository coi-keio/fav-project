#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Metadata.h"

class Material
{
public:
	Material() { identifier = ++counter; };
	std::list<MaterialSpec*> materials;
	Metadata* metadata;

	bool hasMaterials() { return getNumMaterials() > 0; };
	bool hasMetadata() { return metadata != nullptr; };

	int getNumMaterials() { return int(materials.size()); }
	//std::map<int, MaterialSpec*> getMaterials() { return materials; }
	//std::vector<MaterialSpec*> getMaterials() { return materials; }

	void addMaterialName(std::string material_name_) { materials.push_back(new MaterialName(material_name_)); };
	void addMaterialName(MaterialName* material_name_) { materials.push_back(material_name_); };

	void addProductInfo(std::string manufacturer_, std::string product_name_, std::string url_) {
		materials.push_back(new ProductInfo(manufacturer_, product_name_, url_));
	};
	void addProductInfo(ProductInfo* product_info_) { materials.push_back(product_info_); };

	void addIsoStandard(std::string iso_id_, std::string iso_name_) {
		materials.push_back(new IsoStandard(iso_id_, iso_name_));
	};
	void addIsoStandard(IsoStandard* iso_standard_) { materials.push_back(iso_standard_); };

	//void setMetadata(Metadata metadata_) { metadata = &metadata_; has_meta_data = true; };

	int getId() { return identifier; };
	
private:
	static int counter;
	int identifier;
};

enum MaterialType {
	material_name,
	product_info,
	iso_standard,
};

class MaterialSpec {
public:
	MaterialSpec();
	~MaterialSpec();

	MaterialType materialTyep;
};

class MaterialName : public MaterialSpec {
public:
	const MaterialType materialTyep = material_name;

	MaterialName(std::string name_) { name = name_; }

	std::string getMaterialName() { return name; }
	void setMaterialName(std::string name_) { name = name_; }

private:
	std::string name;
};

class ProductInfo : public MaterialSpec {
public:
	const MaterialType materialTyep = product_info;

	ProductInfo(std::string manufacturer_, std::string product_name_, std::string url_)
	{
		manufacturer = manufacturer_;
		product_name = product_name_;
		url = url_;
	};

	std::string getManufacturer() { return manufacturer; };
	void setManufacturer(std::string manufacturer_) { manufacturer = manufacturer_; };

	std::string getUrl() { return url; };
	void setUrl(std::string url_) { url = url_; };

	std::string getProductName() { return product_name; };
	void setProductName(std::string product_name_) { product_name = product_name_; };

private:
	std::string manufacturer;
	std::string product_name;
	std::string url;
};

class IsoStandard : public MaterialSpec {
public:
	const MaterialType materialTyep = iso_standard;

	IsoStandard(std::string iso_id_, std::string iso_name_) { iso_id = iso_id_, iso_name = iso_name_; };

	std::string getIsoId() { return iso_id; };
	void setIsoId(std::string iso_id_) { iso_id = iso_id_; };

	std::string getIsoName() { return iso_name; };
	void setIsoName(std::string iso_name_) { iso_name = iso_name_; };

private:
	std::string iso_id;
	std::string iso_name;
};

