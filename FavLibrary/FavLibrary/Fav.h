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
#include <map>
#include <algorithm>


#include "./Palette/Palette.h"
#include "./Object/Object.h"
#include "FavReader.h"
#include "FavWriter.h"
#include "Voxel.h"
#include "Metadata.h"

namespace FavLibrary
{
	class IDll Fav : public MetadataObject
	{
	public:
		Fav();
		~Fav();
		bool read (const char* file_path);
        bool write(const char* file_path, CompressionMode compression_mode_);
		//bool write(const char* file_path, const char* version_);

		std::vector<Voxel> getVoxels();
		Voxel getVoxel(unsigned int id_);
		void addVoxel(Voxel voxel_);
		void removeVoxel(unsigned int id_);
		bool existsVoxel(unsigned int id_);

		std::map<unsigned int, Object*> getObjects();
		Object* getObject(unsigned int id_);
		void addObject(Object* object_);
		void removeObject(unsigned int id_);

		int getNumObjects();
		int getNumVoxels();

		Palette palette;

	private:
		std::string version;
		std::map<unsigned int, Voxel> voxels;
		std::map<unsigned int, Object*> objects;

		FavReader* fav_reader = NULL;
		FavWriter* fav_writer = NULL;

		Fav* pFav;
	};

}