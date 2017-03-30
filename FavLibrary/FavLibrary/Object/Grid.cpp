#include "Grid.h"

namespace FavLibrary
{
	Grid::Grid() 
	{
		unit = new Unit();
		origin = new Origin();
		dimension = new Dimension();
	}
	Grid::~Grid()
	{
		delete unit;
		delete origin;
		delete dimension;
	}

	Unit* Grid::getUnit() { return unit; }
	void Grid::setUnit(Point3D p) { unit->set(p); }
	void Grid::setUnit(double x, double y, double z) { unit->set(x, y, z); }
	double Grid::getUnitX() { return unit->getX(); }
	void Grid::setUnitX(double x) { unit->setX(x); }
	double Grid::getUnitY() { return unit->getY(); }
	void Grid::setUnitY(double y) { unit->setY(y); }
	double Grid::getUnitZ() { return unit->getY(); }
	void Grid::setUnitZ(double z) { unit->setY(z); }

	Dimension* Grid::getDimension() { return dimension; }
	void Grid::setDimension (Point3D p) { dimension->set(p); }
	void Grid::setDimension (double x, double y, double z) { dimension->set(x, y, z); }
	void Grid::setDimensionX(double x) { dimension->setX(x); }
    void Grid::setDimensionY(double y) { dimension->setY(y); }
    void Grid::setDimensionZ(double z) { dimension->setY(z); }
    double Grid::getDimensionX() { return dimension->getX(); }
	double Grid::getDimensionY() { return dimension->getY(); }
	double Grid::getDimensionZ() { return dimension->getY(); }

	Origin* Grid::getOrigin() { return origin; }
	void Grid::setOrigin (Point3D p) { origin->set(p); }
	void Grid::setOrigin (double x, double y, double z) { origin->set(x, y, z); }
	void Grid::setOriginX(double x) { origin->setX(x); }
	void Grid::setOriginY(double y) { origin->setY(y); }
	void Grid::setOriginZ(double z) { origin->setY(z); }
    double Grid::getOriginX() { return origin->getX(); }
    double Grid::getOriginY() { return origin->getY(); }
    double Grid::getOriginZ() { return origin->getY(); }
}