#pragma once

#include "../../FavLibrary/Palette/Material.h"
#include "./wrapper/Metadata.h"
#include "./wrapper/Primitive/FavPrimitive.h"

using namespace System::Collections::Generic;

namespace FavLibraryDotNet
{
	public enum class MaterialType {
		material_name = 0,
		product_info = 1,
		iso_standard = 2,
	};

	public ref class MaterialSpec abstract
	{
	public:
		virtual property FavLibraryDotNet::MaterialType MaterialType
		{
			FavLibraryDotNet::MaterialType get() = 0;
		}

	protected:
		FavLibrary::MaterialSpec* pMaterialSpec;
	};

	public ref class MaterialName : public MaterialSpec {
	public:
		MaterialName(System::String^ name);
		~MaterialName();

		property System::String^ Name { System::String^ get(); void set(System::String^ value); }
		virtual property FavLibraryDotNet::MaterialType MaterialType
		{
			FavLibraryDotNet::MaterialType get() override;
		}

	private:
		FavLibrary::MaterialName* pMaterialName;
	};

	public ref class ProductInfo : public MaterialSpec {
	public:
		ProductInfo();
		ProductInfo(System::String^ manufacturer, System::String^ product_name, System::String^ url);
		~ProductInfo();

		property System::String^ Manufacturer { System::String^ get(); void set(System::String^ value); }
		property System::String^ Url { System::String^ get(); void set(System::String^ value); }
		property System::String^ ProductName { System::String^ get(); void set(System::String^ value); }

		virtual property FavLibraryDotNet::MaterialType MaterialType
		{
			FavLibraryDotNet::MaterialType get() override;
		}
	private:
		FavLibrary::ProductInfo* pProductInfo;
	};

	public ref class IsoStandard : public MaterialSpec {
	public:
		IsoStandard();
		IsoStandard(System::String^ iso_id_, System::String^ iso_name_);
		~IsoStandard();

		property System::String^ IsoID { System::String^ get(); void set(System::String^ value); }
		property System::String^ IsoName { System::String^ get(); void set(System::String^ value); }

		virtual property FavLibraryDotNet::MaterialType MaterialType
		{
			FavLibraryDotNet::MaterialType get() override;
		}
	private:
		FavLibrary::IsoStandard* pIsoStandard;

	};

	public ref class Material : public IFavPrimitive
	{
	public:
		Material();
		Material(unsigned int id_);
		Material(System::String^ name_);
		Material(unsigned int id_, System::String^ name_);
		~Material();

		property bool HasMaterials { bool get(); }
		property int NumMaterials { int get(); }

		//void addMaterialName(MaterialName material_name);
		//void addProductInfo(ProductInfo product_info);
		//void addIsoStandard(IsoStandard iso_standard);

		//property FavLibraryDotNet::Metadata^ Metadata { FavLibraryDotNet::Metadata^ get(); void set(FavLibraryDotNet::Metadata^ value); }

		/// Impliment IFavPrimitive  -----------------------------------------------------------------------------------------
		virtual property bool IsRemoved { bool get(); }
		virtual void Remove();

		virtual property unsigned int ID { unsigned int get(); void set(unsigned int value); }
		virtual property System::String^ Name { System::String^ get(); void set(System::String^ value); }
		/// ------------------------------------------------------------------------------------------------------------------

	private:
		FavLibrary::Material* pMaterial;

		FavLibraryDotNet::Metadata^ _metadata;
	};


}