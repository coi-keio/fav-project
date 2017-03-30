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
        palette = new Palette;
	}

	Fav::~Fav() {
		//    delete metadata;
        delete palette;
        for(std::map<unsigned int, Object*>::iterator it = objects.begin(); it != objects.end();){
            if(it->second != NULL){
                delete it->second;
                it->second = nullptr;
            }
            it++;
        }
        objects.clear();
        
        for(std::map<unsigned int, Voxel*>::iterator it = voxels.begin(); it != voxels.end();){
            if(it->second != NULL){
                delete it->second;
                it->second = nullptr;
            }
            it++;
        }
	}

	bool Fav::read(const char* file_path) {

		fav_reader = new FavReader(this);
		fav_reader->read(file_path);
		delete fav_reader;
        fav_reader = nullptr;

		return 1;
	}

	bool Fav::write(const char* file_path, CompressionMode compression_mode_) {

		fav_writer = new FavWriter(this);
		fav_writer->write(file_path, compression_mode_);
		delete fav_writer;
        fav_writer = nullptr;
        
		return 1;
	}

	std::vector<Voxel*> Fav::getVoxels()
	{
		std::vector<Voxel*> res;
		//		std::for_each(voxels.begin(), voxels.end(),
		//			[&](const std::pair<const Voxel, Voxel>& ref) { res.push_back(ref.second); });
		return res;
	};
	Voxel* Fav::getVoxel(unsigned int id_)
	{
		Voxel* res = nullptr;
		if (voxels.count(id_) > 0 && !voxels[id_]->isRemoved())
			res = voxels[id_];

		return res;
	}
	void Fav::addVoxel(Voxel* voxel_) { voxels[voxel_->getId()] = voxel_; };
	void Fav::removeVoxel(unsigned int id_) { voxels[id_]->remove(); }
	bool Fav::existsVoxel(unsigned int id_) { return voxels.count(id_) > 0 && !voxels[id_]->isRemoved(); }

	std::map<unsigned int, Object*> Fav::getObjects()
	{
//		std::vector<Object> res;
		//		std::for_each(objects.begin(), objects.end(),
		//			[&](const std::pair<const Object, Object>& ref) { res.push_back(ref.second); });
		return objects;
	};
	Object* Fav::getObject(unsigned int id_)
	{
		Object* res = nullptr;
		// FIXME: 縺薙・isRemoved()縺ｧ繝√ぉ繝・け縺吶ｋ縺ｮ蠢・ｦ√↑縺ｮ縺具ｼ・縺ｩ縺｡繧峨↓縺帙ｈ縺薙・譖ｸ縺肴婿縺ｯ繧｢繧ｯ繧ｻ繧ｹ繧ｨ繝ｩ繝ｼ縺瑚ｵｷ縺阪≧繧九・masumori)
		//        縺ゅ→,object縺檎┌縺九▲縺溷ｴ蜷医↓遨ｺ繧定ｿ斐☆縺ｮ縺ｧ濶ｯ縺・・縺具ｼ溘
//		if (objects.count(id_) > 0 && !objects[id_]->isRemoved())
		if (objects.count(id_) > 0)

			res = objects[id_];

		return res;
	}
	void Fav::addObject(Object* object_) { objects[object_->getId()] = object_; };
	void Fav::removeObject(unsigned int id_) { objects[id_]->remove(); }
	//	bool existsObject(unsigned int id_) { return objects.count(id_) > 0 && !objects[id_]->isRemoved; }

	int Fav::getNumObjects() { return (int)objects.size(); };
	int Fav::getNumVoxels() { return (int)voxels.size(); };
}