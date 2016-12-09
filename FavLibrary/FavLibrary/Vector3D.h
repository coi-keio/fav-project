#pragma once

#include <math.h>
#include "Point3D.h"

class Vector3D :
	public Point3D
{
public:
	Vector3D();
	~Vector3D();

	double getLength() { return sqrt(x * x + y * y + z * z); };

};

