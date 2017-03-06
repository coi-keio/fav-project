#include "Grid.h"

namespace FavLibrary
{
	Unit Grid::getUnit() { return unit; };
	void Grid::setUnit(Point3D p) { unit.set(p); };
	void Grid::setUnit(double x, double y, double z) { unit.set(x, y, z); };
	double Grid::getUnitX() { return unit.getX(); };
	void Grid::setUnitX(double x) { unit.setX(x); };
	double Grid::getUnitY() { return unit.getY(); };
	void Grid::setUnitY(double y) { unit.setY(y); };
	double Grid::getUnitZ() { return unit.getY(); };
	void Grid::setUnitZ(double z) { unit.setY(z); };

	Dimension Grid::getDimension() { return dimension; };
	void Grid::setDimension(Point3D p) { dimension.set(p); };
	void Grid::setDimension(double x, double y, double z) { dimension.set(x, y, z); };
	double Grid::getDimensionX() { return dimension.getX(); };
	void Grid::setDimensionX(double x) { dimension.setX(x); };
	double Grid::getDimensionY() { return dimension.getY(); };
	void Grid::setDimensionY(double y) { dimension.setY(y); };
	double Grid::getDimensionZ() { return dimension.getY(); };
	void Grid::setDimensionZ(double z) { dimension.setY(z); };

	Origin Grid::getOrigin() { return origin; };
	void Grid::setOrigin(Point3D p) { origin.set(p); };
	void Grid::setOrigin(double x, double y, double z) { origin.set(x, y, z); };
	double Grid::getOriginX() { return origin.getX(); };
	void Grid::setOriginX(double x) { origin.setX(x); };
	double Grid::getOriginY() { return origin.getY(); };
	void Grid::setOriginY(double y) { origin.setY(y); };
	double Grid::getOriginZ() { return origin.getY(); };
	void Grid::setOriginZ(double z) { origin.setY(z); };
}