//
//  Object.h
//  FavLibraryDotNet
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include "Object.h"
#include "Structure.h"

namespace FavLibraryDotNet
{
	Object::Object() {};
	Object::Object(unsigned int id_) : FavPrimitive(id_) {};
	Object::Object(std::string name_) : FavPrimitive(name_) {};
	Object::Object(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) {};

	Object::~Object() {};

	void Object::setStructure(Structure* structure_new_) { structure = structure_new_; };
}