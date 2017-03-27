#include "Vector3D.h"

namespace FavLibrary
{
	Vector3D::Vector3D() {}
	Vector3D::Vector3D(double x_, double y_, double z_) 
	{ 
		x = x_;
		y = y_;
		z = z_;
	}
	Vector3D::~Vector3D() {}

	double Vector3D::GetLength() { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }
	double Vector3D::GetDotProduct(Vector3D v) { return x * v.x + y * v.y + z * v.z; }
	Vector3D* Vector3D::GetCrossProduct(Vector3D v)
	{
		return new Vector3D(
			y * v.z - z * v.y,
			z * v.x - x * v.z,
			x * v.y - y * v.x
		);
	}

	double Vector3D::GetDotProduct(Vector3D v1, Vector3D v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
	Vector3D* Vector3D::GetCrossProduct(Vector3D v1, Vector3D v2)
	{
		return new Vector3D(
			v1.y * v2.z - v1.z * v2.y,
			v1.z * v2.x - v1.x * v2.z,
			v1.x * v2.y - v1.y * v2.x
		);
	}
}