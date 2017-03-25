//
//  FavReader.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__FavReader__
#define __FavLibrary__FavReader__

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



#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>


#include "FavSettings.h"
#include "Metadata.h"
#include "Voxel.h"
#include "./Palette/Palette.h"
#include "./Object/Object.h"
#include "./Object/Structure.h"

using namespace xercesc;

namespace FavLibrary
{
    RefClass Fav;

	RefClass FavReader
	{
        class ParserErrorHandler : public ErrorHandler
        {
        private:
            void reportParseException(const SAXParseException& ex)
            {
                char* msg = XMLString::transcode(ex.getMessage());
                fprintf(stderr, "at line %llu column %llu, %s\n", ex.getLineNumber(), ex.getColumnNumber(), msg);
                XMLString::release(&msg);
            }
            
        public:
            void warning(const SAXParseException& ex)
            {
                reportParseException(ex);
            }
            
            void error(const SAXParseException& ex)
            {
                reportParseException(ex);
            }
            
            void fatalError(const SAXParseException& ex)
            {
                reportParseException(ex);
            }
            
            void resetErrors()
            {
            }
        };
        
	public:
		FavReader(Fav* fav_);
		bool read(const char* file_path);

	private:
        
        bool validation(const char* file_path);
        
        int          getNodeValueInt   (DOMNode* node_);
        double       getNodeValueDouble(DOMNode* node_);
		std::string  getNodeValueString(DOMNode* node_);
		int          getElementInt     (DOMElement* elem, const char *tagName);
		double       getElementDouble  (DOMElement* elem, const char *tagName);
		std::string  getElementString  (DOMElement* elem, const char *tagName);
        DOMNodeList* getElements       (DOMElement* elem, const char *tagName);
        std::string  getAttribute      (DOMElement* elem, const char *tagName);

		void readMetaData(DOMNodeList* metadata_node_);
		void readPalette (DOMNodeList* palette_node_);
		void readVoxel   (DOMNodeList* voxel_node_);
		void readObject  (DOMNodeList* object_node_);
		void readGrid();
		void readStructure();
        
        std::string xsd_path;

		Fav* fav;
	};
}
#endif /* defined(__FavLibrary__FavReader__) */
