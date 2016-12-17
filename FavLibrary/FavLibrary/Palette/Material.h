#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Metadata.h"
#include "../Primitive/FavPrimitive.h"

enum MaterialType {
    material_name = 0,
    product_info = 1,
    iso_standard = 2,
};

class MaterialSpec {
public:
    virtual void dammy(){};
    MaterialSpec() {};
    ~MaterialSpec() {};
    
    MaterialType materialTyep;
};

class MaterialName : public MaterialSpec {
public:
    const MaterialType materialTyep = MaterialType::material_name;
    
    MaterialName(std::string name_) { name = name_; }
    
    std::string getMaterialName() { return name; }
    void setMaterialName(std::string name_) { name = name_; }
    
private:
    std::string name;
};

class ProductInfo : public MaterialSpec {
public:
    MaterialType materialTyep = MaterialType::product_info;
    
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
    MaterialType materialTyep = MaterialType::iso_standard;
    
    IsoStandard(std::string iso_id_, std::string iso_name_) { iso_id = iso_id_, iso_name = iso_name_; };
    
    std::string getIsoId() { return iso_id; };
    void setIsoId(std::string iso_id_) { iso_id = iso_id_; };
    
    std::string getIsoName() { return iso_name; };
    void setIsoName(std::string iso_name_) { iso_name = iso_name_; };
    
private:
    std::string iso_id;
    std::string iso_name;
};

class Material : public FavPrimitive, MetadataObject
{
public:
    Material() { identifier = ++counter; std::cout << "counter = " << counter << std::endl;};
    ~Material();
	std::list<MaterialSpec*> materials;

	bool hasMaterials() { return getNumMaterials() > 0; };
    
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


private:
    static unsigned int counter;
};

