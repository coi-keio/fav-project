#pragma once

#include <math.h>
#include "Point3D.h"

namespace FavLibrary
{

	class Vector3D :
		public Point3D
	{
	public:
		Vector3D();
		~Vector3D();

		double getLength();
	};

}