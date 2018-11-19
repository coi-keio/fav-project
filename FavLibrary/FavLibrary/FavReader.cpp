//
//  FavReader.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//
#define _CRT_SECURE_NO_WARNINGS

#include "Fav.h"
#include "FavReader.h"


namespace FavLibrary
{
    
    FavReader::FavReader(Fav* fav_) {
        fav = fav_;
	};
    

    bool FavReader::validation(const char* file_path)
    {
        
        setXsdSchemaAsString();
        
        xercesc::SAX2XMLReader *parser  = xercesc::XMLReaderFactory::createXMLReader();
        xercesc::ErrorHandler  *handler = new ValidateErrorHandler();
        xercesc::MemBufInputSource inMemorySchemaSource(reinterpret_cast<const XMLByte*>(xsd_string.c_str()), xsd_string.size (), "/schema.xsd");
        
        parser->loadGrammar(inMemorySchemaSource, xercesc::Grammar::SchemaGrammarType, true);
        parser->setFeature(xercesc::XMLUni::fgXercesUseCachedGrammarInParse, true);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreValidation, true);
        parser->setFeature(xercesc::XMLUni::fgSAX2CoreNameSpaces, true);
        parser->setProperty(xercesc::XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation, const_cast<void*>(static_cast<const void*>("")));
        parser->setErrorHandler(handler);
        parser->parse(file_path);
        
