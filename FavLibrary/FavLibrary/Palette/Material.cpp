#include "Material.h"

namespace FavLibrary
{
	MaterialSpec::MaterialSpec() {};
	MaterialSpec::~MaterialSpec() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	MaterialName::MaterialName(std::string name_) { name = name_; materialType = MaterialType::material_name; }
	std::string MaterialName::getMaterialName() { return name; }
	void MaterialName::setMaterialName(std::string name_) { name = name_; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ProductInfo::ProductInfo() {};
	ProductInfo::ProductInfo(std::string manufacturer_, std::string product_name_, std::string url_)
	{
		materialType = MaterialType::product_info;
		manufacturer = manufacturer_;
		product_name = product_name_;
		url = url_;
	};

	std::string ProductInfo::getManufacturer() { return manufacturer; };
	void ProductInfo::setManufacturer(std::string manufacturer_) { manufacturer = manufacturer_; };

	std::string ProductInfo::getUrl() { return url; };
	void ProductInfo::setUrl(std::string url_) { url = url_; };

	std::string ProductInfo::getProductName() { return product_name; };
	void ProductInfo::setProductName(std::string product_name_) { product_name = product_name_; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	IsoStandard::IsoStandard() {};
	IsoStandard::IsoStandard(std::string standard_name_) {
		standard_name = standard_name_;
		materialType = MaterialType::iso_standard;
	}

	std::string IsoStandard::getStandardName() {
		return standard_name;
	}
	void IsoStandard::setStandardName(std::string standard_name_) {
		standard_name = standard_name_;
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Material::Material() {};
	Material::Material(unsigned int id_) : FavPrimitive(id_) {};
	Material::Material(std::string name_) : FavPrimitive(name_) {};
	Material::Material(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) {};

    Material::~Material() {
        materials.clear();
    };

	bool Material::hasMaterials() { return getNumMaterials() > 0; };

	int Material::getNumMaterials() { return int(materials.size()); }


	void Material::addMaterialName(std::string material_name_) {
        MaterialName* material_name = new MaterialName(material_name_);
        materials.push_back(std::shared_ptr<MaterialSpec>(material_name));

    };

	void Material::addMaterialName(MaterialName material_name_) {

        MaterialName* tmp = new MaterialName(material_name_.getMaterialName());
        materials.push_back(std::shared_ptr<MaterialSpec>(tmp));

    };

	void Material::addProductInfo(std::string manufacturer_, std::string product_name_, std::string url_) {

        ProductInfo* pinfo = new ProductInfo(manufacturer_, product_name_, url_);

        materials.push_back(std::shared_ptr<MaterialSpec>(pinfo));

	};
	void Material::addProductInfo(ProductInfo product_info_) {
        ProductInfo* pinfo = new ProductInfo(product_info_.getManufacturer(), product_info_.getProductName(), product_info_.getUrl());
        materials.push_back(std::shared_ptr<MaterialSpec>(pinfo));
    };

	void Material::addIsoStandard(std::string standard_name_) {
        IsoStandard* iso_standard = new IsoStandard(standard_name_);
		materials.push_back(std::shared_ptr<MaterialSpec>(iso_standard));
	};
	void Material::addIsoStandard(IsoStandard iso_standard_) {
        IsoStandard* iso_standard = new IsoStandard(iso_standard_.getStandardName());
        materials.push_back(std::shared_ptr<MaterialSpec>(iso_standard));

    };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
