//
//  FavWriter.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/12/05.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#define _CRT_SECURE_NO_WARNINGS

#include "Fav.h"
#include "FavWriter.h"


namespace FavLibrary
{
    FavWriter::FavWriter(Fav* fav_) {
        fav = fav_;
    }
    
    
    bool FavWriter::write(const char* file_path, CompressionMode compression_mode_) {
        compression_mode = compression_mode_;
        return write(file_path);
    }
    
    bool FavWriter::write(const char* file_path) {
        
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
        
        XMLCh* xcore = xercesc::XMLString::transcode("Core");
        xercesc::DOMImplementation *tpImpl = xercesc::DOMImplementationRegistry::getDOMImplementation(xcore);
        xercesc::XMLString::release(&xcore);
        
        XMLCh* xfav = xercesc::XMLString::transcode("fav");
        doc = tpImpl->createDocument(0, xfav, 0);
        xercesc::XMLString::release(&xfav);
        xercesc::DOMElement* fav_elem = doc->getDocumentElement();
        setAttribute(fav_elem, "version", "1.0");
        
        // Add Elements to fav
        writeMetadata(fav_elem);
        writePalette (fav_elem);
        writeVoxel   (fav_elem);
        writeObject  (fav_elem);
        
        bool ret = writeXML(file_path);
        
        doc->release();
        xercesc::XMLPlatformUtils::Terminate();
        
        return ret;
    }

	void FavWriter::writeMetadata(xercesc::DOMElement *parent_elem) {

		xercesc::DOMElement *metadata_elem = createElement("metadata");

        appendCDATA(metadata_elem, "id",      fav->getMetadataId());
		appendCDATA(metadata_elem, "title",   fav->getMetadataTitle());
		appendCDATA(metadata_elem, "author",  fav->getMetadataAuthor());
		appendCDATA(metadata_elem, "license", fav->getMetadataLicense());
        if(fav->getMetadataNote()!="")
            appendCDATA(metadata_elem, "note",    fav->getMetadataNote());

        parent_elem->appendChild(metadata_elem);
	}


	void FavWriter::writePalette(xercesc::DOMElement *parent_elem) {

		xercesc::DOMElement *palette_elem = createElement("palette");

		// write geometry
		int number_of_geometries = fav->palette.getNumberOfGeometries();

		for (int i = 0; i < number_of_geometries; ++i) {

			Geometry current_geometry = fav->palette.getGeometryById(i + 1); //FIXME: ? この+1の処理は必須なんだっけ？
			xercesc::DOMElement *geometry_elem = createElement("geometry");
			
            setAttribute(geometry_elem, "id", std::to_string(current_geometry.getId()));
            if(current_geometry.getName() !="")
                setAttribute(geometry_elem, "name", current_geometry.getName());
            
            if(current_geometry.hasShape()){
                
                switch(current_geometry.getShape()){
                        
                    case GeometryShape::none:
                        appendText(geometry_elem, "shape", "none");
                        break;
                        
                    case GeometryShape::cube:
                        appendText(geometry_elem, "shape", "cube");
                        break;
                        
                    case GeometryShape::sphere:
                        appendText(geometry_elem, "shape", "spehre");
                        break;
                        
                    case GeometryShape::user_defined:
                        appendText(geometry_elem, "shape",     "user_defined"                 );
                        appendText(geometry_elem, "reference", current_geometry.getReference());
                        break;
                }
            }

            if(current_geometry.hasScale()){
                xercesc::DOMElement* scale_elem = createElement("scale");
                appendText(scale_elem, "x", std::to_string(current_geometry.getScaleX()) );
                appendText(scale_elem, "y", std::to_string(current_geometry.getScaleY()) );
                appendText(scale_elem, "z", std::to_string(current_geometry.getScaleZ()) );
                geometry_elem->appendChild(scale_elem);
            }
			palette_elem->appendChild(geometry_elem);
		}

		// write material
		int number_of_materials = fav->palette.getNumberOfMaterials();
		for (int i = 0; i < number_of_materials; ++i) {
            
            //TODO FAV 1.1では matrial idは0からふるので以下の文は id = iにする  
            int id = i + 1;
			Material current_material = fav->palette.getMaterialById(id);
			xercesc::DOMElement *mat_elem = createElement("material");

            setAttribute(mat_elem, "id", std::to_string(id));
            if(current_material.getName() !="")
                setAttribute(mat_elem, "name", current_material.getName());

            // write material
			for (auto material : current_material.materials) {
				
                // write product_info
                if (material->materialType == MaterialType::product_info) {
					ProductInfo* product_info = dynamic_cast<ProductInfo*>(material.get());
					xercesc::DOMElement* pinfo_elem = createElement("product_info");
                    
                    if(product_info->getManufacturer() != "")
                        appendCDATA(pinfo_elem, "manufacturer", product_info->getManufacturer());
                    
                    if(product_info->getProductName() != "")
                        appendCDATA(pinfo_elem, "product_name", product_info->getProductName());
                    
                    if(product_info->getUrl() != "")
                        appendCDATA(pinfo_elem, "url", product_info->getUrl());
                    
					mat_elem->appendChild(pinfo_elem);
				}
                // write iso_standard
				else if (material->materialType == MaterialType::iso_standard) {
                    IsoStandard* iso_standard = dynamic_cast<IsoStandard*>(material.get());
					xercesc::DOMElement* iso_elem = createElement("iso_standard");
					
                    if(iso_standard->getIsoId() != "")
                        appendCDATA(iso_elem, "iso_id",   iso_standard->getIsoId());
                    
                    if(iso_standard->getIsoName() != "")
                        appendCDATA(iso_elem, "iso_name", iso_standard->getIsoName());
					
                    mat_elem->appendChild(iso_elem);
				}
                // write material_name
				else if (material->materialType == MaterialType::material_name) {
                    MaterialName* material_name = dynamic_cast<MaterialName*>(material.get());
                    
                    if(material_name->getMaterialName() != "")
                        appendCDATA(mat_elem, "material_name", material_name->getMaterialName());
				}
			}
			palette_elem->appendChild(mat_elem);
		}
		parent_elem->appendChild(palette_elem);
	}

