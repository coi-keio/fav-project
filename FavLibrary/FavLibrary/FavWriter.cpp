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

void FavWriter::appendCDATA(DOMElement* parent_elem, const char* child_elem_name, const char* text){
    DOMElement *child_elem = doc->createElement(XMLString::transcode(child_elem_name));
    DOMCDATASection *text_elem = doc->createCDATASection(XMLString::transcode(text));
    child_elem->appendChild(text_elem);
    parent_elem->appendChild(child_elem);
};

void FavWriter::appendCDATA(DOMElement* parent_elem, const char* child_elem_name, std::string text){
    appendCDATA(parent_elem, child_elem_name, text.c_str());
};


void FavWriter::appendText(DOMElement* parent_elem, const char* child_elem_name, const char* text){
    DOMElement *child_elem = doc->createElement(XMLString::transcode(child_elem_name));
    DOMText *text_elem = doc->createTextNode(XMLString::transcode(text));
    child_elem->appendChild(text_elem);
    parent_elem->appendChild(child_elem);
};

void FavWriter::appendText(DOMElement* parent_elem, const char* child_elem_name, std::string text){
    appendText(parent_elem, child_elem_name, text.c_str());
};

void FavWriter::setAttribute(DOMElement *elem, const char* attr_name, const char* attr_value){
    elem->setAttribute(XMLString::transcode(attr_name), XMLString::transcode(attr_value) );
    
};

void FavWriter::setAttribute(DOMElement *elem, const char* attr_name, std::string attr_value){
    setAttribute(elem, attr_name, attr_value.c_str());
};

bool FavWriter::write(const char* file_path){
    XMLPlatformUtils::Initialize();
    
    //インスタンス作成.
    DOMImplementation *tpImpl =  DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
    
    //ドキュメント生成( エレメントをModelに設定 ).
    doc 		= tpImpl->createDocument(0,XMLString::transcode("fav"),0);
    DOMElement	*fav_elem = doc->getDocumentElement();
    setAttribute(fav_elem, "version", "1.0");
    
    // Create elements
    
    // Add Elements to <Fav>
    writeMetadata(fav_elem);
    writePalette(fav_elem);
    writeVoxel(fav_elem);
    writeObject(fav_elem);

//    fav_elem->appendChild( voxel_elem );
//    fav_elem->appendChild( object_elem );
    
    //書き出し(次へ).
    writeXML(file_path);
    
    //終了処理.
    doc->release();
    
    XMLPlatformUtils::Terminate();
    return 0;
};

void FavWriter::writeMetadata(DOMElement *parent_elem){
    
    DOMElement *metadata_elem = doc->createElement(XMLString::transcode("metadata"));

    appendCDATA(metadata_elem, "title", fav->metadata->getTitle());
    appendCDATA(metadata_elem, "author", fav->metadata->getAuthor());
    appendCDATA(metadata_elem, "license", fav->metadata->getLicense());
    
    // noteに関して追記
    parent_elem->appendChild( metadata_elem );
}


void FavWriter::writePalette(DOMElement *parent_elem){
    
    DOMElement *palette_elem = doc->createElement(XMLString::transcode("palette"));

    
    // write geometry
    int number_of_geometries = fav->palette.getNumberOfGeometries();

    for(int i=0; i<number_of_geometries; ++i){
        Geometry* tmp = fav->palette.getGeometry(i);
        DOMElement *geo_elem = doc->createElement(XMLString::transcode("geometry"));

        setAttribute(geo_elem, "id", std::to_string(tmp->getId()));
        
        // if(tmp->has_name){
        setAttribute(geo_elem, "name", tmp->getName());

        if(tmp->getShape() == "user_defined"){
            // under development : add reference path
            appendText(geo_elem, "shape", tmp->getShape());
        }else{
            appendText(geo_elem, "shape", tmp->getShape());
        }
        
        DOMElement *scale_elem = doc->createElement(XMLString::transcode("scale"));
        appendText(scale_elem, "x", std::to_string(tmp->getScaleX()));
        appendText(scale_elem, "y", std::to_string(tmp->getScaleY()));
        appendText(scale_elem, "z", std::to_string(tmp->getScaleZ()));
        geo_elem->appendChild(scale_elem);
        
        palette_elem->appendChild(geo_elem);
    }
    
    
    // write material
    int number_of_materials = fav->palette.getNumberOfMaterials();
    std::cout << number_of_materials << std::endl;
    
    for(int i=0; i<number_of_materials; ++i){
        
        Material* tmp = fav->palette.getMaterial(i);
        DOMElement *mat_elem = doc->createElement(XMLString::transcode("material"));
        
        setAttribute(mat_elem, "id", std::to_string(tmp->getId()));
        // if(tmp->has_name){
        setAttribute(mat_elem, "name", tmp->getName());
        
        // 優先順位問題をmaterialクラスの構造で解決する必要がある
        for(int i=0, size=tmp->getNumProductInfo(); i<size; ++i){
            DOMElement *pinfo_elem = doc->createElement(XMLString::transcode("product_info"));
            Material::ProductInfo* p_info = tmp->getProductInfo(i);
            appendCDATA(pinfo_elem, "manufacturer", p_info->getManufacturer());
            appendCDATA(pinfo_elem, "product_name", p_info->getProductName());
            appendCDATA(pinfo_elem, "url", p_info->getUrl() );
            mat_elem->appendChild(pinfo_elem);
        }
        
        for(int i=0, size=tmp->getNumIsoStandard(); i<size; ++i){
            DOMElement *iso_elem = doc->createElement(XMLString::transcode("iso_standard"));
            Material::IsoStandard* iso = tmp->getIsoStandard(i);
            appendCDATA(iso_elem, "iso_id", iso->getIsoId());
            appendCDATA(iso_elem, "iso_name", iso->getIsoName());
            mat_elem->appendChild(iso_elem);
        }
        
//        for(int i=0, size=tmp->getNumMaterialName(); i<size; ++i){
//            DOMElement *name_elem = doc->createElement(XMLString::transcode("material_name"));
//            std::string material_name = tmp->getMaterialName(i);
//            appendCDATA(name_elem, "material_name", material_name);
//            mat_elem->appendChild(name_elem);
//        }
        
        palette_elem->appendChild(mat_elem);
    }
    
    parent_elem->appendChild( palette_elem );
}

