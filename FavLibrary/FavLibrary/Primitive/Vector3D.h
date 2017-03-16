#pragma once

#include <math.h>
#include "Point3D.h"
#include "../FavSettings.h"

namespace FavLibrary
{
	RefClass Vector3D : public Point3D
	{
	public:
		Vector3D();
		~Vector3D();

		double getLength();

	private:
		Vector3D* pVector3D;
	};

}