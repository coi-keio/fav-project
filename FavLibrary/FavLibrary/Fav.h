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

#include "Voxel.h"
#include "Metadata.h"
#include "./Palette/Palette.h"
#include "./Object/Object.h"

class FavReader;
class FavWriter;



class Fav : public MetadataObject
{    
public:
    Fav();
    ~Fav();
    bool read(const char* file_path);
    bool write(const char* file_path, const char* version_);
    
	std::vector<Voxel> getVoxels()
	{
		std::vector<Voxel> res;
//		std::for_each(voxels.begin(), voxels.end(),
//			[&](const std::pair<const Voxel, Voxel>& ref) { res.push_back(ref.second); });
		return res;
	};
	Voxel getVoxel(unsigned int id_)
	{
        Voxel res;// = nullptr;
		if (voxels.count(id_) > 0 && !voxels[id_]->isRemoved())
            res = *voxels[id_];

		return res;
	};
	void addVoxel(Voxel* voxel_) { voxels[voxel_->getId()] = voxel_; };
	void removeVoxel(unsigned int id_) { voxels[id_]->remove(); }
	bool existsVoxel(unsigned int id_) { return voxels.count(id_) > 0 && !voxels[id_]->isRemoved(); }

	std::vector<Object> getObjects()
	{
		std::vector<Object> res;
//		std::for_each(objects.begin(), objects.end(),
//			[&](const std::pair<const Object, Object>& ref) { res.push_back(ref.second); });
		return res;
	};
	Object getObject(unsigned int id_) 
	{ 
        Object res;// = nullptr;
		if (objects.count(id_) > 0 && !objects[id_]->isRemoved())
			res = *objects[id_];

		return res;
	};
	void addObject(Object* object_) { objects[object_->getId()] = object_; };
	void removeObject(unsigned int id_) { objects[id_]->remove(); }
//	bool existsObject(unsigned int id_) { return objects.count(id_) > 0 && !objects[id_]->isRemoved; }
    
    int getNumObjects(){return (int)objects.size(); };
    int getNumVoxels(){return (int)voxels.size(); };

    Palette palette;

private:
	std::string version;
	std::map<unsigned int, Voxel*> voxels;
	std::map<unsigned int, Object*> objects;
    
	FavReader* fav_reader;
	FavWriter* fav_writer;

};

