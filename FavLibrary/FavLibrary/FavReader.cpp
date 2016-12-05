//
//  FavReader.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "FavReader.h"
#include "Fav.h"

#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/PlatformUtils.hpp>

using namespace xercesc;


bool FavReader::read(const char* file_path){
    
    // Xerces-C++を初期化する
    try {
        XMLPlatformUtils::Initialize();
    } catch(...) {
        //        std::cout << "Xerces-C++の初期化に失敗しました。" << std::endl;
        return 1;
    }
    
    XercesDOMParser *parser = new XercesDOMParser;
    parser->parse(file_path);
    
    DOMDocument *doc = parser->getDocument();
    DOMElement *root = doc->getDocumentElement();
    
    DOMNodeList* metadata_list = getElements(root, "metadata");
    readMetaData(metadata_list);
    
    DOMNodeList* palette_list = getElements(root, "palette");
    readPalette(palette_list);
    
    DOMNodeList* voxel_list = getElements(root, "voxel");
    readVoxel(voxel_list);
    
    DOMNodeList* object_list = getElements(root, "object");
    readObject(object_list);
    
    XMLPlatformUtils::Terminate();
    
    return 1;
}

DOMNodeList* FavReader::getElements(DOMElement* element_, const char *tag_name_)
{
    char* tag_name = (char *)tag_name_;
    XMLCh* attributeName = XMLString::transcode(tag_name);
    DOMNodeList* node_list = element_->getElementsByTagName(attributeName);
    XMLString::release(&attributeName);
    
    return node_list;
}

std::string FavReader::getAttribute(DOMElement* element_, const char *tag_name_)
{
    char* tag_name = (char *)tag_name_;
    XMLCh* attributeName = XMLString::transcode(tag_name);
    const XMLCh* attribute_value = element_->getAttribute(attributeName);
    char* attribute_value_str = XMLString::transcode(attribute_value);
    std::string ret = std::string(attribute_value_str);
    XMLString::release(&attribute_value_str);
    
    return ret;
}

int FavReader::getNodeValueInt(DOMNode* node_)
{
    const XMLCh* node_value = node_->getNodeValue();
    char* node_value_str = XMLString::transcode(node_value);
    int ret = atoi(node_value_str);
    XMLString::release(&node_value_str);
    return ret;
}

double FavReader::getNodeValueDouble(DOMNode* node_)
{
    const XMLCh* node_value = node_->getNodeValue();
    char* node_value_str = XMLString::transcode(node_value);
    double ret = atof(node_value_str);
    XMLString::release(&node_value_str);
    return ret;
}

std::string FavReader::getNodeValueString(DOMNode* node_)
{
    const XMLCh* node_value = node_->getNodeValue();
    char* node_value_str = XMLString::transcode(node_value);
    std::string ret = std::string(node_value_str);
    XMLString::release(&node_value_str);
    return ret;
}

int FavReader::getElementInt(DOMElement* elem, const char *tag_name_)
{
    char* tag_name = (char *)tag_name_;
    DOMNodeList* node_list = getElements(elem,tag_name);
    const XMLCh* node_value = ( (node_list->item(0))->getFirstChild() )->getNodeValue();
    char* node_value_str = XMLString::transcode(node_value);
    int ret = atoi(node_value_str);
    XMLString::release(&node_value_str);
    return ret;
}

double FavReader::getElementDouble(DOMElement* elem, const char *tag_name_)
{
    char* tag_name = (char *)tag_name_;
    DOMNodeList* node_list = getElements(elem,tag_name);
    const XMLCh* node_value = ( (node_list->item(0))->getFirstChild() )->getNodeValue();
    char* node_value_str = XMLString::transcode(node_value);
    double ret = atof(node_value_str);
    XMLString::release(&node_value_str);
    return ret;
}

std::string FavReader::getElementString(DOMElement* elem, const char *tag_name_)
{
    char* tag_name = (char *)tag_name_;
    DOMNodeList* node_list = getElements(elem,tag_name);
    const XMLCh* node_value = ( (node_list->item(0))->getFirstChild() )->getNodeValue();
    char* node_value_str = XMLString::transcode(node_value);
    std::string ret = std::string(node_value_str);
    XMLString::release(&node_value_str);
    return ret;
}


