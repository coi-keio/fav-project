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
	}

	bool Fav::read(const char* file_path) {

		fav_reader = new FavReader(this);
		fav_reader->read(file_path);
		delete fav_reader;

		return 1;
	}

	bool Fav::write(const char* file_path, const char* version_) {

		fav_writer = new FavWriter(this);
		fav_writer->write(file_path, version_);
		delete fav_writer;

		return 1;
	}

	std::vector<Voxel> Fav::getVoxels()
	{
		std::vector<Voxel> res;
		//		std::for_each(voxels.begin(), voxels.end(),
		//			[&](const std::pair<const Voxel, Voxel>& ref) { res.push_back(ref.second); });
		return res;
	};
	Voxel Fav::getVoxel(unsigned int id_)
	{
		Voxel res;// = nullptr;
		if (voxels.count(id_) > 0 && !voxels[id_]->isRemoved())
			res = *voxels[id_];

		return res;
	};
	void Fav::addVoxel(Voxel* voxel_) { voxels[voxel_->getId()] = voxel_; };
	void Fav::removeVoxel(unsigned int id_) { voxels[id_]->remove(); }
	bool Fav::existsVoxel(unsigned int id_) { return voxels.count(id_) > 0 && !voxels[id_]->isRemoved(); }

	std::vector<Object> Fav::getObjects()
	{
		std::vector<Object> res;
		//		std::for_each(objects.begin(), objects.end(),
		//			[&](const std::pair<const Object, Object>& ref) { res.push_back(ref.second); });
		return res;
	};
	Object Fav::getObject(unsigned int id_)
	{
		Object res;// = nullptr;
		if (objects.count(id_) > 0 && !objects[id_]->isRemoved())
			res = *objects[id_];

		return res;
	};
	void Fav::addObject(Object* object_) { objects[object_->getId()] = object_; };
	void Fav::removeObject(unsigned int id_) { objects[id_]->remove(); }
	//	bool existsObject(unsigned int id_) { return objects.count(id_) > 0 && !objects[id_]->isRemoved; }

	int Fav::getNumObjects() { return (int)objects.size(); };
	int Fav::getNumVoxels() { return (int)voxels.size(); };
}