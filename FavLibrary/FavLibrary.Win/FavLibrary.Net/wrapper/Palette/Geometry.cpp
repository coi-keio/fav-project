#pragma once
#include "Stdafx.h"
#include "Geometry.h"

namespace FavLibraryDotNet
{
	Scale::Scale() { pPoint3D = new FavLibrary::Scale(); }
	Scale::Scale(double x, double y, double z) { Set(x, y, z); }
	Scale::~Scale() { delete pPoint3D; }

	Geometry::Geometry() { pGeometry = new FavLibrary::Geometry(); }
	Geometry::Geometry(unsigned int id_) { pGeometry = new FavLibrary::Geometry(id_); }
	Geometry::Geometry(System::String^ name_) { pGeometry = new FavLibrary::Geometry(marshal_as<std::string>(name_)); }
	Geometry::Geometry(unsigned int id_, System::String^ name_) { pGeometry = new FavLibrary::Geometry(id_, marshal_as<std::string>(name_)); }
	Geometry::~Geometry() {};

	GeometryShape Geometry::Shape::get()
	{
		switch (pGeometry->getShape())
		{
		case FavLibrary::GeometryShape::sphere:
			return GeometryShape::sphere;
		case FavLibrary::GeometryShape::user_defined:
			return GeometryShape::user_defined;
		default:
			return GeometryShape::cube;
		}
	}
	void Geometry::Shape::set(GeometryShape value) 
	{
		switch (value)
		{
		case GeometryShape::sphere:
			return pGeometry->setShape(FavLibrary::GeometryShape::sphere);
		case GeometryShape::user_defined:
			return pGeometry->setShape(FavLibrary::GeometryShape::user_defined);
		default:
			return pGeometry->setShape(FavLibrary::GeometryShape::cube);
		}
	}

	FavLibraryDotNet::Scale^ Geometry::Scale::get()
	{
		return gcnew FavLibraryDotNet::Scale(pGeometry->getScaleX(), pGeometry->getScaleY(), pGeometry->getScaleZ());
	}
	void Geometry::Scale::set(FavLibraryDotNet::Scale^ value)
	{
		return pGeometry->setScale(value->X, value->Y, value->Z);
	}

	System::String^ Geometry::UserDefinedShapePath::get() { throw gcnew System::NotImplementedException(); }
	void Geometry::UserDefinedShapePath::set(System::String^ value) { throw gcnew System::NotImplementedException(); }

	/// Impliment IFavPrimitive  -----------------------------------------------------------------------------------------
	unsigned int Geometry::ID::get() { return pGeometry->getId(); }
	void Geometry::ID::set(unsigned int value) { pGeometry->setId(value); }

	System::String^ Geometry::Name::get() { return marshal_as<System::String^>(pGeometry->getName()); }
	void Geometry::Name::set(System::String^ value) { pGeometry->setName(marshal_as<std::string>(value)); }
	/// ------------------------------------------------------------------------------------------------------------------
}