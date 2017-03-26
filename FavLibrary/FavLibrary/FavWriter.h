//
//  FavWriter.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

//#ifndef __FavLibrary__FavWriter__
//#define __FavLibrary__FavWriter__
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>


#include "FavSettings.h"
#include "Metadata.h"
#include "Voxel.h"
#include "./Palette/Palette.h"
#include "./Palette/Geometry.h"
#include "./Object/Object.h"
#include "./Object/Structure.h"

using namespace xercesc;

namespace FavLibrary
{
    RefClass Fav;
    
    RefClass FavWriter {
        
    public:
        
        FavWriter(Fav* fav_);
        bool write(const char* file_path);
        bool write(const char* file_path, CompressionMode compression_mode_);
        bool write(const char* file_path, const char* version);
        
    private:
        
        void appendCDATA (DOMElement* parent_elem, const char* child_elem_name, XMLCh*      text);
        void appendCDATA (DOMElement* parent_elem, const char* child_elem_name, const char* text);
        void appendCDATA (DOMElement* parent_elem, const char* child_elem_name, std::string text);
        void appendText  (DOMElement* parent_elem, const char* child_elem_name, const char* text);
        void appendText  (DOMElement* parent_elem, const char* child_elem_name, std::string text);
        void setAttribute(DOMElement* elem, const char* attr_name, const char* attr_value);
        void setAttribute(DOMElement* elem, const char* attr_name, std::string attr_value);
        
        void writeMetadata (DOMElement* parent_elem);
        void writePalette  (DOMElement* parent_elem);
        void writeVoxel    (DOMElement* parent_elem);
        void writeObject   (DOMElement* parent_elem);
        void writeGrid     (DOMElement* parent_elem, Grid* p_grid);
        void writeStructure(DOMElement* parent_elem, Structure* p_structure);
        void writeVoxelMap (DOMElement* parent_elem, Structure* p_structure);
        void writeColorMap (DOMElement* parent_elem, Structure* p_structure);
        void writeColorMapRGB (DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapRGBA(DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapCMYK(DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapGrayScale  (DOMElement *cmap_elem, Structure* p_structure);
        void writeColorMapGrayScale16(DOMElement *cmap_elem, Structure* p_structure);

        void writeXML      (const char* filePath);
        
        void str2bin(const unsigned char *str, unsigned char *hex, int len);
        void BytesFromHexString(unsigned char *data, const char *string);
        void deleteNewLine(std::string &targetStr);
        
        Fav* fav;
        DOMDocument *doc;
        CompressionMode compression_mode;
    };
    
}
//#endif /* defined(__FavLibrary__FavWriter__) */
