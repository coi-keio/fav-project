//
//  Structure.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/02.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "Structure.h"
#include "Object.h"
#include "Grid.h"

//TODO: implement changeColorMap*()
namespace FavLibrary
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
			data[i] = (tVoxelMapType)0;
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

	Structure::~Structure() {
        
        if(voxel_map != NULL){
            delete[] voxel_map;
            voxel_map = nullptr;
        }
        
        if(voxel_map_16bit != NULL){
            delete[] voxel_map_16bit;
            voxel_map_16bit = nullptr;
        }
        
        if(color_map != NULL){
            delete[] color_map;
            color_map = nullptr;
        }
        
        if(color_map_16bit != NULL){
            delete[] color_map_16bit;
            color_map_16bit = nullptr;
        }
        
        if(alpha_map != NULL){
            delete[] alpha_map;
            alpha_map = nullptr;
        }
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
        
        switch(color_mode){
                
            case ColorMode::RGB:
                color_map = new unsigned char[number_of_voxels * 3];
                break;
                
            case ColorMode::RGBA:
                color_map = new unsigned char[number_of_voxels * 3];
                alpha_map = new unsigned char[number_of_voxels];
                break;
                
            case ColorMode::CMYK:
                color_map = new unsigned char[number_of_voxels * 3];
                break;
                
            case ColorMode::Grayscale:
                color_map = new unsigned char[number_of_voxels];
                break;
                
            case ColorMode::Grayscale16:
                color_map_16bit = new unsigned short[number_of_voxels];
                break;
            
            default:
                //TODO: エラー処理
                break;
        }
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

	int Structure::getVoxel(Point3D p_){
        return getVoxel(p_.getX(), p_.getY(), p_.getZ());
    };
    
	int Structure::getVoxel(int x_, int y_, int z_) {

		int index = getIndex(x_, y_, z_);
		int value;
		
        if (bit_per_voxel == 4 || bit_per_voxel == 8) {
			value = voxel_map->getVoxel(index);
		}
        else if (bit_per_voxel == 16) {
            value = voxel_map_16bit->getVoxel(index);
        }
        
		return value;
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorRGB color_) {
		
        if (color_mode != ColorMode::RGB) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
            int index = getIndex(x_, y_, z_);
			color_map[index * 3]     = color_.getR();
			color_map[index * 3 + 1] = color_.getG();
			color_map[index * 3 + 2] = color_.getB();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorRGBA color_) {

        if (color_mode != ColorMode::RGBA) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
            int index = getIndex(x_, y_, z_);
			color_map[index * 3]     = color_.getR();
			color_map[index * 3 + 1] = color_.getG();
			color_map[index * 3 + 2] = color_.getB();
			alpha_map[index]         = color_.getA();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorCMYK color_) {
		
        if (color_mode != ColorMode::CMYK) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
            int index = getIndex(x_, y_, z_);
			color_map[index * 4]     = color_.getC();
			color_map[index * 4 + 1] = color_.getM();
			color_map[index * 4 + 2] = color_.getY();
			color_map[index * 4 + 3] = color_.getK();
		}
	};
    
    void Structure::setColor(int x_, int y_, int z_, int gray_){
        
        if (color_mode == ColorMode::Grayscale){
            
            if(gray_<=256){
                int index = getIndex(x_, y_, z_);
                color_map[index] = gray_;
            }else{
                std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
            }
        }
        else if(color_mode == ColorMode::Grayscale16){
            int index = getIndex(x_, y_, z_);
            color_map_16bit[index] = gray_;
        }
        else{
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
    }

	void Structure::setColor(int x_, int y_, int z_, class ColorGrayscale color_) {

        if (color_mode != ColorMode::Grayscale) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
            int index = getIndex(x_, y_, z_);
			color_map[index] = color_.getGray();
		}
	};

	void Structure::setColor(int x_, int y_, int z_, class ColorGrayscale16 color_) {

        if (color_mode != ColorMode::Grayscale16) {
			std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
		}
		else {
            int index = getIndex(x_, y_, z_);
			color_map_16bit[index] = color_.getGray();
		}
	};
    
    void Structure::setColorRed(int x_, int y_, int z_, int r_){
        if (color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3] = r_;
        }
    }
    
    void Structure::setColorGreen(int x_, int y_, int z_, int g_){
        if (color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3+1] = g_;
        }
    }
    
    void Structure::setColorBlue(int x_, int y_, int z_, int b_){
        if (color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3+2] = b_;
        }
    }
    
    void Structure::setColorAlpha(int x_, int y_, int z_, int a_){
        if (color_mode != ColorMode::RGBA) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            alpha_map[index] = a_;
        }
    }
    
    void Structure::setColorCyan(int x_, int y_, int z_, int c_){
        if (color_mode != ColorMode::CMYK) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3] = c_;
        }
    }
    
    void Structure::setColorMagenta(int x_, int y_, int z_, int m_){
        if (color_mode != ColorMode::CMYK) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3+1] = m_;
        }
    }
    
    void Structure::setColorYellow(int x_, int y_, int z_, int value_){
        if (color_mode != ColorMode::CMYK) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3+2] = value_;
        }
    }
    
    void Structure::setColorKeyPlate(int x_, int y_, int z_, int k_){
        if (color_mode != ColorMode::CMYK) {
            std::cerr << "The input color is not compatible with current Color-Mode" << std::endl;
        }
        else {
            int index = getIndex(x_, y_, z_);
            color_map[index * 3] = k_;
        }
    }

    int Structure::getColorRed  (FavLibrary::Point3D p_){ return getColorRed  (p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorGreen(FavLibrary::Point3D p_){ return getColorGreen(p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorBlue (FavLibrary::Point3D p_){ return getColorBlue (p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorAlpha(FavLibrary::Point3D p_){ return getColorAlpha(p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorCyan    (FavLibrary::Point3D p_){ return getColorCyan    (p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorMagenta (FavLibrary::Point3D p_){ return getColorMagenta (p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorYellow  (FavLibrary::Point3D p_){ return getColorYellow  (p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorKeyPlate(FavLibrary::Point3D p_){ return getColorKeyPlate(p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorGrayScale  (FavLibrary::Point3D p_){ return getColorGrayScale  (p_.getX(), p_.getY(), p_.getZ()); };
    int Structure::getColorGrayScale16(FavLibrary::Point3D p_){ return getColorGrayScale16(p_.getX(), p_.getY(), p_.getZ()); };
    
    int Structure::getColorRed(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*3];
        }
    }
    
    int Structure::getColorGreen(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*3+1];
        }
    }
    
    int Structure::getColorBlue(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*3+2];
        }
    }
    
    int Structure::getColorAlpha(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGBA){
            //TODO: エラー処理
            return NULL;
        }else{
            return alpha_map[getIndex(x_, y_, z_)];
        }
    }
    
    int Structure::getColorCyan(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*4];
        }
    }
    
    int Structure::getColorMagenta(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*4+1];
        }
    }
    
    int Structure::getColorYellow(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*4+2];
        }
    }
    
    int Structure::getColorKeyPlate(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)*4+3];
        }
    }
    
    int Structure::getColorGrayScale(int x_, int y_, int z_){
        if(color_mode != ColorMode::Grayscale){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map[getIndex(x_, y_, z_)];
        }
    }
    
    int Structure::getColorGrayScale16(int x_, int y_, int z_){
        if(color_mode != ColorMode::Grayscale16){
            //TODO: エラー処理
            return NULL;
        }else{
            return color_map_16bit[getIndex(x_, y_, z_)];
        }
    }

	ColorRGB Structure::getColorRGB(int x_, int y_, int z_){
	    int index = getIndex(x_, y_, z_);
	    return ColorRGB(color_map[index*3], color_map[index*3+1], color_map[index*3+2]);
	};

	ColorRGBA Structure::getColorRGBA(int x_, int y_, int z_){
	    int index = getIndex(x_, y_, z_);
	    return ColorRGBA(color_map[index*3], color_map[index*3+1], color_map[index*3+2], alpha_map[index]);
	};

	ColorCMYK Structure::getColorCMYK(int x_, int y_, int z_){
	    int index = getIndex(x_, y_, z_);
	    return ColorCMYK(color_map[index*4], color_map[index*4+1], color_map[index*4+2], color_map[index*4+3]);
	};

	int Structure::getIndex(int x_, int y_, int z_) {
		int ret = x_ + grid->getDimensionX() * y_ + grid->getDimensionX() * grid->getDimensionY() * z_;
		return ret;
		//    return x_ + grid->dimension.getX() * y_ + grid->dimension.getX() * grid->dimension.getY() * z_;
	}
}