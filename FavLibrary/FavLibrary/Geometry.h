#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "Point3D.h"

class Geometry {

public:
	Geometry() { identifier = ++counter; };

	Geometry(std::string name_) {
		Geometry();
		this->name = name_;
	};

	Geometry(std::string name_, GeometryShape shape_, Point3D scale_)
	{
		Geometry(name_);
		this->shape = shape_;
		this->scale.set(scale_);
	};

	Geometry(std::string name_, GeometryShape shape_, float scale_x_, float scale_y_, float scale_z_)
	{
		Geometry(name_);
		this->shape = shape_;
		this->scale.set(scale_x_, scale_y_, scale_z_);
	};

	Geometry(std::string name_, std::string user_defined_shape_, Point3D scale_)
	{
		Geometry(name_);
		this->shape = user_defined;
		this->userDefinedShape = user_defined_shape_;
		this->scale.set(scale_);
	};

	Geometry(std::string name_, std::string user_defined_shape_, float scale_x_, float scale_y_, float scale_z_)
	{
		Geometry(name_);
		this->shape = user_defined;
		this->userDefinedShape = user_defined_shape_;
		this->scale.set(scale_x_, scale_y_, scale_z_);
	};

	GeometryShape getShape() { return shape; };
	void setShape(GeometryShape shape_) { shape = shape_; };

	std::string getName() { return name; };
	void setName(std::string name_) { name = name_; };

	double getScaleX() { return scale.getX(); };
	void setScaleX(double x_) { scale.setX(x_); };

	double getScaleY() { return scale.getY(); };
	void setScaleY(double y_) { scale.setY(y_); };

	double getScaleZ() { return scale.getZ(); };
	void setScaleZ(double z_) { scale.setZ(z_); };

	void setScale(double x_, double y_, double z_) { this->scale.set(x_, y_, z_); };

	int getId() { return identifier; };

private:
	static int counter;
	int identifier;

	std::string name;
	std::string userDefinedShape;

	GeometryShape shape = cube;

	Scale scale;
};

enum GeometryShape
{
	cube,
	sphere,
	user_defined,
};

class Scale : public Point3D
{
public:
	Scale() : Point3D() { }
	Scale(double x, double y, double z) : Point3D(x, y, z) { }
	~Scale();
};