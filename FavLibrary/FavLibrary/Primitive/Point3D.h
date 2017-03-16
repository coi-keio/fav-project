#pragma once
#include "../FavSettings.h"

namespace FavLibrary
{
	RefClass DllInterface Point3D
	{
	public:
		Point3D();
		Point3D(double x, double y, double z);
		~Point3D();

		void set(Point3D p);

		double getX();
		double getY();
		double getZ();
		void set(double x_, double y_, double z_);
		void setX(double x_);
		void setY(double y_);
		void setZ(double z_);

	protected:
		double x = 0.0;
		double y = 0.0;
		double z = 0.0;
	};

}