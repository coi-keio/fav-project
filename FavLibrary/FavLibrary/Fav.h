//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>

#include "Metadata.h"
#include "Palette.h"
#include "Voxel.h"
#include "Object.h"

class FavReader;
class FavWriter;

class Fav{
    
public:
    Fav();
    ~Fav();
    bool read(const char* file_path);
    bool write(const char* file_path, const char* version_);
    
    Metadata* metadata;
    Palette palette;
    std::vector<Voxel*> voxel;
    std::vector<Object*> object;
    
private:
    FavReader* fav_reader;
    FavWriter* fav_writer;

	std::string version;
};

