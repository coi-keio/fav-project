#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.h"
#include "../FavSettings.h"

namespace FavLibraryDotNet
{

	public ref class Unit : public Point3D
	{

	};

	public ref class Dimension : public Point3D
	{

	};

	public ref class Origin : public Point3D
	{

	};

	public ref class Grid
	{
	public:
		Grid();
		~Grid();

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

#ifdef DotNet
		Grid^ pGrid;
#endif
	};

}