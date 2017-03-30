#pragma once
#include <stdio.h>
#include <string>
#include <map>
#include <list>
#include <vector>
#include "../Primitive/Point3D.h"
#include "../Primitive/FavPrimitive.h"


namespace FavLibrary
{
	enum class IDll GeometryShape
	{
		cube,
		sphere,
		user_defined,
        none,
	};

	class IDll Scale : public Point3D
	{
	public:
		Scale();
		Scale(double x, double y, double z);
		~Scale();

	private:
		Scale* pScale;
	};


	class IDll Geometry : public FavPrimitive
	{
	public:
		Geometry();
		Geometry(unsigned int id_);
		Geometry(std::string name_);
		Geometry(unsigned int id_, std::string name_);
		~Geometry();

        GeometryShape getShape();
		void setShape(GeometryShape shape_);
        
        void setName(std::string name_);
		std::string getName();
        
		double getScaleX();
		double getScaleY();
        double getScaleZ();
        void setScaleX(double x_);
		void setScaleY(double y_);
        void setScaleZ(double z_);
        void setScale(double x_, double y_, double z_);
        
        std::string getReference();
        void setReference(std::string reference_);
        
        bool hasShape(){return has_shape;};
        bool hasScale(){return has_scale;};

	private:
		std::string reference;
        GeometryShape shape = GeometryShape::none;
		Scale scale;
        
        bool has_shape = false;
        bool has_scale = false;
        
		Geometry* pGeometry;
	};



}