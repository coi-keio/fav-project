#include "Stdafx.h"
#include "Point3D.h"

using namespace FavLibrary;

namespace FavLibraryDotNet
{
	Point3D::Point3D() { pPoint3D = new FavLibrary::Point3D(); }
	Point3D::Point3D(double x, double y, double z) { pPoint3D = new FavLibrary::Point3D(x, y, z); }
	Point3D::~Point3D() { delete pPoint3D; }

	void Point3D::Set(Point3D p)
	{
		pPoint3D->set(p.X, p.Y, p.Z);
	}
	void Point3D::Set(double x, double y, double z)
	{
		pPoint3D->set(x, y, z);
	};

	double Point3D::X::get() { return pPoint3D->getX(); }
	void Point3D::X::set(double value) { return pPoint3D->setX(value); }

	double Point3D::Y::get() { return pPoint3D->getY(); }
	void Point3D::Y::set(double value) { return pPoint3D->setY(value); }

	double Point3D::Z::get() { return pPoint3D->getZ(); }
	void Point3D::Z::set(double value) { return pPoint3D->setZ(value); }

}