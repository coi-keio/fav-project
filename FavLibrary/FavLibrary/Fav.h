//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include "Metadata.h"
#include "Palette.h"
#include "Voxel.h"
#include "Object.h"
#include "FavWriter.h"

using namespace xercesc;

class Fav;
class FavReader;
class FavWriter;

class FavReader{
public:
    FavReader(Fav* fav_){ fav = fav_; };
    bool read(const char* file_path);
    
private:
    DOMNodeList* getElements(DOMElement* elem, const char *tagName);
    std::string getNodeValueString(DOMNode* node_);
    int getNodeValueInt(DOMNode* node_);
    double getNodeValueDouble(DOMNode* node_);

    std::string getAttribute(DOMElement* element_, const char *tagName);
    int getElementInt(DOMElement* elem, const char *tagName);
    double getElementDouble(DOMElement* elem, const char *tagName);
    std::string getElementString(DOMElement* elem, const char *tagName);
    
    void readMetaData(DOMNodeList* metadata_node_);
    void readPalette(DOMNodeList* palette_node_);
    void readVoxel(DOMNodeList* voxel_node_);
    void readObject(DOMNodeList* object_node_);
    
    void readGrid();
    void readStructure();
    
    Fav* fav;
};

class Fav{
    
public:
    Fav();
    ~Fav();
    bool read(const char* file_path);
    bool write(const char* file_path);
    
    Metadata* metadata;
    Palette palette;
    std::vector<Voxel*> voxel;
    std::vector<Object*> object;
    
private:
    FavReader* fav_reader;
    FavWriter* fav_writer;
};

