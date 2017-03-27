//
//  Structure.cpp
//  FavLibraryDotNet
//
//  Created by atsmsmr on 2016/12/02.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "Structure.h"
#include "Object.h"
#include "Grid.h"

namespace FavLibraryDotNet
{
	template <typename tVoxelMapType>
	VoxelMap<tVoxelMapType>::VoxelMap(int size) {
		number_of_voxels = size;
		data = new tVoxelMapType[size];
	};

	template <typename tVoxelMapType>
	void VoxelMap<tVoxelMapType>::init() {
		data = new tVoxelMapType[number_of_voxels];
		for (int i = 0; i < number_of_voxels; ++i) {
			data[i] = (tVoxelMapType)20;
		}
	};

	template <typename tVoxelMapType>
	void VoxelMap<tVoxelMapType>::setVoxel(int index_, int value_) {
		data[index_] = (tVoxelMapType)value_;
	};

	template <typename tVoxelMapType>
	tVoxelMapType VoxelMap<tVoxelMapType>::getVoxel(int index_) {
		return data[index_];
	}

	Structure::Structure(Grid* grid_) {
		grid = grid_;
		number_of_voxels = grid->getDimensionX() * grid->getDimensionY() * grid->getDimensionZ();
	}

	Structure::Structure(int bit_per_voxel_) {

		bit_per_voxel = bit_per_voxel_;
		number_of_voxels = 100000;

		initVoxelMap();
		color_mode = ColorMode::None;

	};

	Structure::Structure(int bit_per_voxel_, ColorMode color_mode_) {

		bit_per_voxel = bit_per_voxel_;
		color_mode = color_mode_;
		number_of_voxels = 100000000;

		initVoxelMap();
		initColorMap();

	};

	Structure::~Structure() {
		delete[] voxel_map;
		voxel_map = nullptr;
	}

	void Structure::initVoxelMap() {

		if (bit_per_voxel == 4 || bit_per_voxel == 8) {
			voxel_map = new VoxelMap<unsigned char>(number_of_voxels);
			voxel_map->init();
		}
		else if (bit_per_voxel == 16) {
			voxel_map_16bit = new VoxelMap<unsigned short>(number_of_voxels);
			voxel_map_16bit->init();
		}

	}

	void Structure::initColorMap(ColorMode color_mode_) {
		color_mode = color_mode_;
		initColorMap();
	}

	void Structure::initColorMap() {

		if (color_mode == ColorMode::RGB) color_map = new unsigned char[number_of_voxels * 3];
		else if (color_mode == ColorMode::RGBA) { color_map = new unsigned char[number_of_voxels * 3]; alpha_map = new unsigned char[number_of_voxels]; }
		else if (color_mode == ColorMode::CMYK) color_map = new unsigned char[number_of_voxels * 4];
		else if (color_mode == ColorMode::Grayscale) color_map = new unsigned char[number_of_voxels];
		else if (color_mode == ColorMode::Grayscale16) color_map_16bit = new unsigned short[number_of_voxels];

	}

	void Structure::setVoxel(int index_, int value_) {
		voxel_map->setVoxel(index_, value_);
	};

	void Structure::setVoxel(Point3D p_, int value_) {};
	void Structure::setVoxel(int x_, int y_, int z_, int value_) {

		int index = getIndex(x_, y_, z_);

		if (bit_per_voxel == 4 || bit_per_voxel == 8) voxel_map->setVoxel(index, value_);
		else if (bit_per_voxel == 16) voxel_map_16bit->setVoxel(index, value_);

	};

	//int Structure::getVoxel(Point p_){};
	int Structure::getVoxel(int x_, int y_, int z_) {

		int index = getIndex(x_, y_, z_);
		int value;
		if (bit_per_voxel == 4 || bit_per_voxel == 8) {
			value = voxel_map->getVoxel(index);
		}
		else if (bit_per_voxel == 16) value = voxel_map_16bit->getVoxel(index);

		return (int)value;
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorRGB color_) {
		int index = getIndex(x_, y_, z_);
		if (color_mode != ColorMode::RGB) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
			color_map[index * 3] = color_.getR();
			color_map[index * 3 + 1] = color_.getG();
			color_map[index * 3 + 2] = color_.getB();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorRGBA color_) {
		int index = getIndex(x_, y_, z_);
		if (color_mode != ColorMode::RGBA) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
			color_map[index * 4] = color_.getR();
			color_map[index * 4 + 1] = color_.getG();
			color_map[index * 4 + 2] = color_.getB();
			color_map[index * 4 + 3] = color_.getA();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorCMYK color_) {
		int index = getIndex(x_, y_, z_);
		if (color_mode != ColorMode::CMYK) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
			color_map[index * 4] = color_.getC();
			color_map[index * 4 + 1] = color_.getM();
			color_map[index * 4 + 2] = color_.getY();
			color_map[index * 4 + 3] = color_.getK();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorGrayscale color_) {
		int index = getIndex(x_, y_, z_);
		if (color_mode != ColorMode::Grayscale) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
			color_map[index] = color_.getGray();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorGrayscale16 color_) {
		int index = getIndex(x_, y_, z_);
		if (color_mode != ColorMode::Grayscale16) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
			color_map[index] = color_.getGray();
		}
	};


	//ColorRGB Structure::getColorRGB(int x_, int y_, int z_){
	//    int index = getIndex(x_, y_, z_);
	//    return ColorRGB(color_map[index*3], color_map[index*3+1], color_map[index*3+2]);
	//};

	//ColorRGBA Structure::getColorRGBA(int x_, int y_, int z_){
	//    int index = getIndex(x_, y_, z_);
	//    return ColorRGBA(color_map[index*4], color_map[index*4+1], color_map[index*4+2], color_map[index*4+3]);
	//};

	//ColorCMYK Structure::getColorCMYK(int x_, int y_, int z_){
	//    int index = getIndex(x_, y_, z_);
	//    return ColorCMYK(color_map[index*4], color_map[index*4+1], color_map[index*4+2], color_map[index*4+3]);
	//};

	//ColorGrayScale Structure::getColorGrayScale(int x_, int y_, int z_){
	//    int index = getIndex(x_, y_, z_);
	//    return ColorGrayScale(color_map[index]);
	//};

	int Structure::getIndex(int x_, int y_, int z_) {
		int ret = x_ + grid->getDimensionX() * y_ + grid->getDimensionX() * grid->getDimensionY() * z_;
		return ret;
		//    return x_ + grid->dimension.getX() * y_ + grid->dimension.getX() * grid->dimension.getY() * z_;
	}
}