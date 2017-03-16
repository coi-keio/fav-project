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
#include "../FavSettings.h"

namespace FavLibrary
{

	RefClass Object : public FavPrimitive, MetadataObject
	{
	public:
		Object();
		Object(unsigned int id_);
		Object(std::string name_);
		Object(unsigned int id_, std::string name_);

		~Object();

		void setStructure(Structure* structure_new_);

		/// この辺はStructureのメソッド呼ぶだけのショートカット
		//int* getVoxelMap();
		//int* getColorMap();
		//int* getLinkMap();

		//void setVoxelMap(int* voxel_map_); //grid infoと合わないデータが来た場合はエラーを返す。
		//void setColorMap(int* color_map_);
		//void setLinkMap(int* link_map_);

		Grid* grid;
		Structure* structure;

	private:
		Object* pObject;

	};

}