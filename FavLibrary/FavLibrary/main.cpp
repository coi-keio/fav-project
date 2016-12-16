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


int main(int argc, const char * argv[]) {
    
    Fav fav_test;
    fav_test.read("/Users/atsmsmr/Downloads/FAVSample_v1_(1).fav");
//    fav_test.read("/Users/atsmsmr/Downloads/testomato200_base64.xml");
    fav_test.write("/Users/atsmsmr/Downloads/testomato200.xml", "1.0");

    return 0;
}
