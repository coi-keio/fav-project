#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.h"

class Unit : public Point3D
{
    
};

class Dimension : public Point3D
{
    
};

class Origin : public Point3D
{
    
};

class Grid
{
public:
	Unit getUnit() { return unit; };
	void setUnit(Point3D p) { unit.set(p); };
	void setUnit(double x, double y, double z) { unit.set(x, y, z); };
	double getUnitX() { return unit.getX(); };
	void setUnitX(double x) { unit.setX(x); };
	double getUnitY() { return unit.getY(); };
	void setUnitY(double y) { unit.setY(y); };
	double getUnitZ() { return unit.getY(); };
	void setUnitZ(double z) { unit.setY(z); };

	Dimension getDimension() { return dimension; };
	void setDimension(Point3D p) { dimension.set(p); };
	void setDimension(double x, double y, double z) { dimension.set(x, y, z); };
	double getDimensionX() { return dimension.getX(); };
	void setDimensionX(double x) { dimension.setX(x); };
	double getDimensionY() { return dimension.getY(); };
	void setDimensionY(double y) { dimension.setY(y); };
	double getDimensionZ() { return dimension.getY(); };
	void setDimensionZ(double z) { dimension.setY(z); };

	Origin getOrigin() { return origin; };
	void setOrigin(Point3D p) { origin.set(p); };
	void setOrigin(double x, double y, double z) { origin.set(x, y, z); };
	double getOriginX() { return origin.getX(); };
	void setOriginX(double x) { origin.setX(x); };
	double getOriginY() { return origin.getY(); };
	void setOriginY(double y) { origin.setY(y); };
	double getOriginZ() { return origin.getY(); };
	void setOriginZ(double z) { origin.setY(z); };

private:
	Unit unit;
	Dimension dimension;
	Origin origin;
};