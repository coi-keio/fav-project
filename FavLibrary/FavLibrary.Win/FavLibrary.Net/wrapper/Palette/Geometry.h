#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.h"
#include "../Primitive/FavPrimitive.h"
#include "../FavSettings.h"

namespace FavLibrary
{
	RefEnum GeometryShape
	{
		cube,
		sphere,
		user_defined,
	};

	RefClass Scale : public Point3D
	{
	public:
		Scale();
		Scale(double x, double y, double z);
		~Scale();

	private:
#ifdef DotNet
		Scale^ pScale;
#endif
	};


	RefClass Geometry : public FavPrimitive
	{
	public:
		Geometry();
		Geometry(unsigned int id_);
		Geometry(std::string name_);
		Geometry(unsigned int id_, std::string name_);
		~Geometry();

		GeometryShape getShape();
		void setShape(GeometryShape shape_);

		std::string getName();
		void setName(std::string name_);

		double getScaleX();
		void setScaleX(double x_);

		double getScaleY();
		void setScaleY(double y_);

		double getScaleZ();
		void setScaleZ(double z_);

		void setScale(double x_, double y_, double z_);

	private:
		GeometryShape shape = GeometryShape::cube;
		Scale scale;

#ifdef DotNet
		Geometry^ pGeometry;
#else
		std::string userDefinedShape;
#endif

	};



}