//
//  FavReader.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#include "FavReader.h"
#include "Fav.h"

using namespace xercesc;

namespace FavLibrary
{

    FavReader::FavReader(Fav* fav_) {
        fav = fav_;
        //FIXME: xsdのパスの指定の仕方を検討
        xsd_path = "file:///Users/atsmsmr/Documents/Developer/fav-project/xml_schema/fav.xsd";
    };
    

    bool FavReader::validation(const char* file_path)
    {
        ParserErrorHandler parserErrorHandler;
        
        XercesDOMParser domParser;
        
        if (domParser.loadGrammar(xsd_path.c_str(), Grammar::SchemaGrammarType) == NULL)
        {
            fprintf(stderr, "couldn't load schema\n");
            return 0;
        }
        
        domParser.setErrorHandler(&parserErrorHandler);
        domParser.setValidationScheme(XercesDOMParser::Val_Auto);
        domParser.setDoNamespaces(true);
        domParser.setDoSchema(true);
        domParser.setValidationSchemaFullChecking(true);
//        domParser.setValidationConstraintFatal(true);
        domParser.setExternalNoNamespaceSchemaLocation(xsd_path.c_str());
        domParser.parse(file_path);
        
        if (domParser.getErrorCount() == 0)
            printf("This file confirm to Fav ver.1.0\n");
        else
            printf("This file doesn't conform to Fav ver.1.0\n");
        
        return 1;
    }
    
    bool FavReader::read(const char* file_path) {
        
        // TODO: エラー処理
        // Xerces-C++を初期化、検証する
        try {
            XMLPlatformUtils::Initialize();
        }
        catch (...) {
            //        std::cout << "Xerces-C++の初期化に失敗しました。" << std::endl;
            return 0;
        }
        
        validation(file_path);
        
        XercesDOMParser *parser = new XercesDOMParser;
        parser->parse(file_path);
        
        DOMDocument *doc  = parser->getDocument();
        DOMElement  *root = doc->getDocumentElement();
        
        DOMNodeList* metadata_list = getElements(root, "metadata");
        DOMNodeList* palette_list  = getElements(root, "palette" );
        DOMNodeList* voxel_list    = getElements(root, "voxel"   );
        DOMNodeList* object_list   = getElements(root, "object"  );
        
        readMetaData(metadata_list);
        readPalette (palette_list);
        readVoxel   (voxel_list);
        readObject  (object_list);
        
        XMLPlatformUtils::Terminate();
        
        return 1;
    }

    // FIXME: MetaData
    // この関数は、各タグの読み込み関数の内部で仕様するように変更する
	void FavReader::readMetaData(xercesc_3_1::DOMNodeList *metadata_node_) {

		int number_of_metadata = int(metadata_node_->getLength());

		for (int i=0; i<number_of_metadata; ++i) {

			DOMNode *current_metadata = metadata_node_->item(i);
			DOMNode *parent_node = dynamic_cast<DOMElement*>(current_metadata)->getParentNode();

			if (XMLString::transcode(parent_node->getNodeName()) == std::string("fav")) {

                fav->setMetadataId     (getElementString(dynamic_cast<DOMElement*>(current_metadata), "id"   ));
				fav->setMetadataTitle  (getElementString(dynamic_cast<DOMElement*>(current_metadata), "title"));
				fav->setMetadataAuthor (getElementString(dynamic_cast<DOMElement*>(current_metadata), "author"));
				fav->setMetadataLicense(getElementString(dynamic_cast<DOMElement*>(current_metadata), "license"));
                fav->setMetadataNote   (getElementString(dynamic_cast<DOMElement*>(current_metadata), "note"));
            
            }else{
                //TODO: MetaData
                // fav以外の階層でのmetadataの読み込み
            }

		}

	}

