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
//	template <typename tVoxelMapType>
//	VoxelMap<tVoxelMapType>::VoxelMap(int size) {
//		number_of_voxels = size;
//		data = new tVoxelMapType[size];
//	};
//    
//    template <typename tVoxelMapType>
//    VoxelMap<tVoxelMapType>::~VoxelMap() {
//            delete[] data;
//            data = nullptr;
//    };
//
//	template <typename tVoxelMapType>
//	void VoxelMap<tVoxelMapType>::init() {
//		data = new tVoxelMapType[number_of_voxels];
//		for (int i = 0; i < number_of_voxels; ++i) {
//			data[i] = (tVoxelMapType)0;
//		}
//	};
//
//	template <typename tVoxelMapType>
//	void VoxelMap<tVoxelMapType>::setVoxel(int index_, int value_) {
//		data[index_] = (tVoxelMapType)value_;
//	};
//
//	template <typename tVoxelMapType>
//	tVoxelMapType VoxelMap<tVoxelMapType>::getVoxel(int index_) {
//		return data[index_];
//	}

//	Structure::Structure(Grid* grid_) {
//		grid = grid_;
//		number_of_voxels = grid->getDimensionX() * grid->getDimensionY() * grid->getDimensionZ();
//	}

	Structure::~Structure() {
        
//        if(voxel_map != NULL){
//            delete[] voxel_map;
//            voxel_map = NULL;
//        }
//        
//        if(voxel_map_16bit != NULL){
//            delete[] voxel_map_16bit;
//            voxel_map_16bit = NULL;
//        }
        
//        if(color_map != NULL){
//            delete[] color_map;
//            color_map = NULL;
//        }
//        if(color_map_16bit != NULL){
//            delete[] color_map_16bit;
//            color_map_16bit = NULL;
//        }
//        
//        if(alpha_map != NULL){
//            delete[] alpha_map;
//            alpha_map = NULL;
//        }
        
	}

	void Structure::initVoxelMap() {

        number_of_voxels = grid->getDimensionX() * grid->getDimensionY() * grid->getDimensionZ();
        
        switch (bit_per_voxel) {
                
            case BitPerVoxel::Bit4:
            case BitPerVoxel::Bit8:
                
                voxel_map.resize(number_of_voxels);
                
                break;
                
            case BitPerVoxel::Bit16:
                
                voxel_map_16bit.resize(number_of_voxels);
                
                break;
                
            default:
                //TODO: エラー
                break;
        }

	}

	void Structure::initColorMap(ColorMode color_mode_) {
		color_mode = color_mode_;
		initColorMap();
	}

	void Structure::initColorMap() {
        
        number_of_voxels = grid->getDimensionX() * grid->getDimensionY() * grid->getDimensionZ();
        
        color_map.clear();
        color_map_16bit.clear();
        alpha_map.clear();
        
        switch(color_mode){
                
            case ColorMode::RGB:
                color_map.resize(number_of_voxels * 3);
                break;
                
            case ColorMode::RGBA:
                color_map.resize(number_of_voxels * 3);
                alpha_map.resize(number_of_voxels);
                break;
                
            case ColorMode::CMYK:
                color_map.resize(number_of_voxels * 3);
                break;
                
            case ColorMode::Grayscale:
                color_map.resize(number_of_voxels);
                break;
                
            case ColorMode::Grayscale16:
                color_map_16bit.resize(number_of_voxels);
                break;
                
            default:
                //TODO: エラー処理
                break;
        }
	}
    
    void Structure::convertVoxelMapToVoxelMap16Bit(){
        
        if(bit_per_voxel == BitPerVoxel::Bit4 || bit_per_voxel == BitPerVoxel::Bit8){
            
            voxel_map_16bit.clear();
            voxel_map_16bit.resize(number_of_voxels);
            
            for(int i=0; i<number_of_voxels; ++i){
                voxel_map_16bit[i] = voxel_map[i];
            }
            
            voxel_map.clear();
        }
        
    }
    
    void Structure::convertVoxelMap16BitToVoxelMap(){
        
        if(bit_per_voxel == BitPerVoxel::Bit16){
            
            voxel_map.clear();
            voxel_map.resize(number_of_voxels);
            
            for(int i=0; i<number_of_voxels; ++i){
                voxel_map[i] = (unsigned char) voxel_map_16bit[i];
            }
            
            voxel_map_16bit.resize(number_of_voxels);
        }
    }
    
    void Structure::setBitPerVoxel(BitPerVoxel bit_per_voxel_) {
        
        switch (bit_per_voxel_) {
                
            case BitPerVoxel::Bit4:
            case BitPerVoxel::Bit8:
                
                convertVoxelMapToVoxelMap16Bit();
                bit_per_voxel = bit_per_voxel_;

                break;
                
            case BitPerVoxel::Bit16:
                
                convertVoxelMap16BitToVoxelMap();
                bit_per_voxel = bit_per_voxel_;

                break;
            default:
                //TODO: error
                break;
        }
        
        
    };

	void Structure::setVoxel(int index_, int value_) {
        
        if(bit_per_voxel == BitPerVoxel::Bit4  || bit_per_voxel == BitPerVoxel::Bit8)
            voxel_map[index_] = value_;
        else
            voxel_map_16bit[index_] = value_;

	};

	void Structure::setVoxel(Point3D p_, int value_) {
        setVoxel((int)p_.getX(), (int)p_.getY(), (int)p_.getZ(), value_);
    };
    
	void Structure::setVoxel(int x_, int y_, int z_, int value_) {

		int index = getIndex(x_, y_, z_);
		setVoxel(index, value_);

	};

    int Structure::getVoxel(int index_){
        
        if (bit_per_voxel == BitPerVoxel::Bit4 || bit_per_voxel == BitPerVoxel::Bit8)
            return voxel_map[index_];
        else
            return voxel_map_16bit[index_];
        
    };
    
	int Structure::getVoxel(Point3D p_){
        return getVoxel( (int)p_.getX(), (int)p_.getY(), (int)p_.getZ());
    };
    
	int Structure::getVoxel(int x_, int y_, int z_) {

		int index = getIndex(x_, y_, z_);
		int value = -1;
		
        value = getVoxel(index);
        
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

    int Structure::getColorRed     (FavLibrary::Point3D p_){ return getColorRed     ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorGreen   (FavLibrary::Point3D p_){ return getColorGreen   ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorBlue    (FavLibrary::Point3D p_){ return getColorBlue    ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorAlpha   (FavLibrary::Point3D p_){ return getColorAlpha   ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorCyan    (FavLibrary::Point3D p_){ return getColorCyan    ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorMagenta (FavLibrary::Point3D p_){ return getColorMagenta ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorYellow  (FavLibrary::Point3D p_){ return getColorYellow  ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorKeyPlate(FavLibrary::Point3D p_){ return getColorKeyPlate((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorGrayScale  (FavLibrary::Point3D p_){ return getColorGrayScale  ((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    int Structure::getColorGrayScale16(FavLibrary::Point3D p_){ return getColorGrayScale16((int)p_.getX(), (int)p_.getY(), (int)p_.getZ()); };
    
    int Structure::getColorRed(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*3];
        }
    }
    
    int Structure::getColorGreen(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*3+1];
        }
    }
    
    int Structure::getColorBlue(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGB && color_mode != ColorMode::RGBA){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*3+2];
        }
    }
    
    int Structure::getColorAlpha(int x_, int y_, int z_){
        if(color_mode != ColorMode::RGBA){
            //TODO: error handling
            return -1;
        }else{
            return alpha_map[getIndex(x_, y_, z_)];
        }
    }
    
    int Structure::getColorCyan(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*4];
        }
    }
    
    int Structure::getColorMagenta(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*4+1];
        }
    }
    
    int Structure::getColorYellow(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*4+2];
        }
    }
    
    int Structure::getColorKeyPlate(int x_, int y_, int z_){
        if(color_mode != ColorMode::CMYK){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)*4+3];
        }
    }
    
    int Structure::getColorGrayScale(int x_, int y_, int z_){
        if(color_mode != ColorMode::Grayscale){
            //TODO: error handling
            return -1;
        }else{
            return color_map[getIndex(x_, y_, z_)];
        }
    }
    
    int Structure::getColorGrayScale16(int x_, int y_, int z_){
        if(color_mode != ColorMode::Grayscale16){
            //TODO: error handling
            return -1;
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
	}
    
    void Structure::convertRgbToCmyk(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned char> new_color_map(number_of_voxels * 4);
        int count = 0;
        for(int i=0; i<number_of_voxels*3; i=i+3){

            double red   = color_map[i];
            double green = color_map[i+1];
            double blue  = color_map[i+2];
            double black = std::min(1. - red / 255., std::min(1. - green / 255., 1. - blue / 255.));
            
             //FIXME: by 1.001, avoid to devide by zero.
            new_color_map[count*4]   = (unsigned char)(((1. - (red  / 255.) - black) / (1.0001 - black))*255);// Cyan
            new_color_map[count*4+1] = (unsigned char)(((1. - (green/ 255.) - black) / (1.0001 - black))*255);// Magenta
            new_color_map[count*4+2] = (unsigned char)(((1. - (blue / 255.) - black) / (1.0001 - black))*255);// Yellow
            new_color_map[count*4+3] = (unsigned char)(black*255);                                            // KeyPlate
            
            count++;
        }

        color_map.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::CMYK;
    };
    
    void Structure::convertRgbToGrayscale(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned char> new_color_map(number_of_voxels);
        int count = 0;
        for(int i=0; i<number_of_voxels*3; i=i+3){
            
            double red   = color_map[i];
            double green = color_map[i+1];
            double blue  = color_map[i+2];

            // covert by averageRGB
            new_color_map[count] = (unsigned char)int((red + green + blue)/3.);
            
            count++;
        }
        
        color_map.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::Grayscale;
    };
    
    void Structure::convertRgbToGrayscale16(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned short> new_color_map(number_of_voxels);

        int count = 0;
        for(int i=0; i<number_of_voxels*3; i=i+3){
            
            double red   = color_map[i];
            double green = color_map[i+1];
            double blue  = color_map[i+2];
            
            // covert by averageRGB
            new_color_map[count] = (unsigned short)int((red + green + blue)/3.);
            
            count++;
        }
        
        color_map_16bit.clear();
        color_map_16bit = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::Grayscale16;
    };
    
    void Structure::convertCmykToRgb(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned char> new_color_map(number_of_voxels*3);

        int count = 0;
        
        for(int i=0; i<number_of_voxels*4; i=i+4){
            
            double cyan    = color_map[i];
            double magenta = color_map[i+1];
            double yellow  = color_map[i+2];
            double black   = color_map[i+3];
            
            new_color_map[count*3]   = (int)((1 - std::min(1., cyan    * (1. - black) + black)) * 255.);// Red
            new_color_map[count*3+1] = (int)((1 - std::min(1., magenta * (1. - black) + black)) * 255.);// Green
            new_color_map[count*3+2] = (int)((1 - std::min(1., yellow  * (1. - black) + black)) * 255.);// Blue
            
            count++;
        }
        
        color_map.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::RGB;

    };
    
    void Structure::convertCmykToGrayscale(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned char> new_color_map(number_of_voxels);

        int count = 0;
        
        for(int i=0; i<number_of_voxels*4; i=i+4){
            
            double cyan    = color_map[i];
            double magenta = color_map[i+1];
            double yellow  = color_map[i+2];
            double black   = color_map[i+3];
            
            double red   = ((1 - std::min(1., cyan    * (1. - black) + black)) * 255.);// Red
            double green = ((1 - std::min(1., magenta * (1. - black) + black)) * 255.);// Green
            double blue  = ((1 - std::min(1., yellow  * (1. - black) + black)) * 255.);// Blue
            
            new_color_map[count] = (unsigned char)int((red + green + blue)/3.);
            
            count++;
        }
        
        color_map.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::Grayscale;
        
    };
    
    void Structure::convertCmykToGrayscale16(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned short> new_color_map(number_of_voxels);

        int count = 0;
        
        for(int i=0; i<number_of_voxels*4; i=i+4){
            
            double cyan    = color_map[i];
            double magenta = color_map[i+1];
            double yellow  = color_map[i+2];
            double black   = color_map[i+3];
            
            double red   = ((1 - std::min(1., cyan    * (1. - black) + black)) * 255.);// Red
            double green = ((1 - std::min(1., magenta * (1. - black) + black)) * 255.);// Green
            double blue  = ((1 - std::min(1., yellow  * (1. - black) + black)) * 255.);// Blue
            
            new_color_map[count] = (unsigned char)int((red + green + blue)/3.);
            
            count++;
        }
        
        color_map.clear();
        color_map_16bit = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::Grayscale16;
        
    };
    
    void Structure::convertGrayscaleToRgb(){
        
        std::vector<unsigned char> new_color_map(number_of_voxels*3);

        int count = 0;
        
        for(int i=0; i<number_of_voxels; ++i){
            
            unsigned char gray = color_map[i];
            
            new_color_map[count*3+0] = gray;// Red
            new_color_map[count*3+1] = gray;// Green
            new_color_map[count*3+2] = gray;// Blue
            
            count++;
        }
        
        color_map.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::RGB;

    };
    
    void Structure::convertGrayscaleToCmyk(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned char> new_color_map(number_of_voxels*4);

        int count = 0;
        
        for(int i=0; i<number_of_voxels; ++i){
            
            double red   = color_map[i];
            double green = color_map[i];
            double blue  = color_map[i];
            double black = std::min(1. - red / 255., std::min(1. - green / 255., 1. - blue / 255.));
            
            //FIXME: by 1.001, avoid to devide by zero.
            new_color_map[count*4]   = (unsigned char)(((1. - (red  / 255.) - black) / (1.0001 - black))*255);// Cyan
            new_color_map[count*4+1] = (unsigned char)(((1. - (green/ 255.) - black) / (1.0001 - black))*255);// Magenta
            new_color_map[count*4+2] = (unsigned char)(((1. - (blue / 255.) - black) / (1.0001 - black))*255);// Yellow
            new_color_map[count*4+3] = (unsigned char)(black*255);                                            // KeyPlate
            
            count++;
        }
        
        color_map.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::CMYK;
        
    };
    
    void Structure::convertGrayscaleToGrayscale16(){
        
        std::vector<unsigned short> new_color_map(number_of_voxels);

        int count = 0;
        for(int i=0; i<number_of_voxels; ++i){
            
            double gray   = color_map[i];
            
            new_color_map[count] = (unsigned short)int(gray*255.);
            
            count++;
        }
        
        color_map.clear();
        color_map_16bit = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::Grayscale16;
    };
    
    void Structure::convertGrayscale16ToRgb(){
        
        std::vector<unsigned char> new_color_map(number_of_voxels*3);

        int count = 0;
        
        for(int i=0; i<number_of_voxels; ++i){
            
            double gray16 = color_map[i];
            
            new_color_map[count*3]   = (unsigned char)int(gray16/255.);// Red
            new_color_map[count*3+1] = (unsigned char)int(gray16/255.);// Green
            new_color_map[count*3+2] = (unsigned char)int(gray16/255.);// Blue
            
            count++;
        }
        
        
        color_map_16bit.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::RGB;

    };
    
    void Structure::convertGrayscale16ToCmyk(){
        
        // http://www.technotype.net/tutorial/tutorial.php?fileId=%7BImage%20processing%7D&sectionId=%7Bconverting-between-rgb-and-cmyk-color-space%7D
        // FIXME: 不可逆変換のアルゴリズムなので、もっと良い変換アルゴリズムに置き換えるべき
        std::vector<unsigned char> new_color_map(number_of_voxels*4);

        int count = 0;
        
        for(int i=0; i<number_of_voxels; ++i){
            
            double red   = (double)color_map[i]/255.;
            double green = (double)color_map[i]/255.;
            double blue  = (double)color_map[i]/255.;
            double black = std::min(1. - red / 255., std::min(1. - green / 255., 1. - blue / 255.));
            
            //FIXME: by 1.001, avoid to devide by zero.
            new_color_map[count*4]   = (unsigned char)(((1. - (red  / 255.) - black) / (1.0001 - black))*255);// Cyan
            new_color_map[count*4+1] = (unsigned char)(((1. - (green/ 255.) - black) / (1.0001 - black))*255);// Magenta
            new_color_map[count*4+2] = (unsigned char)(((1. - (blue / 255.) - black) / (1.0001 - black))*255);// Yellow
            new_color_map[count*4+3] = (unsigned char)(black*255);                                            // KeyPlate
            
            count++;
        }
        
        color_map_16bit.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::CMYK;
        
    };
    
    void Structure::convertGrayscale16ToGrayscale(){
        
        std::vector<unsigned char> new_color_map(number_of_voxels);

        int count = 0;
        for(int i=0; i<number_of_voxels; ++i){
            
            double gray = color_map[i];
            
            new_color_map[count] = (unsigned char)int(gray*255.);
            
            count++;
        }
        
        color_map_16bit.clear();
        color_map = new_color_map;
        new_color_map.clear();
        color_mode = ColorMode::Grayscale;
    };
    
    
    void Structure::convertColorMapToRGB(){
    
        switch(color_mode){
                
            case ColorMode::RGB:
                break;
                
            case ColorMode::RGBA:
                
//                if(alpha_map != NULL){
//                    delete[] alpha_map;
//                    alpha_map = nullptr;
//                }
                break;
                
            case ColorMode::CMYK:
                convertCmykToRgb();
                break;
                
            case ColorMode::Grayscale:
                convertGrayscaleToRgb();
                break;
                
            case ColorMode::Grayscale16:
                convertGrayscale16ToRgb();
                break;
        }
        
        color_mode = ColorMode::RGB;

    };
    
    void Structure::convertColorMapToCMYK(){
        
        switch(color_mode){
                
            case ColorMode::RGB:
                convertRgbToCmyk();
                break;
                
            case ColorMode::RGBA:
                convertRgbToCmyk();
                alpha_map.clear();
                
                break;
                
            case ColorMode::CMYK:
                break;
                
            case ColorMode::Grayscale:
                convertGrayscaleToCmyk();
                break;
                
            case ColorMode::Grayscale16:
                convertGrayscale16ToCmyk();
                break;
                
        }
        
        color_mode = ColorMode::CMYK;
        
    };
    
    void Structure::convertColorMapToGrayscale(){
        
        switch(color_mode){
                
            case ColorMode::RGB:
                convertRgbToGrayscale();
                break;
                
            case ColorMode::RGBA:
                convertRgbToGrayscale();
                alpha_map.clear();

                break;
                
            case ColorMode::CMYK:
                convertCmykToGrayscale();
                break;
                
            case ColorMode::Grayscale:
                break;
                
            case ColorMode::Grayscale16:
                convertGrayscale16ToGrayscale();
                break;
                
        }
        
        color_mode = ColorMode::Grayscale;
        
    };
    
    void Structure::convertColorMapToGrayscale16(){
        
        switch(color_mode){
                
            case ColorMode::RGB:
                convertRgbToGrayscale16();
                break;
                
            case ColorMode::RGBA:
                convertRgbToGrayscale16();
                alpha_map.clear();
                break;
                
            case ColorMode::CMYK:
                convertCmykToGrayscale16();
                break;
                
            case ColorMode::Grayscale:
                convertGrayscaleToGrayscale16();
                break;
                
            case ColorMode::Grayscale16:
                break;
        }
        
        color_mode = ColorMode::Grayscale16;
        
    };
}
