#pragma once

#include "../../FavLibrary/Primitive/Point3D.h"

using namespace FavLibrary;

namespace FavLibraryDotNet
{
	public ref class Point3D
	{
	public:
		Point3D();
		Point3D(double x, double y, double z);
		~Point3D();

		void Set(Point3D p);
		void Set(double x_, double y_, double z_);

		property double X { double get(); void set(double value); }
		property double Y { double get(); void set(double value); }
		property double Z { double get(); void set(double value); }

	protected:
		FavLibrary::Point3D* pPoint3D;
	};

}