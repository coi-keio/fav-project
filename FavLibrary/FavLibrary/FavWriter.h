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


#include "Metadata.h"
#include "Palette.h"
#include "Voxel.h"
#include "Object.h"

class Fav;
//class Metadata;
//class Palette;
//class Object;

using namespace xercesc;

class FavWriter{
public:
    FavWriter(Fav* fav_){ fav = fav_; };
    
    bool write(const char* file_path);
    void writeMetadata(DOMDocument *doc, DOMElement	*fav_elem, DOMElement *metadata_elem);
    void writeXML(xercesc::DOMDocument* pmyDOMDocument, const char *filePath);
    
    Fav* fav;

private:
//    Metadata testdata;
//    void writeMetaData();
    void writePalette();
    void writeVoxel();
    void writeObject();
    void writeGrid();
    void writeStructure();
    
};

//#endif /* defined(__FavLibrary__FavWriter__) */
