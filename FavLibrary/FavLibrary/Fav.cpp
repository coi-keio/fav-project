//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include "Fav.h"
#include "FavWriter.h"
#include "FavReader.h"

namespace FavLibrary
{
	Fav::Fav() {
	}

	Fav::~Fav() {
		//    delete metadata;
        
//        if(palette != NULL){
//            delete palette;
//            palette = NULL;
//        }
        
//        for(std::map<unsigned int, Object*>::iterator it = objects.begin(); it != objects.end();){
//            if(it->second != NULL){
//                delete it->second;
//                it->second = NULL;
//            }
//            it++;
//        }
        
        objects.clear();
        voxels.clear();
//        for(std::map<unsigned int, Voxel*>::iterator it = voxels.begin(); it != voxels.end();){
//            if(it->second != NULL){
//                delete it->second;
//                it->second = NULL;
//            }
//            it++;
//        }
	}

	bool Fav::read(const char* file_path) {

		FavReader fav_reader(this);
		return fav_reader.read(file_path);
	}

	bool Fav::write(const char* file_path, CompressionMode compression_mode_) {

		FavWriter fav_writer(this);
		return fav_writer.write(file_path, compression_mode_);
	}

	std::vector<Voxel> Fav::getVoxels()
	{
		std::vector<Voxel> res;
		std::for_each(voxels.begin(), voxels.end(),
			[&](const std::pair<const Voxel, Voxel>& ref) { res.push_back(ref.second); });
		return res;
	}
    
	Voxel Fav::getVoxel(unsigned int id_)
	{
		Voxel res = NULL;
		if (voxels.count(id_) > 0)
			res = voxels[id_];

		return res;
	}
	void Fav::addVoxel(Voxel voxel_) { voxels[voxel_.getId()] = voxel_; };
	void Fav::removeVoxel(unsigned int id_) { voxels.erase(id_); }
	bool Fav::existsVoxel(unsigned int id_) { return voxels.count(id_) > 0; }

	std::map<unsigned int, Object> Fav::getObjects()
	{
		return objects;
	};
	Object Fav::getObject(unsigned int id_)
	{
		Object res = NULL;
		if (objects.count(id_) > 0)
			res = objects[id_];

		return res;
	}
    void Fav::addObject(Object object_) {
        objects[object_.getId()] = object_;
        objects[object_.getId()].structure.setGridPointer(&objects[object_.getId()].grid);
    };
    
	void Fav::removeObject(unsigned int id_) { objects.erase(id_); }

	int Fav::getNumObjects() { return (int)objects.size(); };
	int Fav::getNumVoxels() { return (int)voxels.size(); };
}