	void FavWriter::writeVoxel(xercesc::DOMElement *parent_elem) {

        int number_of_voxels = fav->getNumVoxels();
		for (int i = 0; i < number_of_voxels; ++i) {
            
            Voxel current_voxel  = fav->getVoxel(i + 1);
			xercesc::DOMElement*  vox_elem = createElement("voxel");
			setAttribute(vox_elem, "id",   std::to_string(current_voxel.getId()));
			if(current_voxel.getName() != "")
                setAttribute(vox_elem, "name", current_voxel.getName());
			
            xercesc::DOMElement* geo_elem = createElement("geometry_info");
			appendText( geo_elem, "id", std::to_string(current_voxel.getGeometryInfo().getId()));
			vox_elem->appendChild(geo_elem);

			for (int j = 0, size = current_voxel.getNumMaterialInfo(); j < size; ++j) {
				xercesc::DOMElement *matinfo_elem = createElement("material_info");
				appendText(matinfo_elem, "id",    std::to_string(current_voxel.getMaterialInfo(j).getId())   );
                
				appendText(matinfo_elem, "ratio", std::to_string(current_voxel.getMaterialInfo(j).getRatio()));
				vox_elem->appendChild(matinfo_elem);
			}
			parent_elem->appendChild(vox_elem);
		}
	}

	void FavWriter::writeGrid(xercesc::DOMElement* parent_elem, Grid* grid) {

		xercesc::DOMElement *grid_elem  = createElement("grid");
        
		xercesc::DOMElement *origin_elem = createElement("origin");
		appendText(origin_elem, "x", std::to_string(grid->getOriginX()));
		appendText(origin_elem, "y", std::to_string(grid->getOriginY()));
		appendText(origin_elem, "z", std::to_string(grid->getOriginZ()));
		grid_elem->appendChild(origin_elem);

		xercesc::DOMElement *unit_elem = createElement("unit");
		appendText(unit_elem, "x", std::to_string(grid->getUnitX()));
		appendText(unit_elem, "y", std::to_string(grid->getUnitY()));
		appendText(unit_elem, "z", std::to_string(grid->getUnitZ()));
		grid_elem->appendChild(unit_elem);

		xercesc::DOMElement *dim_elem = createElement("dimension");
		appendText(dim_elem, "x", std::to_string(grid->getDimensionX()));
		appendText(dim_elem, "y", std::to_string(grid->getDimensionY()));
		appendText(dim_elem, "z", std::to_string(grid->getDimensionZ()));
		grid_elem->appendChild(dim_elem);

		parent_elem->appendChild(grid_elem);
	}