	void FavReader::readPalette(xercesc_3_1::DOMNodeList *palette_list_) {

		// load geometries
		DOMNodeList* geometry_list = getElements(dynamic_cast<DOMElement*>(palette_list_->item(0)), "geometry");
		int number_of_geometry = int(geometry_list->getLength());

		for (int i=0; i<number_of_geometry; ++i) {

			std::string  id          =     getAttribute(dynamic_cast<DOMElement*>(geometry_list->item(i)), "id"       );
			std::string  name        =     getAttribute(dynamic_cast<DOMElement*>(geometry_list->item(i)), "name"     );
            std::string  shape       = getElementString(dynamic_cast<DOMElement*>(geometry_list->item(i)), "shape"    );
            std::string  reference   = getElementString(dynamic_cast<DOMElement*>(geometry_list->item(i)), "reference");
            DOMNodeList* scale_node  =      getElements(dynamic_cast<DOMElement*>(geometry_list->item(i)), "scale"    );
            
            Geometry current_geometry = Geometry(std::stoi(id), name);
            
            if(shape == "cube"){
             
                current_geometry.setShape(GeometryShape::cube);
            
            }else if(shape == "sphere"){

                current_geometry.setShape(GeometryShape::sphere);

            }else if(shape == "user_defined"){
                
                current_geometry.setShape(GeometryShape::user_defined);
                current_geometry.setReference(reference);
            }
            
			if (scale_node->getLength() > 0) {
				double x = getElementDouble(dynamic_cast<DOMElement*>(scale_node->item(0)), "x");
				double y = getElementDouble(dynamic_cast<DOMElement*>(scale_node->item(0)), "y");
				double z = getElementDouble(dynamic_cast<DOMElement*>(scale_node->item(0)), "z");
				current_geometry.setScale(x, y, z);
			}
            
            //TODO: ポインタ問題
            // ここはポインタ渡しじゃなくて良いんだっけ？一応、大丈夫そうだけど、バグが生じないか確認。
			fav->palette.addGeometry(current_geometry);
		}

        // load materials
		DOMNodeList* material_list = getElements(dynamic_cast<DOMElement*>(palette_list_->item(0)), "material");
		int number_of_material = int(material_list->getLength());

		for (int i = 0; i < number_of_material; ++i) {
            
			//load attributes
            std::string id   = getAttribute(dynamic_cast<DOMElement*>(material_list->item(i)), "id"  );
			std::string name = getAttribute(dynamic_cast<DOMElement*>(material_list->item(i)), "name");
			Material current_material = Material(std::stoi(id), name);
            
            // load material name
            DOMNodeList* material_name_list = getElements(dynamic_cast<DOMElement*>(material_list->item(i)), "material_name");
			int number_of_material_name = int(material_name_list->getLength());
            
            for(int j=0; j<number_of_material_name; ++j){
                const XMLCh* node_value = ((material_name_list->item(j))->getFirstChild())->getNodeValue();
                char* node_value_str    = XMLString::transcode(node_value);
                std::string name        = std::string(node_value_str);
                XMLString::release(&node_value_str);
                current_material.addMaterialName(name);
            }
            
			// load product_info
			DOMNodeList* product_info_list = getElements(dynamic_cast<DOMElement*>(material_list->item(i)), "product_info");
			int number_of_product_info = int(product_info_list->getLength());
            
			for (int j = 0; j < number_of_product_info; ++j) {
				std::string manufacturer = getElementString(dynamic_cast<DOMElement*>(product_info_list->item(j)), "manufacturer");
				std::string product_name = getElementString(dynamic_cast<DOMElement*>(product_info_list->item(j)), "product_name");
				std::string url          = getElementString(dynamic_cast<DOMElement*>(product_info_list->item(j)), "url");
				current_material.addProductInfo(manufacturer, product_name, url);
			}

			// load iso_standard
			DOMNodeList* iso_standard_list = getElements(dynamic_cast<DOMElement*>(material_list->item(i)), "iso_standard");
			int number_of_iso_standard = int(iso_standard_list->getLength());

			for (int j = 0; j < number_of_iso_standard; ++j) {
				std::string iso_id   = getElementString(dynamic_cast<DOMElement*>(iso_standard_list->item(j)), "iso_id");
				std::string iso_name = getElementString(dynamic_cast<DOMElement*>(iso_standard_list->item(j)), "iso_name");
				current_material.addIsoStandard(iso_id, iso_name);
			}

			fav->palette.addMaterial(current_material);
		}
	}

