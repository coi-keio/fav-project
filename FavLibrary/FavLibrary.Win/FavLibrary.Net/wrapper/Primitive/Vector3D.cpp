#include "Stdafx.h"
#include "Vector3D.h"

using namespace FavLibrary;

namespace FavLibraryDotNet
{
	Vector3D::Vector3D() { pVector3D = new FavLibrary::Vector3D(); }
	Vector3D::Vector3D(double x, double y, double z) { pVector3D = new FavLibrary::Vector3D(x, y, z); }
	Vector3D::~Vector3D() { delete pVector3D; }

	//double Vector3D::GetLength() { return pVector3D->GetLength(); }
	//double Vector3D::GetDotProduct(Vector3D v) { return pVector3D->GetDotProduct(new FavLibrary::Vector3D(v.X, v.Y, v.Z)); }
	//Vector3D^ Vector3D::GetCrossProduct(Vector3D v)
	//{
	//	FavLibrary::Vector3D vec = pVector3D->GetCrossProduct();
	//	return gcnew Vector3D(vec.getX(), vec.getY(), vec.getZ());
	//}

	//double Vector3D::GetDotProduct(Vector3D v1, Vector3D v2);
	//Vector3D^ Vector3D::GetCrossProduct(Vector3D v1, Vector3D v2);
}