	void FavWriter::writeVoxelMap(xercesc::DOMElement* parent_elem, Structure* p_structure) {

		// TODO: Zlib compression is under development
        const char* compression;
        
        switch(compression_mode){
                
            case CompressionMode::none:
                compression = "none";
                break;
                
            case CompressionMode::base64:
                compression = "base64";

                break;
                
            case CompressionMode::zlib:
                compression = "zlib";

                break;

			default:
				compression = "none";
				break;
        }
        
		xercesc::DOMElement *vmap_elem = createElement("voxel_map");
		setAttribute(vmap_elem, "compression",   std::string(compression));
		setAttribute(vmap_elem, "bit_per_voxel", std::to_string((int)p_structure->getBitPerVoxel()));

		std::string layer_data;
		for (int z = 0, size = p_structure->getDimensionZ(); z < size; ++z) {
			
            layer_data.clear();
			
            for (int y = 0, size = p_structure->getDimensionY(); y < size; ++y) {
				for (int x = 0, size = p_structure->getDimensionX(); x < size; ++x) {
					
                    int data = p_structure->getVoxel(x, y, z);

                    if (p_structure->getBitPerVoxel() == BitPerVoxel::Bit4) {
						layer_data += std::to_string(data);
					}
                    
					else if (p_structure->getBitPerVoxel() == BitPerVoxel::Bit8) {
						char buff[3];
						sprintf(buff, "%02x", data);
						layer_data.push_back(buff[0]);
						layer_data.push_back(buff[1]);

					}
                    
					else if (p_structure->getBitPerVoxel() == BitPerVoxel::Bit16) {
						char buff[5];
						sprintf(buff, "%04x", data);
						layer_data.push_back(buff[0]);
						layer_data.push_back(buff[1]);
						layer_data.push_back(buff[2]);
						layer_data.push_back(buff[3]);
					}
                    
					else {
						// TODO: bit_per_voxelを決める関数を実装
					}
				}
			}

            switch(compression_mode){
                case CompressionMode::none:
                    
                    appendCDATA(vmap_elem, "layer", layer_data);

                    break;
                    
                case CompressionMode::base64:
                {
                    int size = p_structure->getDimensionX() * p_structure->getDimensionY();
					if(size != 0){
						unsigned char* data = new unsigned char[size];
						for(int i=0; i<size; ++i) data[i] = 0;

						BytesFromHexString(data, layer_data.c_str());
                    
						XMLSize_t len;
						XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    
						// TODO: check later. 何故かnew lineが入ってしまうのでここで除去している。
						std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
						deleteNewLine(input_str);
						XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
						appendCDATA(vmap_elem, "layer", text_encoded);
						xercesc::XMLString::release(&text_encoded);
						xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data_encoded);
                    
						delete[] data;
						data = nullptr;
					}else{
						appendCDATA(vmap_elem, "layer", "");
					}
                    
                    break;
                }
                case CompressionMode::zlib:
                    //TODO: zlib compression
                    break;
            }
		}
        
