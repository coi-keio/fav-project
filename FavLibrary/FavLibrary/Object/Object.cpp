//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include "Object.h"
#include "Structure.h"

namespace FavLibrary
{
	Object::Object() {};
	
    Object::Object(unsigned int id_)  : FavPrimitive(id_) {
    
        structure.setGridPointer(&grid);
        
    };
    
	Object::Object(std::string name_) : FavPrimitive(name_) {
    
        structure.setGridPointer(&grid);

    };
    
	Object::Object(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) {
    
        structure.setGridPointer(&grid);

    };

	Object::~Object() {
    };

}