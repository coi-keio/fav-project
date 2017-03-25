//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include <iostream>
#include "Fav.h"

#include <xercesc/dom/DOMNode.hpp>
#include <xercesc/dom/DOMElement.hpp>
#include <xercesc/dom/DOMText.hpp>
#include <xercesc/parsers/AbstractDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/util/Base64.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>


#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/sax/ErrorHandler.hpp>
#include <xercesc/sax/SAXParseException.hpp>
#include <xercesc/validators/common/Grammar.hpp>


int main(int argc, const char * argv[]) {
    
    FavLibrary::Fav fav_test;
    fav_test.read("/Users/atsmsmr/Downloads/sample_validation_error.fav");
//    fav_test.read("/Users/atsmsmr/Downloads/testomato200_base64.xml");
    fav_test.write("/Users/atsmsmr/Downloads/testomato200.xml");
    
//    XMLPlatformUtils::Initialize();
//    ValidateSchema("file:///Users/atsmsmr/Documents/Developer/fav-project/xml_schema/fav.xsd", "file:///Users/atsmsmr/Downloads/sample_validation_error.fav");
//    XMLPlatformUtils::Terminate();

    return 0;
}