		parent_elem->appendChild(vmap_elem);
        
	}

    void FavWriter::writeColorMapRGB(xercesc::DOMElement *cmap_elem, Structure* p_structure){
                
        std::string layer_data;
        
        //FIXME: Without following useless codes(5 lines), push_back() is not functioned here....
        int data = 0;
        char buff[3];
        sprintf(buff, "%02x", data);
        layer_data.push_back(buff[0]);
        layer_data.push_back(buff[1]);
        
        for (int z = 0, size = p_structure->getDimensionZ(); z < size; ++z) {
            
            layer_data.clear();
            int count_colors = 0;
            
            for (int y = 0, size = p_structure->getDimensionY(); y < size; ++y) {
                for (int x = 0, size = p_structure->getDimensionX(); x < size; ++x) {
                    
                    int voxel_state = p_structure->getVoxel(x,y,z);
                    
                    if(voxel_state > 0){
                    
                        char buff[3];
                        sprintf(buff, "%02x", p_structure->getColorRed(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );

                        sprintf(buff, "%02x", p_structure->getColorGreen(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorBlue(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        count_colors++;
                    }
                }
            }
            
            switch(compression_mode){
                    
                    
                case CompressionMode::zlib:
                    //TODO: zlib complession have not been implemented yet.
                    break;
                    
                case CompressionMode::none:
                    
                    appendCDATA(cmap_elem, "layer", layer_data);
                    
                    break;
                    
                case CompressionMode::base64:

                    int size = count_colors*3;
					if(size != 0){
						unsigned char* data = new unsigned char[size];
						for(int i=0; i<size; ++i) data[i] = 0;
                    
						BytesFromHexString(data, layer_data.c_str());
                    
						XMLSize_t len;
						XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    
						// FIXME: check later. 何故かnew lineが入ってしまうのでここで除去している。
						std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
						deleteNewLine(input_str);
						XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
						appendCDATA(cmap_elem, "layer", text_encoded);
                    
						xercesc::XMLString::release(&text_encoded);
						xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data_encoded);

						delete[] data;
						data = nullptr;
					}else{
						appendCDATA(cmap_elem, "layer", "");
					}
                    
                    break;

            }
            
        }
    }
    
    void FavWriter::writeColorMapRGBA(xercesc::DOMElement *cmap_elem, Structure* p_structure){
        
        std::string layer_data;
        for (int z = 0, size = p_structure->getDimensionZ(); z < size; ++z) {
            
            layer_data.clear();
            int count_colors = 0;
            for (int y = 0, size = p_structure->getDimensionY(); y < size; ++y) {
                for (int x = 0, size = p_structure->getDimensionX(); x < size; ++x) {
                    
                    int voxel_state = p_structure->getVoxel(x,y,z);
                    
                    if(voxel_state != 0){
                        
                        char buff[3];
                        sprintf(buff, "%02x", p_structure->getColorRed(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorGreen(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorBlue(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorAlpha(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        count_colors++;
                    }
                    
                }
            }
            
            switch(compression_mode){
                    
                case CompressionMode::zlib:
                    //TODO: zlib complession have not been implemented yet.
                    break;
                    
                case CompressionMode::none:
                    
                    appendCDATA(cmap_elem, "layer", layer_data);
                    
                    break;
                    
                case CompressionMode::base64:
                    
                    int size = count_colors*4;
					if(size != 0){
						unsigned char* data = new unsigned char[size];
						for(int i=0; i<size; ++i) data[i] = 0;
                    
						BytesFromHexString(data, layer_data.c_str());
                    
						XMLSize_t len;
						XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    
						// FIXME: check later. 何故かnew lineが入ってしまうのでここで除去している。
						std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
						deleteNewLine(input_str);
						XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
						appendCDATA(cmap_elem, "layer", text_encoded);
                    
						xercesc::XMLString::release(&text_encoded);
						xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data_encoded);

						delete[] data;
						data = nullptr;
					}else{
						appendCDATA(cmap_elem, "layer", "");
					}
                    
                    break;
            }
            
        }
    }
    
    void FavWriter::writeColorMapCMYK(xercesc::DOMElement *cmap_elem, Structure* p_structure){
        
        std::string layer_data;
        for (int z = 0, size = p_structure->getDimensionZ(); z < size; ++z) {
            
            layer_data.clear();
            int count_colors = 0;
            for (int y = 0, size = p_structure->getDimensionY(); y < size; ++y) {
                for (int x = 0, size = p_structure->getDimensionX(); x < size; ++x) {
                    
                    int voxel_state = p_structure->getVoxel(x,y,z);
                    
                    if(voxel_state != 0){
                        
                        char buff[3];
                        sprintf(buff, "%02x", p_structure->getColorCyan(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorMagenta(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorYellow(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        
                        sprintf(buff, "%02x", p_structure->getColorKeyPlate(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        count_colors++;
                    }
                    
                }
            }
            
            switch(compression_mode){
                    
                case CompressionMode::zlib:
                    //TODO: zlib complession have not been implemented yet.
                    break;
                    
                case CompressionMode::none:
                    
                    appendCDATA(cmap_elem, "layer", layer_data);
                    
                    break;
                    
                case CompressionMode::base64:
                    
                    int size = count_colors*4;
					if(size != 0){
						unsigned char* data = new unsigned char[size];
						for(int i=0; i<size; ++i) data[i] = 0;
                    
						BytesFromHexString(data, layer_data.c_str());
                    
						XMLSize_t len;
						XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    
						// FIXME: check later. 何故かnew lineが入ってしまうのでここで除去している。
						std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
						deleteNewLine(input_str);
						XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
						appendCDATA(cmap_elem, "layer", text_encoded);
                    
						xercesc::XMLString::release(&text_encoded);
						xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data_encoded);

						delete[] data;
						data = nullptr;
					}else{
						appendCDATA(cmap_elem, "layer", "");
					}
                    
                    break;
            }
            
        }
    }
    
    void FavWriter::writeColorMapGrayScale(xercesc::DOMElement *cmap_elem, Structure* p_structure){
        
        std::string layer_data;
        for (int z = 0, size = p_structure->getDimensionZ(); z < size; ++z) {
            
            layer_data.clear();
            int count_colors = 0;
            for (int y = 0, size = p_structure->getDimensionY(); y < size; ++y) {
                for (int x = 0, size = p_structure->getDimensionX(); x < size; ++x) {
                    
                    int voxel_state = p_structure->getVoxel(x,y,z);
                    
                    if(voxel_state != 0){
                        
                        char buff[3];
                        sprintf(buff, "%02x", p_structure->getColorGrayScale(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        count_colors++;
                    }
                    
                }
            }
            
            switch(compression_mode){
                    
                case CompressionMode::zlib:
                    //TODO: zlib complession have not been implemented yet.
                    break;
                    
                case CompressionMode::none:
                    
                    appendCDATA(cmap_elem, "layer", layer_data);
                    
                    break;
                    
                case CompressionMode::base64:
                    
                    int size = count_colors;
					if(size != 0){
						unsigned char* data = new unsigned char[size];
						for(int i=0; i<size; ++i) data[i] = 0;

						BytesFromHexString(data, layer_data.c_str());
                    
						XMLSize_t len;
						XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    
						// FIXME: check later. 何故かnew lineが入ってしまうのでここで除去している。
						std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
						deleteNewLine(input_str);
						XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
						appendCDATA(cmap_elem, "layer", text_encoded);
                    
						xercesc::XMLString::release(&text_encoded);
						xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data_encoded);

						delete[] data;
						data = nullptr;
					}else{
						appendCDATA(cmap_elem, "layer", "");
					}
                    
                    break;
            }
            
        }
    }
    
    void FavWriter::writeColorMapGrayScale16(xercesc::DOMElement *cmap_elem, Structure* p_structure){
        
        std::string layer_data;
        for (int z = 0, size = p_structure->getDimensionZ(); z < size; ++z) {
            
            layer_data.clear();
            int count_colors = 0;
            for (int y = 0, size = p_structure->getDimensionY(); y < size; ++y) {
                for (int x = 0, size = p_structure->getDimensionX(); x < size; ++x) {
                    
                    int voxel_state = p_structure->getVoxel(x,y,z);
                    
                    if(voxel_state != 0){
                        
                        char buff[5];
                        sprintf(buff, "%04x", p_structure->getColorGrayScale16(x, y, z));
                        layer_data.push_back( buff[0] );
                        layer_data.push_back( buff[1] );
                        layer_data.push_back( buff[2] );
                        layer_data.push_back( buff[3] );
                        count_colors++;
                    }
                    
                }
            }
            
            switch(compression_mode){
                    
                case CompressionMode::zlib:
                    //TODO: zlib complession have not been implemented yet.
                    break;
                    
                case CompressionMode::none:
                    
                    appendCDATA(cmap_elem, "layer", layer_data);
                    
                    break;
                    
                case CompressionMode::base64:
                    
                    int size = count_colors;
					if(size != 0){
						unsigned char* data = new unsigned char[size];
						for(int i=0; i<size; ++i) data[i] = 0;

						BytesFromHexString(data, layer_data.c_str());
                    
						XMLSize_t len;
						XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    
						// FIXME: check later. 何故かnew lineが入ってしまうのでここで除去している。
						std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
						deleteNewLine(input_str);
						XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
						appendCDATA(cmap_elem, "layer", text_encoded);
                    
						xercesc::XMLString::release(&text_encoded);
						xercesc::XMLPlatformUtils::fgMemoryManager->deallocate(data_encoded);

						delete[] data;
						data = nullptr;
					}else{
						appendCDATA(cmap_elem, "layer", "");
					}
                    
                    break;
            }
        }
    }
    
	void FavWriter::writeColorMap(xercesc::DOMElement* parent_elem, Structure* p_structure) {
        
        xercesc::DOMElement *cmap_elem = createElement("color_map");
        
        std::string compression;
        switch(compression_mode){
                
            case CompressionMode::none:
                compression = "none";
                break;
                
            case CompressionMode::base64:
                compression = "base64";
                
                break;
                
            case CompressionMode::zlib:
                compression = "zlib";
                
                break;
        }
        setAttribute(cmap_elem, "compression", compression);

        std::string color_mode;
        switch(p_structure->getColorMode()){
                
            case FavLibrary::ColorMode::RGB:
                color_mode = "RGB";
                setAttribute(cmap_elem, "color_mode",  color_mode );
                writeColorMapRGB(cmap_elem, p_structure);
                break;
                
            case FavLibrary::ColorMode::RGBA:
                color_mode = "RGBA";
                setAttribute(cmap_elem, "color_mode",  color_mode );
                writeColorMapRGBA(cmap_elem, p_structure);

                break;
                
            case FavLibrary::ColorMode::CMYK:
                color_mode = "CMYK";
                setAttribute(cmap_elem, "color_mode",  color_mode );
                writeColorMapCMYK(cmap_elem, p_structure);

                break;
                
            case FavLibrary::ColorMode::Grayscale:
                color_mode = "GrayScale";
                setAttribute(cmap_elem, "color_mode",  color_mode );
                writeColorMapGrayScale(cmap_elem, p_structure);

                break;
                
            case FavLibrary::ColorMode::Grayscale16:
                color_mode = "GrayScale16";
                setAttribute(cmap_elem, "color_mode",  color_mode );
                writeColorMapGrayScale16(cmap_elem, p_structure);

                break;
        }
        
        parent_elem->appendChild(cmap_elem);
	}

	void FavWriter::writeStructure(xercesc::DOMElement* parent_elem, Structure* p_structure) {
		
        // waiting for structure class
		xercesc::DOMElement *structure_elem = createElement("structure");

		writeVoxelMap(structure_elem, p_structure);
		writeColorMap(structure_elem, p_structure);

		parent_elem->appendChild(structure_elem);
	}


	void FavWriter::writeObject(xercesc::DOMElement* parent_elem) {
        
        std::map<unsigned int, Object> objects = fav->getObjects();
        for(std::map<unsigned int, Object>::iterator it = objects.begin(); it != objects.end();){

            Object* current_object = &it->second;
            xercesc::DOMElement  *obj_elem = createElement("object");
            setAttribute(obj_elem, "id",   std::to_string(current_object->getId()));
            setAttribute(obj_elem, "name", current_object->getName());
            
            xercesc::DOMElement *metadata_elem = createElement("metadata");
            appendCDATA(metadata_elem, "id",      current_object->getMetadataId());
            appendCDATA(metadata_elem, "title",   current_object->getMetadataTitle());
            appendCDATA(metadata_elem, "author",  current_object->getMetadataAuthor());
            appendCDATA(metadata_elem, "license", current_object->getMetadataLicense());
            if(current_object->getMetadataNote()!="")
                appendCDATA(metadata_elem, "note",    current_object->getMetadataNote());
            
            obj_elem->appendChild(metadata_elem);
            
            writeGrid(obj_elem, &current_object->grid);
            writeStructure(obj_elem, &current_object->structure);
            
            parent_elem->appendChild(obj_elem);
            
            it++;
        }
	}

	bool FavWriter::writeXML(const char *filePath) {
        
		// set LS (Load/Save)
		//        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(L"LS");
		xercesc::DOMImplementation *implementation = xercesc::DOMImplementation::getImplementation();
		xercesc::DOMLSSerializer *serializer = ((xercesc::DOMImplementationLS*)implementation)->createLSSerializer();
		if (serializer->getDomConfig()->canSetParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true)) {
			serializer->getDomConfig()->setParameter(xercesc::XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}
        
        XMLCh* xnewline = xercesc::XMLString::transcode("\r\n");
		serializer->setNewLine(xnewline);
        xercesc::XMLString::release(&xnewline);
        
		// Change filepath to XMLCh type.
		XMLCh *xFilePath = xercesc::XMLString::transcode(filePath);

		// Create target file.
        xercesc::XMLFormatTarget *formatTarget;
        try{
            formatTarget = new xercesc::LocalFileFormatTarget(xFilePath);
        }catch(...){
            std::cerr << "Error: No such directry found." << std::endl;
            return 0;
        }
        
        xercesc::XMLString::release(&xFilePath);

		xercesc::DOMLSOutput *output = ((xercesc::DOMImplementationLS*)implementation)->createLSOutput();
		output->setByteStream(formatTarget);

		// Write
		serializer->write(doc, output);

		// Release
		serializer->release();
		delete formatTarget;
		output->release();
        
        return 1;
	};
    
    
    void FavWriter::str2bin(const unsigned char *str, unsigned char *hex, int len)
    {
        int i = 0;
        for (i = 0; i < (len >> 1); i++) {
            unsigned int tmp;
            sscanf((const char*)str + (i << 1), "%2x", &tmp);
            hex[i] = (unsigned char)tmp & 0xff;
        }
    }
    
    void FavWriter::BytesFromHexString(unsigned char *data, const char *string) {
//        printf("string:%s\n", string);
        int len = (int)strlen(string);
        for (int i = 0; i < len; i += 2) {
            unsigned int x;
            sscanf((char *)(string + i), "%02x", &x);
            data[i / 2] = x;
        }
    }
    
    void FavWriter::deleteNewLine(std::string &targetStr)
    {
        const char CR = '\r';
        const char LF = '\n';
        std::string destStr;
        for (const auto c : targetStr) {
            if (c != CR && c != LF) {
                destStr += c;
            }
        }
        targetStr = std::move(destStr);
    }
    
    xercesc::DOMElement* FavWriter::createElement(const char *name_){
        XMLCh* xname  = xercesc::XMLString::transcode(name_);
        xercesc::DOMElement* ret_elem = doc->createElement(xname);
        xercesc::XMLString::release(&xname);
        return ret_elem;
    };
    
    void FavWriter::appendCDATA(xercesc::DOMElement* parent_elem, const char* child_elem_name, XMLCh* text) {

        xercesc::DOMElement *child_elem = createElement(child_elem_name);
        xercesc::DOMCDATASection *text_elem = doc->createCDATASection(text);
        child_elem->appendChild(text_elem);
        parent_elem->appendChild(child_elem);

    };
    
    void FavWriter::appendCDATA(xercesc::DOMElement* parent_elem, const char* child_elem_name, const char* text) {
        
        XMLCh* xname  = xercesc::XMLString::transcode(child_elem_name);
        XMLCh* xtext  = xercesc::XMLString::transcode(text);

        xercesc::DOMElement *child_elem = doc->createElement(xname);
        xercesc::DOMCDATASection *text_elem = doc->createCDATASection(xtext);
        child_elem->appendChild(text_elem);
        parent_elem->appendChild(child_elem);
        
        xercesc::XMLString::release(&xname);
        xercesc::XMLString::release(&xtext);
    };
    
    void FavWriter::appendCDATA(xercesc::DOMElement* parent_elem, const char* child_elem_name, std::string text) {
        appendCDATA(parent_elem, child_elem_name, text.c_str());
    };
    
    
    void FavWriter::appendText(xercesc::DOMElement* parent_elem, const char* child_elem_name, const char* text) {
        XMLCh* xname  = xercesc::XMLString::transcode(child_elem_name);
        XMLCh* xtext  = xercesc::XMLString::transcode(text);

        xercesc::DOMElement *child_elem = doc->createElement(xname);
        xercesc::DOMText *text_elem = doc->createTextNode(xtext);
        child_elem->appendChild(text_elem);
        parent_elem->appendChild(child_elem);
        
        xercesc::XMLString::release(&xname);
        xercesc::XMLString::release(&xtext);
    };
    
    void FavWriter::appendText(xercesc::DOMElement* parent_elem, const char* child_elem_name, std::string text) {
        appendText(parent_elem, child_elem_name, text.c_str());
    };
    
    void FavWriter::setAttribute(xercesc::DOMElement *elem, const char* attr_name, const char* attr_value) {
        XMLCh* name  = xercesc::XMLString::transcode(attr_name);
        XMLCh* value = xercesc::XMLString::transcode(attr_value);
        
        elem->setAttribute(name, value);
        
        xercesc::XMLString::release(&name);
        xercesc::XMLString::release(&value);
    };
    
    void FavWriter::setAttribute(xercesc::DOMElement *elem, const char* attr_name, std::string attr_value) {
        setAttribute(elem, attr_name, attr_value.c_str());
    };
    
}
