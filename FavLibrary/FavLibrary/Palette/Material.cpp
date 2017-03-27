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
	IsoStandard::IsoStandard(std::string iso_id_, std::string iso_name_) { iso_id = iso_id_, iso_name = iso_name_; materialType = MaterialType::iso_standard; };

	std::string IsoStandard::getIsoId() { return iso_id; };
	void IsoStandard::setIsoId(std::string iso_id_) { iso_id = iso_id_; };

	std::string IsoStandard::getIsoName() { return iso_name; };
	void IsoStandard::setIsoName(std::string iso_name_) { iso_name = iso_name_; };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Material::Material() {};
	Material::Material(unsigned int id_) : FavPrimitive(id_) {};
	Material::Material(std::string name_) : FavPrimitive(name_) {};
	Material::Material(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) {};
	Material::~Material() {};

	bool Material::hasMaterials() { return getNumMaterials() > 0; };

	int Material::getNumMaterials() { return int(materials.size()); }
	//std::map<int, MaterialSpec*> Material::getMaterials() { return materials; }
	//std::vector<MaterialSpec*> Material::getMaterials() { return materials; }

	void Material::addMaterialName(std::string material_name_) { materials.push_back(new MaterialName(material_name_)); };
	void Material::addMaterialName(MaterialName* material_name_) { materials.push_back(material_name_); };

	void Material::addProductInfo(std::string manufacturer_, std::string product_name_, std::string url_) {
		materials.push_back(new ProductInfo(manufacturer_, product_name_, url_));
	};
	void Material::addProductInfo(ProductInfo* product_info_) { materials.push_back(product_info_); };

	void Material::addIsoStandard(std::string iso_id_, std::string iso_name_) {
		materials.push_back(new IsoStandard(iso_id_, iso_name_));
	};
	void Material::addIsoStandard(IsoStandard* iso_standard_) { materials.push_back(iso_standard_); };

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}