	void FavReader::readVoxel(xercesc_3_1::DOMNodeList *voxel_list_) {

		int number_of_voxels = int(voxel_list_->getLength());
		for (int i = 0; i < number_of_voxels; ++i) {

			DOMElement* voxel = dynamic_cast<DOMElement*>(voxel_list_->item(i));
			
            //load attributes
			std::string id   = getAttribute(voxel, "id"  );
			std::string name = getAttribute(voxel, "name");
			Voxel* current_voxel = new Voxel(std::stoi(id), name);

			//load geometry_info
			DOMNodeList* geoinfo_node   = getElements(voxel, "geometry_info");
			DOMElement*  geoinfo_element = dynamic_cast<DOMElement*>(geoinfo_node->item(0));
			int geometry_id = getElementInt(geoinfo_element, "id");
			current_voxel->setGeometryInfo(geometry_id);

			//load material_info
			DOMNodeList* matinfo_node = getElements(voxel, "material_info");
			int number_of_matinfo = int(matinfo_node->getLength());
			
            for (int j = 0; j < number_of_matinfo; ++j) {
				DOMElement* matinfo_element = dynamic_cast<DOMElement*>(matinfo_node->item(j));
				int    material_id    = getElementInt   (matinfo_element, "id");
				double material_ratio = getElementDouble(matinfo_element, "ratio");
				current_voxel->addMaterialInfo(material_id, material_ratio);
			}
			fav->addVoxel(current_voxel);
		}
	}
    
    void FavReader::readGrid(xercesc_3_1::DOMElement *object_elem, Object* current_object){
        
        
        // load origin
        DOMNodeList* origin_node = getElements(object_elem, "origin");
        if (origin_node->getLength() > 0) {
            double x = getElementDouble(dynamic_cast<DOMElement*>(origin_node->item(0)), "x");
            double y = getElementDouble(dynamic_cast<DOMElement*>(origin_node->item(0)), "y");
            double z = getElementDouble(dynamic_cast<DOMElement*>(origin_node->item(0)), "z");
            current_object->grid->setOrigin(x, y, z);
        }
        
        // load unit
        DOMNodeList* unit_node = getElements(object_elem, "unit");
        if (unit_node->getLength() > 0) {
            double x = getElementInt(dynamic_cast<DOMElement*>(unit_node->item(0)), "x");
            double y = getElementInt(dynamic_cast<DOMElement*>(unit_node->item(0)), "y");
            double z = getElementInt(dynamic_cast<DOMElement*>(unit_node->item(0)), "z");
            current_object->grid->setUnit(x, y, z);
        }
        
        // load dimension
        DOMNodeList* dimension_node = getElements(object_elem, "dimension");
        if (dimension_node->getLength() > 0) {
            int x = getElementInt(dynamic_cast<DOMElement*>(dimension_node->item(0)), "x");
            int y = getElementInt(dynamic_cast<DOMElement*>(dimension_node->item(0)), "y");
            int z = getElementInt(dynamic_cast<DOMElement*>(dimension_node->item(0)), "z");
            current_object->grid->setDimension(x, y, z);
        }
    }
    
    void FavReader::readVoxelMap(xercesc_3_1::DOMElement *object_elem, Object* current_object, FavLibrary::Structure* structure){
   
        DOMElement* vmap_elem = dynamic_cast<DOMElement*>(getElements(object_elem, "voxel_map")->item(0));
        std::string compression   = getAttribute(vmap_elem, "compression");
        std::string bit_per_voxel = getAttribute(vmap_elem, "bit_per_voxel");
        
        structure->setBitPerVoxel(std::atoi(bit_per_voxel.c_str()));
        
        DOMNodeList* vmap_layers = getElements(vmap_elem, "layer");
        int number_of_layers = int(vmap_layers->getLength());
        structure->initVoxelMap();
        
        for (int j = 0; j < number_of_layers; ++j) {
            
            std::string layer_data = getNodeValueString(vmap_layers->item(j)->getFirstChild());
            std::string data_in;
            
            if (compression == "none") {
                
                if (bit_per_voxel == "4") { // need debug.
                    data_in.resize(layer_data.size());
                    for (int k = 0; k < (int)layer_data.size(); k++) {
                        int dec;
                        char hex[2] = { layer_data[k], layer_data[k + 1] };
                        sscanf(hex, "%01x", &dec);
                        data_in[k] = dec; //if compressed using this scheme
                    }
                    
                }
                else if (bit_per_voxel == "8") {
                    data_in.resize(layer_data.size() / 2);
                    int cur = 0;
                    for (int k = 0; k < (int)layer_data.size(); k = k + 2) {
                        int dec;
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
                        int dec;
                        char hex[4] = { layer_data[k], layer_data[k + 1], layer_data[k + 2], layer_data[k + 3] };
                        sscanf(hex, "%04x", &dec);
                        data_in[cur] = dec; //if compressed using this scheme
                        cur++;
                    }
                }
                
                // TODO: compression mode is under development
                // other compression mode is under development
            } else if (compression == "base64") {
                
                XMLSize_t size = current_object->grid->getDimensionX() * current_object->grid->getDimensionY();
                data_in.resize(size);
                std::string input_str = getNodeValueString(vmap_layers->item(j)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                for (int d = 0; d < size; d++) {
                    data_in[d] = (unsigned int)data_decoded[d];
                }
            }
            
            int dim_x = current_object->grid->getDimensionX();
            int dim_y = current_object->grid->getDimensionY();
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
    
    
    void FavReader::readColorMapRGB(DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_r;
        int* layer_g;
        int* layer_b;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            
            int count_colors = 0;
            for(int y=0; y<current_object->grid->getDimensionY(); ++y){
                for(int x=0; x<current_object->grid->getDimensionX(); ++x){
                    if(structure->getVoxel(x,y,z) > 0 )
                        count_colors++;
                }
            }
            
            layer_r = new int[count_colors]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            layer_g = new int[count_colors];
            layer_b = new int[count_colors];
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+6){
                    
                    int r_value, g_value, b_value;
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
            }
            
            int dim_x = current_object->grid->getDimensionX();
            int dim_y = current_object->grid->getDimensionY();
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
        }
    }
    
    void FavReader::readColorMapRGBA(DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
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
                    
                    int r_value, g_value, b_value;
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
                for(int y=0; y<current_object->grid->getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid->getDimensionX(); ++x){
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
            }
            
            int dim_x = current_object->grid->getDimensionX();
            int dim_y = current_object->grid->getDimensionY();
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
        }
    }
    
