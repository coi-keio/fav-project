#include "Geometry.h"

namespace FavLibrary
{
	Scale::Scale() : Point3D() { }
	Scale::Scale(double x, double y, double z) : Point3D(x, y, z) { }
	Scale::~Scale() {};

	Geometry::Geometry() {};
	Geometry::Geometry(unsigned int id_) : FavPrimitive(id_) {};
	Geometry::Geometry(std::string name_) : FavPrimitive(name_) {};
	Geometry::Geometry(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) {};
	Geometry::~Geometry() {};

	GeometryShape Geometry::getShape() { return shape; };
    void Geometry::setShape(GeometryShape shape_) { shape = shape_; has_shape = true;};

	std::string Geometry::getName() { return name; };
	void Geometry::setName(std::string name_) { name = name_; };

	double Geometry::getScaleX() { return scale.getX(); };
	void Geometry::setScaleX(double x_) { scale.setX(x_); has_scale = true;};

	double Geometry::getScaleY() { return scale.getY(); };
	void Geometry::setScaleY(double y_) { scale.setY(y_); has_scale = true;};

	double Geometry::getScaleZ() { return scale.getZ(); };
	void Geometry::setScaleZ(double z_) { scale.setZ(z_); has_scale = true;};

	void Geometry::setScale(double x_, double y_, double z_) { this->scale.set(x_, y_, z_); has_scale = true;};
    
    std::string Geometry::getReference() { return reference; };
    void Geometry::setReference(std::string  reference_path_) { reference = reference_path_; };

}