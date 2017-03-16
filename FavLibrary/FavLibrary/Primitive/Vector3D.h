#pragma once

#include <math.h>
#include "Point3D.h"
#include "../FavSettings.h"

namespace FavLibrary
{

	class DllInterface Vector3D :
		public Point3D
	{
	public:
		Vector3D();
		~Vector3D();

		double getLength();
	};

}