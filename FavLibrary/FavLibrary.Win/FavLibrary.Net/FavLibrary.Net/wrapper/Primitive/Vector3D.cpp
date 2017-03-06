#include "Vector3D.h"

namespace FavLibrary
{
	Vector3D::Vector3D() {}
	Vector3D::~Vector3D() {}

	double Vector3D::getLength() { return sqrt(x * x + y * y + z * z); };

}