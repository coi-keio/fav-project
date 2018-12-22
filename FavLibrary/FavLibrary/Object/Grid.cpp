#include "Grid.h"

namespace FavLibrary
{
	Grid::Grid() 
	{
	}
	Grid::~Grid()
	{
	}

	void Grid::setUnit(Point3D p) { unit.set(p); }
	void Grid::setUnit(double x, double y, double z) { unit.set(x, y, z); }
    void Grid::setUnitX(double x) { unit.setX(x); }
    void Grid::setUnitY(double y) { unit.setY(y); }
    void Grid::setUnitZ(double z) { unit.setZ(z); }
    Unit   Grid::getUnit()  { return unit; }
	double Grid::getUnitX() { return unit.getX(); }
	double Grid::getUnitY() { return unit.getY(); }
	double Grid::getUnitZ() { return unit.getZ(); }

	Dimension Grid::getDimension() { return dimension; }
	void Grid::setDimension (Point3D p) { dimension.set(p); }
	void Grid::setDimension (double x, double y, double z) { dimension.set(x, y, z); }
	void Grid::setDimensionX(double x) { dimension.setX(x); }
    void Grid::setDimensionY(double y) { dimension.setY(y); }
    void Grid::setDimensionZ(double z) { dimension.setZ(z); }
    int  Grid::getDimensionX() { return (int)dimension.getX(); }
	int  Grid::getDimensionY() { return (int)dimension.getY(); }
	int  Grid::getDimensionZ() { return (int)dimension.getZ(); }

	Origin Grid::getOrigin() { return origin; }
	void Grid::setOrigin (Point3D p) { origin.set(p); }
	void Grid::setOrigin (double x, double y, double z) { origin.set(x, y, z); }
	void Grid::setOriginX(double x) { origin.setX(x); }
	void Grid::setOriginY(double y) { origin.setY(y); }
	void Grid::setOriginZ(double z) { origin.setZ(z); }
    double Grid::getOriginX() { return origin.getX(); }
    double Grid::getOriginY() { return origin.getY(); }
    double Grid::getOriginZ() { return origin.getZ(); }
}