        if (parser->getErrorCount() == 0)
        {
            delete parser;
            delete handler;
            printf("This file confirm to Fav ver.1.0\n");
            return 1;
        }
        else
        {
            delete parser;
            delete handler;
            printf("This file does not conform to Fav ver.1.0\n");
            return 0;
        }
    }
    
    bool FavReader::read(const char* file_path) {
        
        try {
            xercesc::XMLPlatformUtils::Initialize();
        }
        catch(const xercesc::XMLException& exp) {
            char* message = xercesc::XMLString::transcode(exp.getMessage());
            std::cerr << "Error: Xerces-C++ could not be initialized." << std::endl;
            std::cerr << message << std::endl;
            xercesc::XMLString::release(&message);
            return 0;
        }
        
        if(validation(file_path) == false){
            return 0;
        };
        
        xercesc::XercesDOMParser *parser = new xercesc::XercesDOMParser;
        
        try{
            parser->parse(file_path);
        }
        catch ( const xercesc::XMLException& exp ) {
            char* message = xercesc::XMLString::transcode(exp.getMessage());
            std::cerr<< "Error: " << message << std::endl;
            xercesc::XMLString::release(&message);
            return 0;
        }
        
        xercesc::DOMDocument *doc  = parser->getDocument();
        xercesc::DOMElement  *root = doc->getDocumentElement();
        xercesc::DOMNodeList* metadata_list = getElements(root, "metadata");
        xercesc::DOMNodeList* palette_list  = getElements(root, "palette" );
        xercesc::DOMNodeList* voxel_list    = getElements(root, "voxel"   );
        xercesc::DOMNodeList* object_list   = getElements(root, "object"  );
        
        readMetaData(metadata_list);
        readPalette (palette_list);
        readVoxel   (voxel_list);
        readObject  (object_list);
        
        delete parser;
        xercesc::XMLPlatformUtils::Terminate();
        
        return 1;
    }

	void FavReader::readMetaData(xercesc::DOMNodeList *metadata_node_) {

		int number_of_metadata = int(metadata_node_->getLength());

		for (int i=0; i<number_of_metadata; ++i) {

			xercesc::DOMNode *current_metadata = metadata_node_->item(i);
			xercesc::DOMNode *parent_node = dynamic_cast<xercesc::DOMElement*>(current_metadata)->getParentNode();

            char* node_name = xercesc::XMLString::transcode(parent_node->getNodeName());
			if (node_name == std::string("fav")) {

                fav->setMetadataId     (getElementString(dynamic_cast<xercesc::DOMElement*>(current_metadata), "id"   ));
				fav->setMetadataTitle  (getElementString(dynamic_cast<xercesc::DOMElement*>(current_metadata), "title"));
				fav->setMetadataAuthor (getElementString(dynamic_cast<xercesc::DOMElement*>(current_metadata), "author"));
				fav->setMetadataLicense(getElementString(dynamic_cast<xercesc::DOMElement*>(current_metadata), "license"));
                std::string note = getElementString(dynamic_cast<xercesc::DOMElement*>(current_metadata), "note");
                if(note != "") fav->setMetadataNote(note);
            }
            xercesc::XMLString::release(&node_name);
		}
	}

	void FavReader::readPalette(xercesc::DOMNodeList *palette_list_) {

		// load geometries
		xercesc::DOMNodeList* geometry_list = getElements(dynamic_cast<xercesc::DOMElement*>(palette_list_->item(0)), "geometry");
		int number_of_geometry = int(geometry_list->getLength());

		for (int i=0; i<number_of_geometry; ++i) {

			std::string  id          =     getAttribute(dynamic_cast<xercesc::DOMElement*>(geometry_list->item(i)), "id"       );
			std::string  name        =     getAttribute(dynamic_cast<xercesc::DOMElement*>(geometry_list->item(i)), "name"     );
            std::string  shape       = getElementString(dynamic_cast<xercesc::DOMElement*>(geometry_list->item(i)), "shape"    );
            std::string  reference   = getElementString(dynamic_cast<xercesc::DOMElement*>(geometry_list->item(i)), "reference");
            xercesc::DOMNodeList* scale_node = getElements(dynamic_cast<xercesc::DOMElement*>(geometry_list->item(i)), "scale"    );
            
            Geometry current_geometry(std::stoi(id), name);
            
            if(shape == "cube"){
             
                current_geometry.setShape(GeometryShape::cube);
            
            }else if(shape == "sphere"){

                current_geometry.setShape(GeometryShape::sphere);

            }else if(shape == "user_defined"){
                
                current_geometry.setShape(GeometryShape::user_defined);
                current_geometry.setReference(reference);
            }
            
			if (scale_node->getLength() > 0) {
				double x = getElementDouble(dynamic_cast<xercesc::DOMElement*>(scale_node->item(0)), "x");
				double y = getElementDouble(dynamic_cast<xercesc::DOMElement*>(scale_node->item(0)), "y");
				double z = getElementDouble(dynamic_cast<xercesc::DOMElement*>(scale_node->item(0)), "z");
				current_geometry.setScale(x, y, z);
			}
            
			fav->palette.addGeometry(current_geometry);
		}

        // load materials
		xercesc::DOMNodeList* material_list = getElements(dynamic_cast<xercesc::DOMElement*>(palette_list_->item(0)), "material");
		int number_of_material = int(material_list->getLength());

		for (int i = 0; i < number_of_material; ++i) {
            
			//load attributes
            std::string id   = getAttribute(dynamic_cast<xercesc::DOMElement*>(material_list->item(i)), "id"  );
			std::string name = getAttribute(dynamic_cast<xercesc::DOMElement*>(material_list->item(i)), "name");
			Material current_material(std::stoi(id), name);
            
            // load material name
            xercesc::DOMNodeList* material_name_list = getElements(dynamic_cast<xercesc::DOMElement*>(material_list->item(i)), "material_name");
			int number_of_material_name = int(material_name_list->getLength());
            
            for(int j=0; j<number_of_material_name; ++j){
                const XMLCh* node_value = ((material_name_list->item(j))->getFirstChild())->getNodeValue();
                char* node_value_str    = xercesc::XMLString::transcode(node_value);
                std::string name        = std::string(node_value_str);
                xercesc::XMLString::release(&node_value_str);
                current_material.addMaterialName(name);
            }
            
			// load product_info
			xercesc::DOMNodeList* product_info_list = getElements(dynamic_cast<xercesc::DOMElement*>(material_list->item(i)), "product_info");
			int number_of_product_info = int(product_info_list->getLength());
            
			for (int j = 0; j < number_of_product_info; ++j) {
				std::string manufacturer = getElementString(dynamic_cast<xercesc::DOMElement*>(product_info_list->item(j)), "manufacturer");
				std::string product_name = getElementString(dynamic_cast<xercesc::DOMElement*>(product_info_list->item(j)), "product_name");
				std::string url          = getElementString(dynamic_cast<xercesc::DOMElement*>(product_info_list->item(j)), "url");
				current_material.addProductInfo(manufacturer, product_name, url);
			}

			// load iso_standard
			xercesc::DOMNodeList* iso_standard_list = getElements(dynamic_cast<xercesc::DOMElement*>(material_list->item(i)), "iso_standard");
			int number_of_iso_standard = int(iso_standard_list->getLength());

			for (int j = 0; j < number_of_iso_standard; ++j) {
				std::string iso_id   = getElementString(dynamic_cast<xercesc::DOMElement*>(iso_standard_list->item(j)), "iso_id");
				std::string iso_name = getElementString(dynamic_cast<xercesc::DOMElement*>(iso_standard_list->item(j)), "iso_name");
				current_material.addIsoStandard(iso_id, iso_name);
			}
            
            // load metadata
            xercesc::DOMNodeList* metadata_list = getElements(dynamic_cast<xercesc::DOMElement*>(material_list->item(i)), "metadata");
            if(metadata_list->getLength() > 0){
                current_material.setMetadataId     (getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "id"   ));
                current_material.setMetadataTitle  (getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "title"));
                current_material.setMetadataAuthor (getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "author"));
                current_material.setMetadataLicense(getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "license"));
                std::string note = getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "note");
                if(note != "") current_material.setMetadataNote(note);
            }
            
			fav->palette.addMaterial(current_material);
		}
	}

	void FavReader::readVoxel(xercesc::DOMNodeList *voxel_list_) {

		int number_of_voxels = int(voxel_list_->getLength());
		for (int i = 0; i < number_of_voxels; ++i) {

			xercesc::DOMElement* voxel = dynamic_cast<xercesc::DOMElement*>(voxel_list_->item(i));
			
            //load attributes
			std::string id   = getAttribute(voxel, "id"  );
			std::string name = getAttribute(voxel, "name");
			Voxel current_voxel(std::stoi(id), name);

			//load geometry_info
			xercesc::DOMNodeList* geoinfo_node   = getElements(voxel, "geometry_info");
			xercesc::DOMElement*  geoinfo_element = dynamic_cast<xercesc::DOMElement*>(geoinfo_node->item(0));
			int geometry_id = getElementInt(geoinfo_element, "id");
			current_voxel.setGeometryInfo(geometry_id);

			//load material_info
			double total_ratio = 0;
            xercesc::DOMNodeList* matinfo_node = getElements(voxel, "material_info");
			int number_of_matinfo = int(matinfo_node->getLength());
           			
            for (int j = 0; j < number_of_matinfo; ++j) {
				xercesc::DOMElement* matinfo_element = dynamic_cast<xercesc::DOMElement*>(matinfo_node->item(j));
				int    material_id    = getElementInt   (matinfo_element, "id");
				double material_ratio = getElementDouble(matinfo_element, "ratio");
				current_voxel.addMaterialInfo(material_id, material_ratio);
                total_ratio += material_ratio;
			}
            
            if( total_ratio != 1.0 ) printf("!!!WARNING!!! : the total ration of the voxel [id:%s, name:%s] is not 1.0!\n", id.c_str(), name.c_str());
			fav->addVoxel(current_voxel);
		}
	}
    
    void FavReader::readGrid(xercesc::DOMElement *object_elem, Object* current_object){
        
        
        // load origin
        xercesc::DOMNodeList* origin_node = getElements(object_elem, "origin");
        if (origin_node->getLength() > 0) {
            double x = getElementDouble(dynamic_cast<xercesc::DOMElement*>(origin_node->item(0)), "x");
            double y = getElementDouble(dynamic_cast<xercesc::DOMElement*>(origin_node->item(0)), "y");
            double z = getElementDouble(dynamic_cast<xercesc::DOMElement*>(origin_node->item(0)), "z");
            current_object->grid.setOrigin(x, y, z);
        }
        
        // load unit
        xercesc::DOMNodeList* unit_node = getElements(object_elem, "unit");
        if (unit_node->getLength() > 0) {
            double x = getElementInt(dynamic_cast<xercesc::DOMElement*>(unit_node->item(0)), "x");
            double y = getElementInt(dynamic_cast<xercesc::DOMElement*>(unit_node->item(0)), "y");
            double z = getElementInt(dynamic_cast<xercesc::DOMElement*>(unit_node->item(0)), "z");
            current_object->grid.setUnit(x, y, z);
        }
        
        // load dimension
        xercesc::DOMNodeList* dimension_node = getElements(object_elem, "dimension");
        if (dimension_node->getLength() > 0) {
            int x = getElementInt(dynamic_cast<xercesc::DOMElement*>(dimension_node->item(0)), "x");
            int y = getElementInt(dynamic_cast<xercesc::DOMElement*>(dimension_node->item(0)), "y");
            int z = getElementInt(dynamic_cast<xercesc::DOMElement*>(dimension_node->item(0)), "z");
            current_object->grid.setDimension(x, y, z);
        }
    }
    
    void FavReader::readVoxelMap(xercesc::DOMElement *object_elem, Object* current_object, FavLibrary::Structure* structure){
   
        xercesc::DOMElement* vmap_elem = dynamic_cast<xercesc::DOMElement*>(getElements(object_elem, "voxel_map")->item(0));
        std::string compression   = getAttribute(vmap_elem, "compression");
        std::string bit_per_voxel = getAttribute(vmap_elem, "bit_per_voxel");
        
        
        if(bit_per_voxel == "4")
            structure->setBitPerVoxel(BitPerVoxel::Bit4);
        
        else if(bit_per_voxel == "8")
            structure->setBitPerVoxel(BitPerVoxel::Bit8);
        
        else if(bit_per_voxel == "16")
            structure->setBitPerVoxel(BitPerVoxel::Bit16);
    
        structure->initVoxelMap();
        
        xercesc::DOMNodeList* vmap_layers = getElements(vmap_elem, "layer");
        int number_of_layers = int(vmap_layers->getLength());
        
        for (int j = 0; j < number_of_layers; ++j) {
            
            std::string layer_data = getNodeValueString(vmap_layers->item(j)->getFirstChild());
            std::string data_in = "";
            
            if (compression == "none") {
                
                if (bit_per_voxel == "4") {
                    data_in.resize(layer_data.size());
                    for (int k = 0; k < (int)layer_data.size(); k++) {
                        int dec = 0;
                        char hex[2] = { layer_data[k], layer_data[k + 1] };
                        sscanf(hex, "%01x", &dec);
                        data_in[k] = dec; //if compressed using this scheme
                    }
                    
                }
                else if (bit_per_voxel == "8") {
                    data_in.resize(layer_data.size() / 2);
                    int cur = 0;
                    for (int k = 0; k < (int)layer_data.size(); k = k + 2) {
                        int dec = 0;
                        char hex[2] = { layer_data[k], layer_data[k + 1] };
                        sscanf(hex, "%02x", &dec);
                        data_in[cur] = dec; //if compressed using this scheme
                        cur++;
                    }
                }
                else if (bit_per_voxel == "16") {
                    data_in.resize(layer_data.size() / 4);
                    int cur = 0;
                    for (int k = 0; k < (int)layer_data.size(); k = k + 4) {
                        int dec = 0;
                        char hex[4] = { layer_data[k], layer_data[k + 1], layer_data[k + 2], layer_data[k + 3] };
                        sscanf(hex, "%04x", &dec);
                        data_in[cur] = dec; //if compressed using this scheme
                        cur++;
                    }
                }
                
            // TODO: Zlib compression is under development
            } else if (compression == "base64") {
                
                XMLSize_t size = current_object->grid.getDimensionX() * current_object->grid.getDimensionY();
                data_in.resize(size);
                std::string input_str = getNodeValueString(vmap_layers->item(j)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                for (int d = 0; d < size; d++) {
                    data_in[d] = (unsigned int)data_decoded[d];
                }
				delete data_decoded;
            }
            
            int dim_x = current_object->grid.getDimensionX();
            int dim_y = current_object->grid.getDimensionY();
            int layer_size = dim_x * dim_y;
            
            if (data_in.size() != layer_size) {
                // TODO: エラー処理
            }else{
                
                for (int k = 0; k < layer_size; k++) {
                    
                    int index = layer_size*j + k;
                    structure->setVoxel(index, (int)data_in[k]);                    
                }
            }
        }
    }
    
    
    void FavReader::readColorMapRGB(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        xercesc::DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_r;
        int* layer_g;
        int* layer_b;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            
            int count_colors = 0;
            for(int y=0; y<current_object->grid.getDimensionY(); ++y){
                for(int x=0; x<current_object->grid.getDimensionX(); ++x){
                    if(structure->getVoxel(x,y,z) > 0 )
                        count_colors++;
                }
            }
            
            layer_r = new int[count_colors]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            layer_g = new int[count_colors];
            layer_b = new int[count_colors];
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+6){
                    
                    int r_value, g_value, b_value = 0;
                    char r[2] = {layer_data[i],  layer_data[i+1]};
                    char g[2] = {layer_data[i+2],layer_data[i+3]};
                    char b[2] = {layer_data[i+4],layer_data[i+5]};
                    sscanf(r, "%02x", &r_value);
                    sscanf(g, "%02x", &g_value);
                    sscanf(b, "%02x", &b_value);
                    layer_r[i/6] = r_value;
                    layer_g[i/6] = g_value;
                    layer_b[i/6] = b_value;
                    
                }
                
            }else if (compression == "base64") {
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(layer_data.c_str()), &size);
                
                int count = 0;
                for (int d = 0; d < size; d=d+3) {
                    layer_r[count] = (unsigned int)data_decoded[d];
                    layer_g[count] = (unsigned int)data_decoded[d+1];
                    layer_b[count] = (unsigned int)data_decoded[d+2];
                    count++;
                }
				delete data_decoded;
            }
            
            int dim_x = current_object->grid.getDimensionX();
            int dim_y = current_object->grid.getDimensionY();
            int count = 0;
            
            for(int y=0; y<dim_y; y++){
                for(int x=0; x<dim_x; x++){
                    
                    if(structure->getVoxel(x,y,z) != 0){
                        ColorRGB color_rgb(layer_r[count], layer_g[count], layer_b[count]);
                        structure->setColor(x,y,z, color_rgb);
                        count++;
                        
                    }else{
                        structure->setColor(x,y,z, ColorRGB(0, 0, 0));
                    }
                    
                }
            }
            delete[] layer_r;
            delete[] layer_g;
            delete[] layer_b;
            layer_r = nullptr;
            layer_g = nullptr;
            layer_b = nullptr;
        }
    }
    
    void FavReader::readColorMapRGBA(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        xercesc::DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_r;
        int* layer_g;
        int* layer_b;
        int* layer_a;

        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in;
            
            layer_r = new int[layer_data.size()/(2*4)]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            layer_g = new int[layer_data.size()/(2*4)];
            layer_b = new int[layer_data.size()/(2*4)];
            layer_a = new int[layer_data.size()/(2*4)];

            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+8){
                    
                    int r_value, g_value, b_value = 0;
                    char r[2] = {layer_data[i],  layer_data[i+1]};
                    char g[2] = {layer_data[i+2],layer_data[i+3]};
                    char b[2] = {layer_data[i+4],layer_data[i+5]};
                    char a[2] = {layer_data[i+6],layer_data[i+7]};

                    sscanf(r, "%02x", &r_value);
                    sscanf(g, "%02x", &g_value);
                    sscanf(b, "%02x", &b_value);
                    sscanf(a, "%02x", &b_value);

                    layer_r[i/6] = r_value;
                    layer_g[i/6] = g_value;
                    layer_b[i/6] = b_value;
                    layer_a[i/6] = b_value;
                    
                }
                
            }else if (compression == "base64") {
                
                int count_colors = 0;
                for(int y=0; y<current_object->grid.getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid.getDimensionX(); ++x){
                        if(structure->getVoxel(x,y,z) > 0 )
                            count_colors++;
                    }
                }
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                int count = 0;
                for (int d = 0; d < size; d=d+4) {
                    layer_r[count] = (unsigned int)data_decoded[d];
                    layer_g[count] = (unsigned int)data_decoded[d+1];
                    layer_b[count] = (unsigned int)data_decoded[d+2];
                    layer_a[count] = (unsigned int)data_decoded[d+3];
                    count++;
                }
				delete data_decoded;
            }
            
            int dim_x = current_object->grid.getDimensionX();
            int dim_y = current_object->grid.getDimensionY();
            int count = 0;
            
            for(int y=0; y<dim_y; y++){
                for(int x=0; x<dim_x; x++){
                    
                    if(structure->getVoxel(x,y,z) > 0){
                        
                        ColorRGBA color_rgba(layer_r[count], layer_g[count], layer_b[count], layer_a[count]);
                        structure->setColor(x,y,z, color_rgba);
                        count++;
                        
                    }else{
                        structure->setColor(x,y,z, ColorRGBA(0, 0, 0, 0));
                    }
                    
                }
            }
            
            delete[] layer_r;
            delete[] layer_g;
            delete[] layer_b;
            delete[] layer_a;
            layer_r = nullptr;
            layer_g = nullptr;
            layer_b = nullptr;
            layer_a = nullptr;
        }
        
        
    }
    
    void FavReader::readColorMapCMYK(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        xercesc::DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_c;
        int* layer_m;
        int* layer_y;
        int* layer_k;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in = "";
            
            layer_c = new int[layer_data.size()/(2*4)]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            layer_m = new int[layer_data.size()/(2*4)];
            layer_y = new int[layer_data.size()/(2*4)];
            layer_k = new int[layer_data.size()/(2*4)];
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+8){
                    
                    int r_value, g_value, b_value = 0;
                    char r[2] = {layer_data[i],  layer_data[i+1]};
                    char g[2] = {layer_data[i+2],layer_data[i+3]};
                    char b[2] = {layer_data[i+4],layer_data[i+5]};
                    char a[2] = {layer_data[i+6],layer_data[i+7]};
                    
                    sscanf(r, "%02x", &r_value);
                    sscanf(g, "%02x", &g_value);
                    sscanf(b, "%02x", &b_value);
                    sscanf(a, "%02x", &b_value);
                    
                    layer_c[i/6] = r_value;
                    layer_m[i/6] = g_value;
                    layer_y[i/6] = b_value;
                    layer_k[i/6] = b_value;
                    
                }
                
            }else if (compression == "base64") {
                
                int count_colors = 0;
                for(int y=0; y<current_object->grid.getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid.getDimensionX(); ++x){
                        if(structure->getVoxel(x,y,z) > 0 )
                            count_colors++;
                    }
                }
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                int count = 0;
                for (int d = 0; d < size; d=d+4) {
                    layer_c[count] = (unsigned int)data_decoded[d];
                    layer_m[count] = (unsigned int)data_decoded[d+1];
                    layer_y[count] = (unsigned int)data_decoded[d+2];
                    layer_k[count] = (unsigned int)data_decoded[d+3];
                    count++;
                }
				delete data_decoded;
            }
            
            int dim_x = current_object->grid.getDimensionX();
            int dim_y = current_object->grid.getDimensionY();
            int count = 0;
            
            for(int y=0; y<dim_y; y++){
                for(int x=0; x<dim_x; x++){
                    
                    if(structure->getVoxel(x,y,z) > 0){
                        
                        ColorCMYK color_cmyk(layer_c[count], layer_m[count], layer_y[count], layer_k[count]);
                        structure->setColor(x,y,z, color_cmyk);
                        count++;
                        
                    }else{
                        structure->setColor(x,y,z, ColorCMYK(0, 0, 0, 0));
                    }
                    
                }
            }
            
            delete[] layer_c;
            delete[] layer_m;
            delete[] layer_y;
            delete[] layer_k;
            
            layer_c = nullptr;
            layer_m = nullptr;
            layer_y = nullptr;
            layer_k = nullptr;
        }
    }
    
    void FavReader::readColorMapGrayscale(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        xercesc::DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_g;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in = "";
            
            layer_g = new int[layer_data.size()/2]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+2){
                    
                    int gray_value = 0;
                    char gray[2] = {layer_data[i],  layer_data[i+1]};
                    sscanf(gray, "%02x", &gray_value);
                    layer_g[i/2] = gray_value;
                }
                
            }else if (compression == "base64") {
                
                int count_colors = 0;
                for(int y=0; y<current_object->grid.getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid.getDimensionX(); ++x){
                        if(structure->getVoxel(x,y,z) > 0 )
                            count_colors++;
                    }
                }
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                for (int d = 0; d < size; ++d) {
                    layer_g[d] = (unsigned int)data_decoded[d];
                }
				delete data_decoded;
            }
            
            int dim_x = current_object->grid.getDimensionX();
            int dim_y = current_object->grid.getDimensionY();
            int count = 0;
            
            for(int y=0; y<dim_y; y++){
                for(int x=0; x<dim_x; x++){
                    
                    if(structure->getVoxel(x,y,z) > 0){
                        
                        structure->setColor(x,y,z, layer_g[count]);
                        count++;
                        
                    }else{
                        structure->setColor(x,y,z, 0);
                    }
                    
                }
            }
            delete[] layer_g;
            layer_g = nullptr;
        }
    }
    
    void FavReader::readColorMapGrayscale16(xercesc::DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        xercesc::DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_g;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in = "";
            
            layer_g = new int[layer_data.size()/2]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+4){
                    
                    int gray_value = 0;
                    char gray[4] = {layer_data[i],  layer_data[i+1], layer_data[i+2],  layer_data[i+3] };
                    sscanf(gray, "%04x", &gray_value);
                    layer_g[i/4] = gray_value;
                }
                
            }else if (compression == "base64") {
                
                int count_colors = 0;
                for(int y=0; y<current_object->grid.getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid.getDimensionX(); ++x){
                        if(structure->getVoxel(x,y,z) > 0 )
                            count_colors++;
                    }
                }
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                for (int d = 0; d < size; ++d) {
                    layer_g[d] = (unsigned int)data_decoded[d];
                }
				delete data_decoded;
            }
            
            int dim_x = current_object->grid.getDimensionX();
            int dim_y = current_object->grid.getDimensionY();
            int count = 0;
            
            for(int y=0; y<dim_y; y++){
                for(int x=0; x<dim_x; x++){
                    
                    if(structure->getVoxel(x,y,z) > 0){
                        
                        structure->setColor(x,y,z, layer_g[count]);
                        count++;
                        
                    }else{
                        structure->setColor(x,y,z, 0);
                    }
                    
                }
            }
            delete[] layer_g;
            layer_g = nullptr;
        }
    }
    
    void FavReader::readColorMap(xercesc::DOMElement *object_elem, Object* current_object, FavLibrary::Structure* structure){
       
        xercesc::DOMElement* cmap_elem = dynamic_cast<xercesc::DOMElement*>( getElements(object_elem, "color_map")->item(0) );
        
        if(cmap_elem != NULL){
            std::string color_mode_str = getAttribute(cmap_elem, "color_mode");
            
            if(color_mode_str == "RGB"){
                structure->initColorMap(FavLibrary::ColorMode::RGB);
                readColorMapRGB(cmap_elem, current_object, structure);
                
            }else if(color_mode_str == "RGBA"){
                structure->initColorMap(FavLibrary::ColorMode::RGBA);
                readColorMapRGBA(cmap_elem, current_object, structure);
                
            }else if(color_mode_str == "CMYK"){
                structure->initColorMap(FavLibrary::ColorMode::CMYK);
                readColorMapCMYK(cmap_elem, current_object, structure);
                
            }else if(color_mode_str == "GrayScale"){
                structure->initColorMap(FavLibrary::ColorMode::Grayscale);
                readColorMapGrayscale(cmap_elem, current_object, structure);
                
            }else if(color_mode_str == "GrayScale16"){
                structure->initColorMap(FavLibrary::ColorMode::Grayscale16);
                readColorMapGrayscale16(cmap_elem, current_object, structure);
                
            }
        }
    }

	void FavReader::readObject(xercesc::DOMNodeList *object_node_) {

        
		int number_of_object = int(object_node_->getLength());
		for (int i=0; i<number_of_object; ++i) {
            
			xercesc::DOMElement* object_elem = dynamic_cast<xercesc::DOMElement*>(object_node_->item(i));

			//load attributes
			std::string id   = getAttribute(object_elem, "id"  );
			std::string name = getAttribute(object_elem, "name");
            
			Object* current_object = new Object(stoi(id), name);

            readGrid(object_elem, current_object);
            
            // load Structure
            readVoxelMap(object_elem, current_object, &current_object->structure);
            readColorMap(object_elem, current_object, &current_object->structure);
            

            // load metadata
            xercesc::DOMNodeList* metadata_list = getElements(object_elem, "metadata");
            if(metadata_list->getLength() > 0){
                current_object->setMetadataId     (getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "id"   ));
                current_object->setMetadataTitle  (getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "title"));
                current_object->setMetadataAuthor (getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "author"));
                current_object->setMetadataLicense(getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "license"));
                std::string note = getElementString(dynamic_cast<xercesc::DOMElement*>(metadata_list->item(0)), "note");
                if(note != "") current_object->setMetadataNote(note);
            }
			fav->addObject(*current_object);
            delete current_object;
        }
	}
    
    xercesc::DOMNodeList* FavReader::getElements(xercesc::DOMElement* element_, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        XMLCh* attribute_name = xercesc::XMLString::transcode(tag_name);
        xercesc::DOMNodeList* node_list = element_->getElementsByTagName(attribute_name);
        xercesc::XMLString::release(&attribute_name);
        
        return node_list;
    }
    
    std::string FavReader::getAttribute(xercesc::DOMElement* element_, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        XMLCh* attribute_name = xercesc::XMLString::transcode(tag_name);
        const XMLCh* attribute_value = element_->getAttribute(attribute_name);
        char* attribute_value_str = xercesc::XMLString::transcode(attribute_value);
        std::string ret = std::string(attribute_value_str);
        
        xercesc::XMLString::release(&attribute_name);
        xercesc::XMLString::release(&attribute_value_str);

        return ret;
    }
    
    int FavReader::getNodeValueInt(xercesc::DOMNode* node_)
    {
        const XMLCh* node_value = node_->getNodeValue();
        char* node_value_str = xercesc::XMLString::transcode(node_value);
        int ret = atoi(node_value_str);
        
        xercesc::XMLString::release(&node_value_str);
        return ret;
    }
    
    double FavReader::getNodeValueDouble(xercesc::DOMNode* node_)
    {
        const XMLCh* node_value = node_->getNodeValue();
        char* node_value_str = xercesc::XMLString::transcode(node_value);
        double ret = atof(node_value_str);
        xercesc::XMLString::release(&node_value_str);
        return ret;
    }
    
    std::string FavReader::getNodeValueString(xercesc::DOMNode* node_)
    {
        const XMLCh* node_value = node_->getNodeValue();
        char* node_value_str = xercesc::XMLString::transcode(node_value);
        std::string ret = std::string(node_value_str);
        xercesc::XMLString::release(&node_value_str);
        return ret;
    }
    
    int FavReader::getElementInt(xercesc::DOMElement* elem, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        xercesc::DOMNodeList* node_list = getElements(elem, tag_name);
        const XMLCh* node_value = ((node_list->item(0))->getFirstChild())->getNodeValue();
        char* node_value_str = xercesc::XMLString::transcode(node_value);
        int ret = atoi(node_value_str);
        xercesc::XMLString::release(&node_value_str);
        return ret;
    }
    
    double FavReader::getElementDouble(xercesc::DOMElement* elem, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        xercesc::DOMNodeList* node_list = getElements(elem, tag_name);
        const XMLCh* node_value = ((node_list->item(0))->getFirstChild())->getNodeValue();
        char* node_value_str = xercesc::XMLString::transcode(node_value);
        double ret = atof(node_value_str);
        xercesc::XMLString::release(&node_value_str);
        return ret;
    }
    
    std::string FavReader::getElementString(xercesc::DOMElement* elem, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        xercesc::DOMNodeList* node_list = getElements(elem, tag_name);
        std::string ret = "";
        if(node_list->getLength()>0){
            const XMLCh* node_value = ((node_list->item(0))->getFirstChild())->getNodeValue();
            char* node_value_str = xercesc::XMLString::transcode(node_value);
            ret = std::string(node_value_str);
            xercesc::XMLString::release(&node_value_str);
        }
        return ret;
    }
    


    //TODO Fav 1.1からmaterial_info のmaterial id = 0 を許可するので以下の書き直しを行った
    //古)"<xsd:element name=\"id\"    type=\"xsd:positiveInteger\" minOccurs=\"1\" maxOccurs=\"1\"/>"
    //新)"<xsd:element name=\"id\"    type=\"xsd:nonNegativeInteger\" minOccurs=\"1\" maxOccurs=\"1\"/>"

    void FavReader::setXsdSchemaAsString(){
        
        xsd_string =
        "<?xml version=\"1.0\"?>"
        "<xsd:schema xmlns:xsd=\"http://www.w3.org/2001/XMLSchema\">"
        
        "<xsd:element name=\"fav\">"
        "<xsd:complexType>"
        "<xsd:choice minOccurs=\"1\" maxOccurs=\"unbounded\">"
        "<xsd:element ref=\"metadata\"/>"
        "<xsd:element ref=\"palette\"/>"
        "<xsd:element ref=\"voxel\"/>"
        "<xsd:element ref=\"object\"/>"
        "</xsd:choice>"
        "<xsd:attribute name=\"version\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"metadata\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"id\"      minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"title\"   minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"author\"  minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"license\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"note\"    minOccurs=\"0\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"palette\">"
        "<xsd:complexType>"
        "<xsd:choice maxOccurs=\"unbounded\">"
        "<xsd:element ref=\"geometry\" />"
        "<xsd:element ref=\"material\" />"
        "</xsd:choice>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"geometry\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"shape\"     type=\"xsd:string\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"reference\" type=\"xsd:string\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element  ref=\"scale\"                       minOccurs=\"0\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "<xsd:attribute name=\"id\"   type=\"xsd:positiveInteger\" use=\"required\"/>"
        "<xsd:attribute name=\"name\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"scale\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"x\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"y\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"z\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"material\">"
        "<xsd:complexType>"
        "<xsd:choice minOccurs=\"0\" maxOccurs=\"unbounded\">"
        "<xsd:element name=\"material_name\" type=\"xsd:string\"/>"
        "<xsd:element  ref=\"product_info\"/>"
        "<xsd:element  ref=\"iso_standard\"/>"
        "</xsd:choice>"
        "<xsd:attribute name=\"id\"   type=\"xsd:positiveInteger\" use=\"required\"/>"
        "<xsd:attribute name=\"name\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"product_info\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"manufacturer\" type=\"xsd:string\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"product_name\" type=\"xsd:string\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"url\"          type=\"xsd:anyURI\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"iso_standard\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"iso_id\"   type=\"xsd:string\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"iso_name\" type=\"xsd:string\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"voxel\">"
        "<xsd:complexType>"
        "<xsd:choice maxOccurs=\"unbounded\">"
        "<xsd:element ref=\"geometry_info\"/>"
        "<xsd:element ref=\"material_info\"/>"
        "<xsd:element ref=\"display\"/>"
        "<xsd:element name=\"application_note\" type=\"xsd:string\"/>"
        "</xsd:choice>"
        "<xsd:attribute name=\"id\"   type=\"xsd:positiveInteger\" use=\"required\"/>"
        "<xsd:attribute name=\"name\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"geometry_info\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"id\" type=\"xsd:positiveInteger\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"material_info\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"id\"    type=\"xsd:nonNegativeInteger\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"ratio\" type=\"xsd:double\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"display\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"r\" type=\"xsd:nonNegativeInteger\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"g\" type=\"xsd:nonNegativeInteger\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"b\" type=\"xsd:nonNegativeInteger\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"a\" type=\"xsd:nonNegativeInteger\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"object\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element ref=\"metadata\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element ref=\"grid\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element ref=\"structure\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "<xsd:attribute name=\"id\"   type=\"xsd:positiveInteger\" use=\"required\"/>"
        "<xsd:attribute name=\"name\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"grid\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element ref=\"origin\"    minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element ref=\"unit\"      minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element ref=\"dimension\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"origin\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"x\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"y\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"z\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"unit\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"x\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"y\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"z\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"dimension\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element name=\"x\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"y\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element name=\"z\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"structure\">"
        "<xsd:complexType>"
        "<xsd:all>"
        "<xsd:element ref=\"voxel_map\" minOccurs=\"1\" maxOccurs=\"1\"/>"
        "<xsd:element ref=\"color_map\" minOccurs=\"0\" maxOccurs=\"1\"/>"
        "<xsd:element ref=\"link_map\"  minOccurs=\"0\" maxOccurs=\"1\"/>"
        "</xsd:all>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"voxel_map\">"
        "<xsd:complexType>"
        "<xsd:sequence>"
        "<xsd:element name=\"layer\" minOccurs=\"1\" maxOccurs=\"unbounded\"/>"
        "</xsd:sequence>"
        "<xsd:attribute name=\"bit_per_voxel\" type=\"xsd:positiveInteger\" use=\"required\"/>"
        "<xsd:attribute name=\"compression\"   type=\"xsd:string\" default=\"none\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"color_map\">"
        "<xsd:complexType>"
        "<xsd:sequence>"
        "<xsd:element name=\"layer\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>"
        "</xsd:sequence>"
        "<xsd:attribute name=\"color_mode\"  type=\"xsd:string\" use=\"required\"/>"
        "<xsd:attribute name=\"compression\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        
        "<xsd:element name=\"link_map\">"
        "<xsd:complexType>"
        "<xsd:sequence>"
        "<xsd:element name=\"layer\" minOccurs=\"0\" maxOccurs=\"unbounded\"/>"
        "</xsd:sequence>"
        "<xsd:attribute name=\"neighbors\"   type=\"xsd:string\" use=\"required\"/>"
        "<xsd:attribute name=\"compression\" type=\"xsd:string\"/>"
        "</xsd:complexType>"
        "</xsd:element>"
        "</xsd:schema>";
        
    }
    
}
