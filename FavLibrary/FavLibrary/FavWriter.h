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

#include "Fav.h"
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

using namespace xercesc;

//class FavReader{
//public:
//    FavReader(Fav* fav_){ fav = fav_; };
//    bool read(const char* file_path);
//    
//private:
//    DOMNodeList* getElements(DOMElement* elem, const char *tagName);
//    std::string getNodeValueString(DOMNode* node_);
//    int getNodeValueInt(DOMNode* node_);
//    double getNodeValueDouble(DOMNode* node_);
//    
//    std::string getAttribute(DOMElement* element_, const char *tagName);
//    int getElementInt(DOMElement* elem, const char *tagName);
//    double getElementDouble(DOMElement* elem, const char *tagName);
//    std::string getElementString(DOMElement* elem, const char *tagName);
//    
//    void readMetaData(DOMNodeList* metadata_node_);
//    void readPalette(DOMNodeList* palette_node_);
//    void readVoxel(DOMNodeList* voxel_node_);
//    void readObject(DOMNodeList* object_node_);
//    
//    void readGrid();
//    void readStructure();
//    
//    Fav* fav;
//};

class FavWriter{
public:
//    FavWriter(Fav* fav_){ fav = fav_; };
//    
//    bool write(const char* file_path){
//        XMLPlatformUtils::Initialize();
//        
//        //インスタンス作成.
//        DOMImplementation *tpImpl =  DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
//        
//        //ドキュメント生成( エレメントをModelに設定 ).
//        DOMDocument *doc 		= tpImpl->createDocument(0,XMLString::transcode("fav"),0);
//        DOMElement	*fav_elem = doc->getDocumentElement();
//        fav_elem->setAttribute(XMLString::transcode("version"), XMLString::transcode("1.0"));
//        
//        // Create elements
//        DOMElement *metadata_elem = doc->createElement(XMLString::transcode("metadata"));
//        DOMElement *palette_elem = doc->createElement(XMLString::transcode("palette"));
//        DOMElement *voxel_elem = doc->createElement(XMLString::transcode("voxel"));
//        DOMElement *object_elem = doc->createElement(XMLString::transcode("object"));
//
//        // Add Elements to <Fav>
//        writeMetadata(doc, fav_elem, metadata_elem);
//        fav_elem->appendChild( palette_elem );
//        fav_elem->appendChild( voxel_elem );
//        fav_elem->appendChild( object_elem );
//
//        //書き出し(次へ).
//        writeXML( doc, file_path);
//        
//        //終了処理.
//        doc->release();
//        
//        XMLPlatformUtils::Terminate();
//        return 0;
//    };
//    
//    void writeMetadata(DOMDocument *doc, DOMElement	*fav_elem, DOMElement *metadata_elem){
//        
//        
//        for( int ii = 0 ; ii < 10 ; ii++ )
//        {
//            std::cout << fav->metadata->getTitle() << std::endl;
//            
//            //頂点という名前のエレメントを作成する( SVertex ).
//            DOMElement *tpElem = doc->createElement(XMLString::transcode("SVertex"));
//            
//            //Vertexを文字列として書いてみる(テストなので適当に).
//            XMLCh tVertexs[ 128 ];
//            //            sprintf( tVertexs, 128, L"%f,%f,%f", 0, 1, 2 );
//            
//            //作成したエレメントのパラメーターとしてVertexを追加、名称は[ tVertexs ]である.
//            //< SVertex Vertex="0,1,2"/>で入るはず.
//            tpElem-> setAttribute(XMLString::transcode("Vertex"), tVertexs );
//            
//            //作成したエレメントを子としてつなぐ.
//            //Infoエレメント以下の子とする.
//            metadata_elem-> appendChild( tpElem );
//        }
//
//        fav_elem->appendChild( metadata_elem );
//    }
//    
//    void writeXML(xercesc::DOMDocument* pmyDOMDocument, const char *filePath){
//        // set LS (Load/Save)
////        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(L"LS");
//        DOMImplementation *implementation = DOMImplementation::getImplementation();
//        
//        DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();
//        if (serializer-> getDomConfig()-> canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true)){
//            serializer-> getDomConfig()-> setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
//        }
//        
//        serializer-> setNewLine(XMLString::transcode("\r\n"));
//        
//        // Change filepath to XMLCh type.
//        XMLCh *tempFilePath = XMLString::transcode( filePath );
//        
//        // Create target file.
//        XMLFormatTarget *formatTarget = new LocalFileFormatTarget( tempFilePath );
//        
//        DOMLSOutput *output = ((DOMImplementationLS*)implementation)-> createLSOutput();
//        output->setByteStream(formatTarget);
//        
//        // Write
//        serializer-> write(pmyDOMDocument, output);
//        
//        // Release
//        serializer-> release();
//        XMLString::release( &tempFilePath );
//        delete formatTarget;
//        output-> release();
//    };
    
//    Fav* fav;

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
