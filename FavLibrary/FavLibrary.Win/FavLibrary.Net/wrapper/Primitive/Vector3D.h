#pragma once

#include "Point3D.h"
#include "../../FavLibrary/Primitive/Vector3D.h"

using namespace FavLibrary;

namespace FavLibraryDotNet
{
	public ref class Vector3D : public Point3D
	{
	public:
		Vector3D();
		Vector3D(double x, double y, double z);
		~Vector3D();

		//double GetLength();
		//double GetDotProduct(Vector3D v);
		//Vector3D^ GetCrossProduct(Vector3D v);

		//static double GetDotProduct(Vector3D v1, Vector3D v2);
		//static Vector3D^ GetCrossProduct(Vector3D v1, Vector3D v2);

	private:
		FavLibrary::Vector3D* pVector3D;
	};

}