//
//  FavWriter.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "FavWriter.h"
#include "Fav.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

using namespace xercesc;

bool FavWriter::write(const char* file_path){
    XMLPlatformUtils::Initialize();
    
    //インスタンス作成.
    DOMImplementation *tpImpl =  DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
    
    //ドキュメント生成( エレメントをModelに設定 ).
    DOMDocument *doc 		= tpImpl->createDocument(0,XMLString::transcode("fav"),0);
    DOMElement	*fav_elem = doc->getDocumentElement();
    fav_elem->setAttribute(XMLString::transcode("version"), XMLString::transcode("1.0"));
    
    // Create elements
    DOMElement *metadata_elem = doc->createElement(XMLString::transcode("metadata"));
    DOMElement *palette_elem = doc->createElement(XMLString::transcode("palette"));
    DOMElement *voxel_elem = doc->createElement(XMLString::transcode("voxel"));
    DOMElement *object_elem = doc->createElement(XMLString::transcode("object"));
    
    // Add Elements to <Fav>
    writeMetadata(doc, fav_elem, metadata_elem);
    fav_elem->appendChild( palette_elem );
    fav_elem->appendChild( voxel_elem );
    fav_elem->appendChild( object_elem );
    
    //書き出し(次へ).
    writeXML( doc, file_path);
    
    //終了処理.
    doc->release();
    
    XMLPlatformUtils::Terminate();
    return 0;
};

void FavWriter::writeMetadata(DOMDocument *doc, DOMElement	*fav_elem, DOMElement *metadata_elem){
    
    
    for( int ii = 0 ; ii < 10 ; ii++ )
    {
        std::cout << fav->metadata->getTitle() << std::endl;
        
        //頂点という名前のエレメントを作成する( SVertex ).
        DOMElement *tpElem = doc->createElement(XMLString::transcode("SVertex"));
        
        //Vertexを文字列として書いてみる(テストなので適当に).
        XMLCh tVertexs[ 128 ];
        //            sprintf( tVertexs, 128, L"%f,%f,%f", 0, 1, 2 );
        
        //作成したエレメントのパラメーターとしてVertexを追加、名称は[ tVertexs ]である.
        //< SVertex Vertex="0,1,2"/>で入るはず.
        tpElem-> setAttribute(XMLString::transcode("Vertex"), tVertexs );
        
        //作成したエレメントを子としてつなぐ.
        //Infoエレメント以下の子とする.
        metadata_elem-> appendChild( tpElem );
    }
    
    fav_elem->appendChild( metadata_elem );
}

void FavWriter::writeXML(xercesc::DOMDocument* pmyDOMDocument, const char *filePath){
    // set LS (Load/Save)
    //        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(L"LS");
    DOMImplementation *implementation = DOMImplementation::getImplementation();
    
    DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();
    if (serializer-> getDomConfig()-> canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true)){
        serializer-> getDomConfig()-> setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
    }
    
    serializer-> setNewLine(XMLString::transcode("\r\n"));
    
    // Change filepath to XMLCh type.
    XMLCh *tempFilePath = XMLString::transcode( filePath );
    
    // Create target file.
    XMLFormatTarget *formatTarget = new LocalFileFormatTarget( tempFilePath );
    
    DOMLSOutput *output = ((DOMImplementationLS*)implementation)-> createLSOutput();
    output->setByteStream(formatTarget);
    
    // Write
    serializer-> write(pmyDOMDocument, output);
    
    // Release
    serializer-> release();
    XMLString::release( &tempFilePath );
    delete formatTarget;
    output-> release();
};