void FavWriter::writeVoxel(DOMElement *parent_elem){
    
//    under development Voxelクラスが出来てから
//    DOMElement *voxel_elem = doc->createElement(XMLString::transcode("voxel"));
//
//    for(int i=0, size = (int)fav->voxel.size(); i<size; ++i){
//        DOMElement *vox_elem = doc->createElement(XMLString::transcode("voxel"));
//        Voxel* tmp = fav->voxel[i];
//        setAttribute(vox_elem, "id", std::to_string(tmp->getId()));
//        setAttribute(vox_elem, "name", tmp->getName());
//        DOMElement *geo_elem = doc->createElement(XMLString::transcode("geometry_info"));
//        appendText(geo_elem, "id", tmp->getGeometryInfo()->getId());
//        vox_elem->appendChild(geo_elem);
//        
//        for(int j=0, size = tmp->getNumMaterialInfo(); j<size; ++j){
//            
//        }
//        voxel_elem->appendChild(vox_elem);
//    }
//    
//    parent_elem->appendChild( voxel_elem );

};

void FavWriter::writeGrid(DOMElement* parent_elem, Grid* grid){

//    // waiting for grid class
//    DOMElement *grid_elem = doc->createElement(XMLString::transcode("grid"));
//    
//    DOMElement *origin_elem = doc->createElement(XMLString::transcode("origin"));
//    appendText(origin_elem, "x", std::to_string(grid->getOriginX()));
//    appendText(origin_elem, "y", std::to_string(grid->getOriginY()));
//    appendText(origin_elem, "z", std::to_string(grid->getOriginZ()));
//    grid_elem->appendChild(origin_elem);
//    
//    DOMElement *unit_elem = doc->createElement(XMLString::transcode("unit"));
//    appendText(unit_elem, "x", std::to_string(grid->getUnitX()));
//    appendText(unit_elem, "y", std::to_string(grid->getUnitX()));
//    appendText(unit_elem, "z", std::to_string(grid->getUnitX()));
//    grid_elem->appendChild(unit_elem);
//    
//    DOMElement *dim_elem = doc->createElement(XMLString::transcode("dimension"));
//    appendText(dim_elem, "x", std::to_string(grid->getDimensionX()));
//    appendText(dim_elem, "y", std::to_string(grid->getDimensionY()));
//    appendText(dim_elem, "z", std::to_string(grid->getDimensionZ()));
//    grid_elem->appendChild(dim_elem);
//    
//    parent_elem->appendChild(grid_elem);
    
}

void FavWriter::writeStructure(DOMElement* parent_elem, Structure* p_str){
 

}


void FavWriter::writeObject(DOMElement* parent_elem){
    
    for(int i=0, size=(int)fav->object.size(); i<size; ++i){
        Object* tmp = fav->object[i];
        DOMElement *obj_elem = doc->createElement(XMLString::transcode("object"));
//        setAttribute(obj_elem, "id", std::to_string(tmp->getId()));
//        setAttribute(obj_elem, "name", tmp->getName());
        writeGrid(obj_elem, tmp->grid);
//        writeStructure(obj_elem, tmp->getStructure());
        parent_elem->appendChild(obj_elem);
    }

}

void FavWriter::writeXML(const char *filePath){
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
    serializer-> write(doc, output);
    
    // Release
    serializer-> release();
    XMLString::release( &tempFilePath );
    delete formatTarget;
    output-> release();
};