void FavReader::readMetaData(xercesc_3_1::DOMNodeList *metadata_node_){
    
    int number_of_metadata = int(metadata_node_->getLength());
    
    for(int i=0; i<number_of_metadata; ++i){
        
        DOMNode *current_metadata = metadata_node_->item(i);
        DOMNode *parent_node = dynamic_cast<DOMElement*>(current_metadata)->getParentNode();
        
        if(XMLString::transcode(parent_node->getNodeName()) == std::string("fav")){
            fav->metadata = new Metadata();
            fav->metadata->setTitle  ( getElementString(dynamic_cast<DOMElement*>(current_metadata), "title") );
            fav->metadata->setAuthor ( getElementString(dynamic_cast<DOMElement*>(current_metadata), "author") );
            fav->metadata->setLicense( getElementString(dynamic_cast<DOMElement*>(current_metadata), "license") );
        }
        
    }
    
}

void FavReader::readPalette(xercesc_3_1::DOMNodeList *palette_list_){
    
    // Load geometries
    DOMNodeList* geometry_list = getElements(dynamic_cast<DOMElement*>(palette_list_->item(0)), "geometry");
    int number_of_geometry = int(geometry_list->getLength());
    
    for(int i=0; i<number_of_geometry; ++i){
        
        //load attributes
        int index = std::stoi(getAttribute(dynamic_cast<DOMElement*>(geometry_list->item(i)), "id"));
        std::string name = getAttribute(dynamic_cast<DOMElement*>(geometry_list->item(i)), "name");
        Geometry* current_geometry = new Geometry(index, name);
        
        std::string shape = getElementString(dynamic_cast<DOMElement*>(geometry_list->item(i)), "shape");
        current_geometry->setShape(shape);
        
        DOMNodeList* scale_node = getElements(dynamic_cast<DOMElement*>(geometry_list->item(i)), "scale");
        if(scale_node->getLength() > 0){
            double x = getElementDouble(dynamic_cast<DOMElement*>(scale_node->item(0)), "x");
            double y = getElementDouble(dynamic_cast<DOMElement*>(scale_node->item(0)), "y");
            double z = getElementDouble(dynamic_cast<DOMElement*>(scale_node->item(0)), "z");
            current_geometry->setScale(x,y,z);
        }
        
        fav->palette.addGeometry(current_geometry);
    }
    
    
    // load materials
    DOMNodeList* material_list = getElements(dynamic_cast<DOMElement*>(palette_list_->item(0)), "material");
    int number_of_material = int(material_list->getLength());
    
    for(int i=0; i<number_of_material; ++i){
        Material* current_material = new Material();
        
        // debug required for multiple material_name case
        DOMNodeList* material_name_list = getElements(dynamic_cast<DOMElement*>(material_list->item(i)), "material_name");
        int number_of_material_name = int(material_name_list->getLength());
        if(number_of_material_name > 0){
            std::string name = getElementString(dynamic_cast<DOMElement*>(material_list->item(i)), "material_name");
            current_material->addMaterialName(name);
        }
        
        // load product_info
        DOMNodeList* product_info_list = getElements(dynamic_cast<DOMElement*>(material_list->item(i)), "product_info");
        int number_of_product_info = int(product_info_list->getLength());
        
        for(int j=0; j<number_of_product_info; ++j){
            std::string manufacturer = getElementString(dynamic_cast<DOMElement*>(product_info_list->item(j)), "manufacturer");
            std::string product_name = getElementString(dynamic_cast<DOMElement*>(product_info_list->item(j)), "product_name");
            std::string url          = getElementString(dynamic_cast<DOMElement*>(product_info_list->item(j)), "url");
            
            current_material->addProductInfo(manufacturer, product_name, url);
        }
        
        // load iso_standard
        DOMNodeList* iso_standard_list = getElements(dynamic_cast<DOMElement*>(material_list->item(i)), "iso_standard");
        int number_of_iso_standard = int(iso_standard_list->getLength());
        
        for(int j=0; j<number_of_iso_standard; ++j){
            std::string iso_id = getElementString(dynamic_cast<DOMElement*>(iso_standard_list->item(j)), "iso_id");
            std::string iso_name = getElementString(dynamic_cast<DOMElement*>(iso_standard_list->item(j)), "iso_name");
            
            current_material->addIsoStandard(iso_id, iso_name);
        }
        
        fav->palette.addMaterial(current_material);
    }
}

