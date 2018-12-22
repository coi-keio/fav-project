//
//  Voxel.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include "Metadata.h"
#include "./Primitive/FavPrimitive.h"
#include "./Primitive/Color.h"


namespace FavLibrary
{
	class Fav;

    class IDll VoxelInfo 
    {    
    public:
        VoxelInfo();
        VoxelInfo(unsigned int id_);
        virtual ~VoxelInfo();

        virtual unsigned int getId();
        virtual void setId(unsigned int id_);

    private:
        unsigned int identifier;
    };


    class IDll GeometryInfo : public VoxelInfo 
    {
    public:
        GeometryInfo();
        GeometryInfo(unsigned int id_);
        ~GeometryInfo();
    };


    class IDll MaterialInfo : public VoxelInfo 
    {
    public:
        MaterialInfo();
        MaterialInfo(unsigned int id_);
        MaterialInfo(unsigned int id_, double ratio_);
        ~MaterialInfo();

        double getRatio();
        void setRatio(double ratio_);

    private:
        double ratio = 1.0;
    };


    class IDll Voxel : public FavPrimitive, MetadataObject
    {
    public:
        Voxel();
        Voxel(unsigned int id_);
        Voxel(std::string name_);
        Voxel(unsigned int id_, std::string name_);
        ~Voxel();

        //copy constractor 
        Voxel(const Voxel &src);
        Voxel &operator=(const Voxel &src);
        void copy(const Voxel &src);
    
        void setGeometryInfo(GeometryInfo geometry_info_);
        GeometryInfo getGeometryInfo() const ;

        std::vector<MaterialInfo> getMaterialInfo() const;
        MaterialInfo getMaterialInfo(unsigned int id_) const ;
        void addMaterialInfo(unsigned int id_, double ratio_);
        void unpdateMaterialInfo(unsigned int id_, double ratio_);
        void removeMaterialInfo(unsigned int id_);
        bool existsMaterialInfo(unsigned int id_);
        int getNumMaterialInfo() const ;
        ColorRGBA getDisplay();
        void setDisplay(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_);
        void setDisplay(ColorRGBA color_);

        unsigned char getDisplayR();
        void setDisplayR(unsigned char r_);
        unsigned char getDisplayG();
        void setDisplayG(unsigned char g_);
        unsigned char getDisplayB();
        void setDisplayB(unsigned char b_);
        unsigned char getDisplayA();
        void setDisplayA(unsigned char a_);

		void setReferencePath(std::string reference_path, std::string favfile_dirpath);

        std::string getApplicationNote() const ;
        void setApplicationNote(std::string note_);

		std::string getReferencePath() const ;

    private:		
		//for standard voxel
        GeometryInfo geometry_info;
        std::vector<MaterialInfo> material_info;
        ColorRGBA display;
        std::string application_note;
		
		//for reference voxel
		std::string m_reference_path;
		Fav        *m_reference_fav ; 
    };


}
