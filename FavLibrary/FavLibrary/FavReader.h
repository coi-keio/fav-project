//
//  FavReader.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//
#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <iostream>

// read fav file
#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/util/Base64.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>

// for xsd validation
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>
#include <xercesc/parsers/SAXParser.hpp>
#include <xercesc/framework/MemBufInputSource.hpp>

#include "./Object/Object.h"

namespace FavLibrary
{
    class IDll Fav;

	class IDll FavReader
	{
        
	public:
		FavReader(Fav* fav_);
		bool read(const char* file_path);

	private:
        
        int          getNodeValueInt   (xercesc::DOMNode* node_);
        double       getNodeValueDouble(xercesc::DOMNode* node_);
		std::string  getNodeValueString(xercesc::DOMNode* node_);
		int          getElementInt     (xercesc::DOMElement* elem, const char *tagName);
		double       getElementDouble  (xercesc::DOMElement* elem, const char *tagName);
        std::string  getElementString  (xercesc::DOMElement* elem);
		std::string  getElementString  (xercesc::DOMElement* elem, const char *tagName);
        std::string  getAttribute      (xercesc::DOMElement* elem, const char *tagName);
        xercesc::DOMNodeList* getElements (xercesc::DOMElement* elem, const char *tagName);

        void setXsdSchemaAsString();
        bool validation(const char* file_path);
		void readMetaData(xercesc::DOMNodeList* metadata_node_);
		void readPalette (xercesc::DOMNodeList* palette_node_);
		void readVoxel   (xercesc::DOMNodeList* voxel_node_);
		void readObject  (xercesc::DOMNodeList* object_node_);
		void readGrid    (xercesc::DOMElement* parent_elem, Object* pObject);
        void readColorMap(xercesc::DOMElement* parent_elem, Object* pObject, Structure* pStructure);
        void readVoxelMap(xercesc::DOMElement* parent_elem, Object* pObject, Structure* pStructure);
        void readColorMapRGB (xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure);
        void readColorMapRGBA(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure);
        void readColorMapCMYK(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure);
        void readColorMapGrayscale  (xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure);
        void readColorMapGrayscale16(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure);

        std::string xsd_path;
        std::string xsd_string;
		Fav* fav;
	};
    
    class ValidateErrorHandler : public xercesc::ErrorHandler
    {
    public:
        void warning(const xercesc::SAXParseException& ex)
        {
            reportParseException(ex);
        }
        
        void error(const xercesc::SAXParseException& ex)
        {
            reportParseException(ex);
        }
        
        void fatalError(const xercesc::SAXParseException& ex)
        {
            reportParseException(ex);
        }
        
        void resetErrors()
        {
        }
        
    private:
        
        void reportParseException(const xercesc::SAXParseException& ex)
        {
            char* message = xercesc::XMLString::transcode(ex.getMessage());
            std::cout << message << " at line " << ex.getLineNumber() << " column " << ex.getColumnNumber() << std::endl;
            xercesc::XMLString::release(&message);
        }
    };
}
