//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#pragma once

#include <string>
#include "Structure.h"
#include "Grid.h"
#include "../Metadata.h"
#include "../Primitive/FavPrimitive.h"


namespace FavLibrary
{

	class IDll Object : public FavPrimitive, MetadataObject
	{
	public:
		Object();
		Object(unsigned int id_);
		Object(std::string name_);
        Object(unsigned int id_, std::string name_);
		~Object();
        
        Grid grid;
        Structure structure;

	private:

		Object* pObject;

	};

}