#pragma once

#include "../../FavLibrary/Palette/Geometry.h"
#include "./wrapper/Primitive/Point3D.h"
#include "./wrapper/Primitive/FavPrimitive.h"

namespace FavLibraryDotNet
{
	public enum class GeometryShape
	{
		cube,
		sphere,
		user_defined,
	};

	public ref class Scale : public Point3D
	{
	public:
		Scale();
		Scale(double x, double y, double z);
		~Scale();
	};


	public ref class Geometry : public IFavPrimitive
	{
	public:
		Geometry();
		Geometry(unsigned int id_);
		Geometry(System::String^ name_);
		Geometry(unsigned int id_, System::String^ name_);
		~Geometry();

		property GeometryShape Shape { GeometryShape get(); void set(GeometryShape value); }
		property FavLibraryDotNet::Scale^ Scale { FavLibraryDotNet::Scale^ get(); void set(FavLibraryDotNet::Scale^ value); }
		property System::String^ UserDefinedShapePath { System::String^ get(); void set(System::String^ value); }

		/// Impliment IFavPrimitive  -----------------------------------------------------------------------------------------
		virtual property bool IsRemoved { bool get(); }
		virtual void Remove();

		virtual property unsigned int ID { unsigned int get(); void set(unsigned int value); }
		virtual property System::String^ Name { System::String^ get(); void set(System::String^ value); }
		/// ------------------------------------------------------------------------------------------------------------------

	private:
		FavLibrary::Geometry* pGeometry;

	};



}