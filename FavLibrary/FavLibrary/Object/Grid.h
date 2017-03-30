#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.h"


namespace FavLibrary
{

	class IDll Unit : public Point3D
	{

	};

	class IDll Dimension : public Point3D
	{

	};

	class IDll Origin : public Point3D
	{

	};

	class IDll Grid
	{
	public:
		Unit getUnit();
		void setUnit(Point3D p);
		void setUnit(double x, double y, double z);
		double getUnitX();
		void setUnitX(double x);
		double getUnitY();
		void setUnitY(double y);
		double getUnitZ();
		void setUnitZ(double z);

		Dimension getDimension();
		void setDimension(Point3D p);
		void setDimension(double x, double y, double z);
		double getDimensionX();
		void setDimensionX(double x);
		double getDimensionY();
		void setDimensionY(double y);
		double getDimensionZ();
		void setDimensionZ(double z);

		Origin getOrigin();
		void setOrigin(Point3D p);
		void setOrigin(double x, double y, double z);
		double getOriginX();
		void setOriginX(double x);
		double getOriginY();
		void setOriginY(double y);
		double getOriginZ();
		void setOriginZ(double z);

	private:
		Unit unit;
		Dimension dimension;
		Origin origin;

		Grid* pGrid;
	};

}