void FavReader::readVoxel(xercesc_3_1::DOMNodeList *voxel_list_){
    
    int number_of_voxels = int(voxel_list_->getLength());
    for(int i=0; i<number_of_voxels; ++i){
        
        DOMElement* voxel_elem = dynamic_cast<DOMElement*>(voxel_list_->item(i));
        //load attributes
        int index = std::stoi(getAttribute(voxel_elem, "id"));
        std::string name = getAttribute(voxel_elem, "name");
        Voxel* current_voxel = new Voxel(index, name);
        
        //load geometry_info
        DOMNodeList* geoinfo_node = getElements(voxel_elem, "geometry_info");
        DOMElement*  geoinfo_elem = dynamic_cast<DOMElement*>(geoinfo_node->item(0));
        int geometry_id = getElementInt(geoinfo_elem, "id");
        current_voxel->setGeometryInfo(geometry_id);
        
        //load material_info
        DOMNodeList* matinfo_node = getElements(voxel_elem, "material_info");
        int number_of_matinfo = int(matinfo_node->getLength());
        for(int j=0; j<number_of_matinfo; ++j){
            DOMElement* matinfo_elem = dynamic_cast<DOMElement*>(matinfo_node->item(j));
            int material_id       = getElementInt(matinfo_elem, "id");
            double material_ratio = getElementDouble(matinfo_elem, "ratio");
            current_voxel->addMaterialInfo(material_id, material_ratio);
        }
        
        fav->voxel.push_back(current_voxel);
    }
    
    
}

