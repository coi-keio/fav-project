#pragma once
#include "Stdafx.h"
#include "Material.h"

namespace FavLibraryDotNet
{
	//MaterialSpec::MaterialSpec() {};
	//MaterialSpec::~MaterialSpec() {};

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	MaterialName::MaterialName(System::String^ name_) { pMaterialName = new FavLibrary::MaterialName(marshal_as<std::string>(name_)); }
	MaterialName::~MaterialName() { delete pMaterialName; }

	System::String^ MaterialName::Name::get() { return  marshal_as<System::String^>(pMaterialName->getMaterialName()); }
	void MaterialName::Name::set(System::String^ value) { pMaterialName->setMaterialName(marshal_as<std::string>(value)); }

	MaterialType MaterialName::MaterialType::get() { return FavLibraryDotNet::MaterialType::material_name; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	ProductInfo::ProductInfo() { pProductInfo = new FavLibrary::ProductInfo(); }
	ProductInfo::ProductInfo(System::String^ manufacturer_, System::String^ product_name_, System::String^ url_)
	{
		pProductInfo = new FavLibrary::ProductInfo(
			marshal_as<std::string>(manufacturer_),
			marshal_as<std::string>(product_name_),
			marshal_as<std::string>(url_)
		);
	}
	ProductInfo::~ProductInfo() { delete pProductInfo; }

	System::String^ ProductInfo::Manufacturer::get() { return marshal_as<System::String^>(pProductInfo->getManufacturer()); }
	void ProductInfo::Manufacturer::set(System::String^ value) { pProductInfo->setManufacturer(marshal_as<std::string>(value)); }

	System::String^ ProductInfo::ProductName::get() { return  marshal_as<System::String^>(pProductInfo->getProductName()); }
	void ProductInfo::ProductName::set(System::String^ value) { pProductInfo->setProductName(marshal_as<std::string>(value)); }

	System::String^ ProductInfo::Url::get() { return marshal_as<System::String^>(pProductInfo->getUrl()); }
	void ProductInfo::Url::set(System::String^ value) { pProductInfo->setUrl(marshal_as<std::string>(value)); }

	MaterialType ProductInfo::MaterialType::get() { return FavLibraryDotNet::MaterialType::product_info; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	IsoStandard::IsoStandard() { pIsoStandard = new FavLibrary::IsoStandard(); }
	IsoStandard::IsoStandard(System::String^ iso_id_, System::String^ iso_name_)
	{
		pIsoStandard = new FavLibrary::IsoStandard(
			marshal_as<std::string>(iso_id_),
			marshal_as<std::string>(iso_name_)
		);
	}
	IsoStandard::~IsoStandard() { delete pIsoStandard; }

	System::String^ IsoStandard::IsoID::get() { return marshal_as<System::String^>(pIsoStandard->getIsoId()); }
	void IsoStandard::IsoID::set(System::String^ value) { pIsoStandard->setIsoId(marshal_as<std::string>(value)); }

	System::String^ IsoStandard::IsoName::get() { return marshal_as<System::String^>(pIsoStandard->getIsoName()); }
	void IsoStandard::IsoName::set(System::String^ value) { pIsoStandard->setIsoName(marshal_as<std::string>(value)); }

	MaterialType IsoStandard::MaterialType::get() { return FavLibraryDotNet::MaterialType::iso_standard; }

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	Material::Material() 
	{
		pMaterial = new FavLibrary::Material(); 
		_metadata = gcnew FavLibraryDotNet::Metadata();
	}
	Material::Material(unsigned int id_) 
	{
		pMaterial = new FavLibrary::Material(id_);
		_metadata = gcnew FavLibraryDotNet::Metadata();
	}
	Material::Material(System::String^ name_) 
	{
		pMaterial = new FavLibrary::Material(marshal_as<std::string>(name_));
		_metadata = gcnew FavLibraryDotNet::Metadata();
	}
	Material::Material(unsigned int id_, System::String^ name_)
	{
		pMaterial = new FavLibrary::Material(id_, marshal_as<std::string>(name_));
		_metadata = gcnew FavLibraryDotNet::Metadata();
	}
	Material::~Material() 
	{
		delete pMaterial;
		_metadata->~Metadata();
	}

	bool Material::HasMaterials::get() { return pMaterial->hasMaterials(); }
	int Material::NumMaterials::get() { return pMaterial->getNumMaterials(); }

	void addMaterialName(MaterialName material_name);
	void addProductInfo(ProductInfo product_info);
	void addIsoStandard(IsoStandard iso_standard);

	//FavLibraryDotNet::Metadata^ Material::Metadata::get()
	//{
	//	return gcnew FavLibraryDotNet::Metadata(pMaterial->getScaleX(), pGeometry->getScaleY(), pGeometry->getScaleZ());
	//}
	//void Material::Metadata::set(FavLibraryDotNet::Metadata^ value)
	//{
	//	return pMaterial->setScale(value->X, value->Y, value->Z);
	//}

	/// Impliment IFavPrimitive  -----------------------------------------------------------------------------------------

	unsigned int Material::ID::get() { return pMaterial->getId(); }
	void Material::ID::set(unsigned int value) { pMaterial->setId(value); }

	System::String^ Material::Name::get() { return marshal_as<System::String^>(pMaterial->getName()); }
	void Material::Name::set(System::String^ value) { pMaterial->setName(marshal_as<std::string>(value)); }
	/// ------------------------------------------------------------------------------------------------------------------


}