    void FavReader::readColorMapCMYK(DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_c;
        int* layer_m;
        int* layer_y;
        int* layer_k;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in;
            
            layer_c = new int[layer_data.size()/(2*4)]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            layer_m = new int[layer_data.size()/(2*4)];
            layer_y = new int[layer_data.size()/(2*4)];
            layer_k = new int[layer_data.size()/(2*4)];
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+8){
                    
                    int r_value, g_value, b_value;
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
                for(int y=0; y<current_object->grid->getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid->getDimensionX(); ++x){
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
            }
            
            int dim_x = current_object->grid->getDimensionX();
            int dim_y = current_object->grid->getDimensionY();
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
        }
    }
    
    void FavReader::readColorMapGrayscale(DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_g;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in;
            
            layer_g = new int[layer_data.size()/2]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+2){
                    
                    int gray_value;
                    char gray[2] = {layer_data[i],  layer_data[i+1]};
                    sscanf(gray, "%02x", &gray_value);
                    layer_g[i/2] = gray_value;
                }
                
            }else if (compression == "base64") {
                
                int count_colors = 0;
                for(int y=0; y<current_object->grid->getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid->getDimensionX(); ++x){
                        if(structure->getVoxel(x,y,z) > 0 )
                            count_colors++;
                    }
                }
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                int count = 0;
                for (int d = 0; d < size; ++d) {
                    layer_g[d] = (unsigned int)data_decoded[d];
                }
            }
            
            int dim_x = current_object->grid->getDimensionX();
            int dim_y = current_object->grid->getDimensionY();
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
        }
    }
    
    void FavReader::readColorMapGrayscale16(DOMElement* cmap_elem, Object* current_object, Structure* structure){
        
        std::string compression = getAttribute(cmap_elem, "compression");
        DOMNodeList* cmap_layers = getElements(cmap_elem, "layer");
        int number_of_layers = int(cmap_layers->getLength());
        
        int* layer_g;
        
        for(int z=0; z<number_of_layers; ++z){
            
            std::string layer_data = getNodeValueString( cmap_layers->item(z)->getFirstChild() );
            std::string data_in;
            
            layer_g = new int[layer_data.size()/2]; // 1 voxel has 2*[Sample_Per_Voxel] bytes.
            
            if(compression == "none"){
                
                for (int i=0; i<(int)layer_data.size(); i=i+4){
                    
                    int gray_value;
                    char gray[4] = {layer_data[i],  layer_data[i+1], layer_data[i+2],  layer_data[i+3] };
                    sscanf(gray, "%04x", &gray_value);
                    layer_g[i/4] = gray_value;
                }
                
            }else if (compression == "base64") {
                
                int count_colors = 0;
                for(int y=0; y<current_object->grid->getDimensionY(); ++y){
                    for(int x=0; x<current_object->grid->getDimensionX(); ++x){
                        if(structure->getVoxel(x,y,z) > 0 )
                            count_colors++;
                    }
                }
                
                XMLSize_t size = count_colors;
                std::string input_str = getNodeValueString(cmap_layers->item(z)->getFirstChild());
                XMLByte* data_decoded = xercesc::Base64::decode(reinterpret_cast<const XMLByte*>(input_str.c_str()), &size);
                
                int count = 0;
                for (int d = 0; d < size; ++d) {
                    layer_g[d] = (unsigned int)data_decoded[d];
                }
            }
            
            int dim_x = current_object->grid->getDimensionX();
            int dim_y = current_object->grid->getDimensionY();
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
        }
    }
    
    void FavReader::readColorMap(xercesc_3_1::DOMElement *object_elem, Object* current_object, FavLibrary::Structure* structure){
       
        DOMElement* cmap_elem = dynamic_cast<DOMElement*>( getElements(object_elem, "color_map")->item(0) );
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
            
        }else{
            //TODO: エラー処理
            //color_mode属性はあるが、値が間違っている場合のエラー
            
        }
        
    }

	void FavReader::readObject(xercesc_3_1::DOMNodeList *object_node_) {

        
		int number_of_object = int(object_node_->getLength());
		for (int i=0; i<number_of_object; ++i) {
            

			DOMElement* object_elem = dynamic_cast<DOMElement*>(object_node_->item(i));

			//load attributes
			std::string id   = getAttribute(object_elem, "id"  );
			std::string name = getAttribute(object_elem, "name");
            
            //FIXME: バグ
            // idを引数にして生成すると、write()の際にorigin.getX()でメモリのアクセスエラーが出る。
            // それに加えて、サンプルデータの書き出し後Originの値が変わってしまっている。
			Object* current_object = new Object(name);
//            current_object->setId(1);

            current_object->grid = new Grid();
            readGrid(object_elem, current_object);
            // load Structure
            // TODO: ポインタ問題
            // こっちはポインタ渡しで上の方は違うので、どちらかに統一する?
            Structure* structure = new Structure(current_object->grid);
            current_object->setStructure(structure);

            readVoxelMap(object_elem, current_object, structure);
            readColorMap(object_elem, current_object, structure);
            

            //FIXME: バグ metadataが無い場合にメモリエラー
            // load metadata
//            DOMNodeList* metadata_list = getElements(object_elem, "metadata");
//            if(metadata_list->getLength() == 1){
//            
//                current_object->setMetadataId     (getElementString(dynamic_cast<DOMElement*>(metadata_list->item(0)), "id"   ));
//                current_object->setMetadataTitle  (getElementString(dynamic_cast<DOMElement*>(metadata_list->item(0)), "title"));
//                current_object->setMetadataAuthor (getElementString(dynamic_cast<DOMElement*>(metadata_list->item(0)), "author"));
//                current_object->setMetadataLicense(getElementString(dynamic_cast<DOMElement*>(metadata_list->item(0)), "license"));
//                current_object->setMetadataNote   (getElementString(dynamic_cast<DOMElement*>(metadata_list->item(0)), "note"));
//            
//            }else if(metadata_list->getLength() > 1){
//                //TODO: エラー処理
//            }
            
			fav->addObject(current_object);
		}
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
        DOMNodeList* node_list = getElements(elem, tag_name);
        const XMLCh* node_value = ((node_list->item(0))->getFirstChild())->getNodeValue();
        char* node_value_str = XMLString::transcode(node_value);
        int ret = atoi(node_value_str);
        XMLString::release(&node_value_str);
        return ret;
    }
    
    double FavReader::getElementDouble(DOMElement* elem, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        DOMNodeList* node_list = getElements(elem, tag_name);
        const XMLCh* node_value = ((node_list->item(0))->getFirstChild())->getNodeValue();
        char* node_value_str = XMLString::transcode(node_value);
        double ret = atof(node_value_str);
        XMLString::release(&node_value_str);
        return ret;
    }
    
    std::string FavReader::getElementString(DOMElement* elem, const char *tag_name_)
    {
        char* tag_name = (char *)tag_name_;
        DOMNodeList* node_list = getElements(elem, tag_name);
        std::string ret = "";
        if(node_list->getLength()>0){
            const XMLCh* node_value = ((node_list->item(0))->getFirstChild())->getNodeValue();
            char* node_value_str = XMLString::transcode(node_value);
            ret = std::string(node_value_str);
            XMLString::release(&node_value_str);
        }
        return ret;
    }
    
}