void FavReader::readObject(xercesc_3_1::DOMNodeList *object_node_){
    
    int number_of_object = int(object_node_->getLength());
    for(int i=0; i<number_of_object; ++i){
        
        DOMElement* object_elem = dynamic_cast<DOMElement*>(object_node_->item(i));
        
        //load attributes
        int index = std::stoi(getAttribute(object_elem, "id"));
        std::string name = getAttribute(object_elem, "name");
        Object* current_object = new Object(index, name);
        
        // load grid
        current_object->grid = new Grid();
        
        // load origin
        DOMNodeList* origin_node = getElements(object_elem, "origin");
        if(origin_node->getLength() > 0){
            int x = getElementInt(dynamic_cast<DOMElement*>(origin_node->item(0)), "x");
            int y = getElementInt(dynamic_cast<DOMElement*>(origin_node->item(0)), "y");
            int z = getElementInt(dynamic_cast<DOMElement*>(origin_node->item(0)), "z");
            current_object->grid->origin.set(x, y, z);
        }
        
        // load unit
        DOMNodeList* unit_node = getElements(object_elem, "unit");
        if(unit_node->getLength() > 0){
            int x = getElementInt(dynamic_cast<DOMElement*>(unit_node->item(0)), "x");
            int y = getElementInt(dynamic_cast<DOMElement*>(unit_node->item(0)), "y");
            int z = getElementInt(dynamic_cast<DOMElement*>(unit_node->item(0)), "z");
            current_object->grid->unit.set(x, y, z);
        }
        
        // load dimension
        DOMNodeList* dimension_node = getElements(object_elem, "dimension");
        if(origin_node->getLength() > 0){
            int x = getElementInt(dynamic_cast<DOMElement*>(dimension_node->item(0)), "x");
            int y = getElementInt(dynamic_cast<DOMElement*>(dimension_node->item(0)), "y");
            int z = getElementInt(dynamic_cast<DOMElement*>(dimension_node->item(0)), "z");
            current_object->grid->dimension.set(x, y, z);
        }else{
            // error message is here. dimension is required.
        }
        
        
        // load Structure
        Structure* structure = new Structure(current_object->grid->dimension.getX(),current_object->grid->dimension.getY(),current_object->grid->dimension.getZ());
        
        // load voxel_map
        DOMElement* vmap_elem = dynamic_cast<DOMElement*>( getElements(object_elem, "voxel_map")->item(0) );
        std::string compression   = getAttribute(vmap_elem, "compression");
        std::string bit_per_voxel = getAttribute(vmap_elem, "bit_per_voxel");
        
        if(compression == "none"){
            
            DOMNodeList* vmap_layers = getElements(vmap_elem, "layer");
            int number_of_layers = int(vmap_layers->getLength());
            structure->initVoxelMap();
            
            for(int j=0; j<number_of_layers; ++j){
                
                if(bit_per_voxel == "8"){
                    std::string layer_data = getNodeValueString( vmap_layers->item(j)->getFirstChild() );
                    std::string data_in;
                    data_in.resize(layer_data.size()/2);
                    int cur = 0;
                    for(int k=0; k<(int)layer_data.size(); k=k+2){
                        int dec;
                        char hex[2] = {layer_data[k], layer_data[k+1]};
                        sscanf(hex, "%02x", &dec);
                        data_in[cur] = dec; //if compressed using this scheme
                        cur++;
                        std::cout << dec << std::endl;
                    }
                    
                    int dim_x = current_object->grid->dimension.getX();
                    int dim_y = current_object->grid->dimension.getY();
                    int layer_size = dim_x * dim_y;
                    
                    if (data_in.size() != layer_size){
                        // error here
                    }
                    
                    for(int k=0; k<layer_size; k++){
                        
                        int index = layer_size*j + k;
                        structure->setVoxel(index, (int)data_in[k]);
                        
                    }
                }
            }
        }
        
        // load color_map
        DOMElement* cmap_elem = dynamic_cast<DOMElement*>( getElements(object_elem, "color_map")->item(0) );
        compression = getAttribute(cmap_elem, "compression");
        std::string color_mode = getAttribute(cmap_elem, "color_mode");
        
        if(compression == "none"){
            
            DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
            int number_of_layers = int(cmap_layers->getLength());
            
            if(number_of_layers > 0){
                structure->initColorMap(color_mode);
            }
            
            if(color_mode == "RGB"){
                
                int* layer_r;
                int* layer_g;
                int* layer_b;
                
                for(int j=0; j<number_of_layers; ++j){
                    
                    std::string layer_data = getNodeValueString( cmap_layers->item(j)->getFirstChild() );
                    std::string data_in;
                    std::cout << layer_data << std::endl;
                    
                    layer_r = new int[layer_data.size()/(2*3)]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
                    layer_g = new int[layer_data.size()/(2*3)];
                    layer_b = new int[layer_data.size()/(2*3)];
                    
                    for (int i=0; i<(int)layer_data.size(); i=i+6){
                        int r_value, g_value, b_value;
                        char r[2] = {layer_data[i],  layer_data[i+1]};
                        char g[2] = {layer_data[i+2],layer_data[i+3]};
                        char b[2] = {layer_data[i+4],layer_data[i+5]};
                        sscanf(r, "%02x", &r_value);
                        sscanf(g, "%02x", &g_value);
                        sscanf(b, "%02x", &b_value);
                        layer_r[i/6] = r_value; //if compressed using this scheme
                        layer_g[i/6] = g_value; //if compressed using this scheme
                        layer_b[i/6] = b_value; //if compressed using this scheme
                    }
                    
                    
                    int dim_x = current_object->grid->dimension.getX();
                    int dim_y = current_object->grid->dimension.getY();
                    int current_color = 0;
                    
                    for(int y=0; y<dim_y; y++){
                        for(int x=0; x<dim_x; x++){
                            
                            int index = structure->getIndex(x,y,j);
                            if(structure->getVoxel(index) != 0){
                                structure->setColor(index, layer_r[current_color], layer_g[current_color], layer_b[current_color]);
                                std::cout << layer_r[current_color] << " -- " << structure->getColorR(index) << std::endl;
                                current_color++;
                            }else{
                                structure->setColor(index, 0, 0, 0);
                            }
                            
                        }
                    }
                }
                
            }
        }
        
        current_object->structure = structure;
        
        // other compression mode is under development
        
        fav->object.push_back(current_object);
    }
}