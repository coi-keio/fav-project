#pragma once

#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.h"

class Grid
{
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
	double getDimensionX() { return unit.getX(); };
	void setDimensionX(double x) { unit.setX(x); };
	double getDimensionY() { return unit.getY(); };
	void setDimensionY(double y) { unit.setY(y); };
	double getDimensionZ() { return unit.getY(); };
	void setDimensionZ(double z) { unit.setY(z); };

	Origin getOrigin() { return origin; };
	void setOrigin(Point3D p) { origin.set(p); };
	void setOrigin(double x, double y, double z) { origin.set(x, y, z); };
	double getOriginX() { return unit.getX(); };
	void setOriginX(double x) { unit.setX(x); };
	double getOriginY() { return unit.getY(); };
	void setOriginY(double y) { unit.setY(y); };
	double getOriginZ() { return unit.getY(); };
	void setOriginZ(double z) { unit.setY(z); };

private:
	Unit unit;
	Dimension dimension;
	Origin origin;
};

class Unit : public Point3D
{

};

class Dimension : public Point3D
{

};

class Origin : public Point3D
{

};