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
#include <xercesc/util/Base64.hpp>

using namespace xercesc;

namespace FavLibrary
{
    FavWriter::FavWriter(Fav* fav_) {
        fav = fav_;
    }
    
    bool FavWriter::write(const char* file_path) {
        
        //TODO: write later
        // エラー処理
        XMLPlatformUtils::Initialize();
        
        DOMImplementation *tpImpl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));
        
        doc = tpImpl->createDocument(0, XMLString::transcode("fav"), 0);
        DOMElement* fav_elem = doc->getDocumentElement();
        setAttribute(fav_elem, "version", "1.0");
        
        // Add Elements to fav
        writeMetadata(fav_elem);
        writePalette (fav_elem);
        writeVoxel   (fav_elem);
        writeObject  (fav_elem);
        
        writeXML(file_path);
        
        // TODO: write later
        // ここもエラー処理か？
        doc->release();
        XMLPlatformUtils::Terminate();
        
        return 0;
    }

	void FavWriter::writeMetadata(DOMElement *parent_elem) {

		DOMElement *metadata_elem = doc->createElement(XMLString::transcode("metadata"));

        appendCDATA(metadata_elem, "id",      fav->getMetadataId());
		appendCDATA(metadata_elem, "title",   fav->getMetadataTitle());
		appendCDATA(metadata_elem, "author",  fav->getMetadataAuthor());
		appendCDATA(metadata_elem, "license", fav->getMetadataLicense());
        // FIXME: revise later
        // ノートが存在しなかった場合の処理 (上記は必須項目)
        appendCDATA(metadata_elem, "note",    fav->getMetadataNote());

        parent_elem->appendChild(metadata_elem);
	}


	void FavWriter::writePalette(DOMElement *parent_elem) {

		DOMElement *palette_elem = doc->createElement(XMLString::transcode("palette"));

		// write geometry
		int number_of_geometries = fav->palette.getNumberOfGeometries();

		for (int i = 0; i < number_of_geometries; ++i) {

			Geometry current_geometry = fav->palette.getGeometryById(i + 1); //FIXME: ? この+1の処理は必須なんだっけ？
			DOMElement *geometry_elem = doc->createElement(XMLString::transcode("geometry"));

			setAttribute(geometry_elem, "id", std::to_string(current_geometry.getId()));

			// TODO: write later
            // nameは必須項目ではない。
            // FIXME: なぜかnameが元ファイルと異なる、、なんで？
			setAttribute(geometry_elem, "name", current_geometry.getName());

            
            switch(current_geometry.getShape()){
                case GeometryShape::cube:
                    appendText(geometry_elem, "shape", "cube");
                    break;
                    
                case GeometryShape::sphere:
                    appendText(geometry_elem, "shape", "spehre");
                    break;
                    
                case GeometryShape::user_defined:
                    // TODO: write later. under development : add reference path
                    appendText(geometry_elem, "shape", "user_defined");
                    break;
            }

			DOMElement* scale_elem = doc->createElement(XMLString::transcode("scale"));
			appendText(scale_elem, "x", std::to_string(current_geometry.getScaleX()) );
			appendText(scale_elem, "y", std::to_string(current_geometry.getScaleY()) );
			appendText(scale_elem, "z", std::to_string(current_geometry.getScaleZ()) );
            
			geometry_elem->appendChild(scale_elem);
			palette_elem->appendChild(geometry_elem);
		}


		// write material
		int number_of_materials = fav->palette.getNumberOfMaterials();

		for (int i = 0; i < number_of_materials; ++i) {

            int id = i + 1;
			Material current_material = fav->palette.getMaterialById(id);
			DOMElement *mat_elem = doc->createElement(XMLString::transcode("material"));

            setAttribute(mat_elem, "id", std::to_string(id));
			// if(tmp->has_name){
			setAttribute(mat_elem, "name", current_material.getName());

            // FIXME: 優先順位の問題
			// 優先順位問題をmaterialクラスの構造で解決する必要がある
            // 必須じゃない項目の処理を追加
			for (auto material : current_material.materials) {
				
                if (material->materialType == MaterialType::product_info) {
					ProductInfo* pinfo = dynamic_cast<ProductInfo*>(material);
					DOMElement* pinfo_elem = doc->createElement(XMLString::transcode("product_info"));
					appendCDATA(pinfo_elem, "manufacturer", pinfo->getManufacturer());
					appendCDATA(pinfo_elem, "product_name", pinfo->getProductName());
					appendCDATA(pinfo_elem, "url",          pinfo->getUrl());
					mat_elem->appendChild(pinfo_elem);
				}
                
				else if (material->materialType == MaterialType::iso_standard) {
                    IsoStandard* iso = dynamic_cast<IsoStandard*>(material);
					DOMElement* iso_elem = doc->createElement(XMLString::transcode("iso_standard"));
					appendCDATA(iso_elem, "iso_id",   iso->getIsoId());
					appendCDATA(iso_elem, "iso_name", iso->getIsoName());
					mat_elem->appendChild(iso_elem);
				}

				else if (material->materialType == MaterialType::material_name) {
                    MaterialName* material_name = dynamic_cast<MaterialName*>(material);
					DOMElement* name_elem = doc->createElement(XMLString::transcode("material_name"));
					appendCDATA(name_elem, "material_name", material_name->getMaterialName());
					mat_elem->appendChild(name_elem);
				}
			}
			palette_elem->appendChild(mat_elem);
		}
		parent_elem->appendChild(palette_elem);
	}

	void FavWriter::writeVoxel(DOMElement *parent_elem) {

        int number_of_voxels = fav->getNumVoxels();
		for (int i = 0; i < number_of_voxels; ++i) {
            
            Voxel current_voxel  = fav->getVoxel(i + 1);
			DOMElement*  vox_elem = doc->createElement(XMLString::transcode("voxel"));
			setAttribute(vox_elem, "id",   std::to_string(current_voxel.getId()));
			setAttribute(vox_elem, "name", current_voxel.getName());
			
            DOMElement* geo_elem = doc->createElement(XMLString::transcode("geometry_info"));
			appendText( geo_elem, "id", std::to_string(current_voxel.getGeometryInfo()));
			vox_elem->appendChild(geo_elem);

			for (int j = 0, size = current_voxel.getNumMaterialInfo(); j < size; ++j) {
				DOMElement *matinfo_elem = doc->createElement(XMLString::transcode("material_info"));
				appendText(matinfo_elem, "id",    std::to_string(current_voxel.getMaterialInfo(j).getId())   );
				appendText(matinfo_elem, "ratio", std::to_string(current_voxel.getMaterialInfo(j).getRatio()));
				vox_elem->appendChild(matinfo_elem);
			}
			parent_elem->appendChild(vox_elem);
		}
	};

	void FavWriter::writeGrid(DOMElement* parent_elem, Grid* grid) {

		DOMElement *grid_elem  = doc->createElement(XMLString::transcode("grid"));
        
        // FIXME: 必須じゃない項目の処理
		DOMElement *origin_elem = doc->createElement(XMLString::transcode("origin"));
		appendText(origin_elem, "x", std::to_string(grid->getOriginX()));
		appendText(origin_elem, "y", std::to_string(grid->getOriginY()));
		appendText(origin_elem, "z", std::to_string(grid->getOriginZ()));
		grid_elem->appendChild(origin_elem);

		DOMElement *unit_elem = doc->createElement(XMLString::transcode("unit"));
		appendText(unit_elem, "x", std::to_string(grid->getUnitX()));
		appendText(unit_elem, "y", std::to_string(grid->getUnitY()));
		appendText(unit_elem, "z", std::to_string(grid->getUnitZ()));
		grid_elem->appendChild(unit_elem);

		DOMElement *dim_elem = doc->createElement(XMLString::transcode("dimension"));
		appendText(dim_elem, "x", std::to_string(grid->getDimensionX()));
		appendText(dim_elem, "y", std::to_string(grid->getDimensionY()));
		appendText(dim_elem, "z", std::to_string(grid->getDimensionZ()));
		grid_elem->appendChild(dim_elem);

		parent_elem->appendChild(grid_elem);
	}

	void FavWriter::writeVoxelMap(DOMElement* parent_elem, Structure* p_structure) {

		// voxel_map
		// TODO: compression mode is under development
        //
        
        CompressionMode compression_test = CompressionMode::none;
        const char* compression;
        
        switch(compression_test){
                
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
        
		DOMElement *vmap_elem = doc->createElement(XMLString::transcode("voxel_map"));
		setAttribute(vmap_elem, "compression",   std::string(compression));
		setAttribute(vmap_elem, "bit_per_voxel", std::to_string(p_structure->getBitPerVoxel()));

		std::string layer_data;
		for (int z = 0, size = p_structure->grid->getDimensionZ(); z < size; ++z) {
			
            layer_data.clear();
			
            for (int y = 0, size = p_structure->grid->getDimensionY(); y < size; ++y) {
				for (int x = 0, size = p_structure->grid->getDimensionX(); x < size; ++x) {
					
                    int data = p_structure->getVoxel(x, y, z);

					if (p_structure->getBitPerVoxel() == 4) {
						layer_data += std::to_string(data);
					}
                    
					else if (p_structure->getBitPerVoxel() == 8) {
						char buff[2];
						sprintf(buff, "%02x", data);
						layer_data.push_back(buff[0]);
						layer_data.push_back(buff[1]);

					}
                    
					else if (p_structure->getBitPerVoxel() == 16) {
						char buff[4];
						sprintf(buff, "%04x", data);
						layer_data.push_back(buff[0]);
						layer_data.push_back(buff[1]);
						layer_data.push_back(buff[2]);
						layer_data.push_back(buff[3]);
					}
                    
					else {
						// TODO: エラー処理 (ただ、この辺はschemaのvaridationで全部省略できるのかな？)
					}
				}
			}

            switch(compression_test){
                case CompressionMode::none:
                    
                    appendCDATA(vmap_elem, "layer", layer_data);

                    break;
                    
                case CompressionMode::base64:
                {
                    int size = p_structure->grid->getDimensionX() * p_structure->grid->getDimensionY();
                    unsigned char* data = new unsigned char[size];
                    BytesFromHexString(data, layer_data.c_str());
                    
                    
                    
                    XMLSize_t len;
                    //            XMLByte* testt = reinterpret_cast<XMLByte*>("");
                    XMLByte* data_encoded = xercesc::Base64::encode(reinterpret_cast<const XMLByte*>(data), size, &len);
                    //            XMLByte* data_decoded = xercesc::Base64::decode( data_encoded, &len );
                    //            for(int dd=0; dd<size; dd++){
                    //                std::cout << (int)data_decoded[dd] << ",";
                    //            }
                    // debug is needed? 何故かnew lineが入ってしまうのでここで除去している。
                    std::string input_str = std::string(reinterpret_cast<char*>(data_encoded));
                    deleteNewLine(input_str);
                    XMLCh* text_encoded = xercesc::XMLString::transcode(input_str.c_str());
                    appendCDATA(vmap_elem, "layer", text_encoded);
                    
                    break;
                }
                case CompressionMode::zlib:
                    //TODO: zlib compression
                    break;
            }
		}
        
		parent_elem->appendChild(vmap_elem);
	}

	void FavWriter::writeColorMap(DOMElement* parent_elem, Structure* p_str) {

        // TODO: writeColorMap の実装はwriteVoxelMapができてからそれに準じてやる
		//
		//    // color_map
		//    DOMElement *cmap_elem = doc->createElement(XMLString::transcode("color_map"));
		//    setAttribute(cmap_elem, "color_mode", std::to_string( p_str->getColorMode() ));
		//
		//    for(int i=0, size=p_str->grid->getDimensionZ(); size<i; ++i){
		//        appendCDATA(cmap_elem, "layer", layer_data);
		//    }
		//    parent_elem->appendChild(cmap_elem);

	}

	void FavWriter::writeStructure(DOMElement* parent_elem, Structure* p_structure) {
		
        // waiting for structure class
		DOMElement *structure_elem = doc->createElement(XMLString::transcode("structure"));

		writeVoxelMap(structure_elem, p_structure);
		writeColorMap(structure_elem, p_structure);

		parent_elem->appendChild(structure_elem);
	}


	void FavWriter::writeObject(DOMElement* parent_elem) {

		for (int i = 0, size = fav->getNumObjects(); i < size; ++i) {
			
            Object current_object = fav->getObject(i);
			DOMElement  *obj_elem = doc->createElement(XMLString::transcode("object"));
            setAttribute(obj_elem, "id",   std::to_string(current_object.getId()));
            setAttribute(obj_elem, "name", current_object.getName());
			
            writeGrid(obj_elem, current_object.grid);
			writeStructure(obj_elem, current_object.structure);
			parent_elem->appendChild(obj_elem);
		}

	}

	void FavWriter::writeXML(const char *filePath) {
        // TODO: xercesの仕様をチェック
		// set LS (Load/Save)
		//        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(L"LS");
		DOMImplementation *implementation = DOMImplementation::getImplementation();
		DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();
		if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true)) {
			serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}

		serializer->setNewLine(XMLString::transcode("\r\n"));

		// Change filepath to XMLCh type.
		XMLCh *xFilePath = XMLString::transcode(filePath);

		// Create target file.
		XMLFormatTarget *formatTarget = new LocalFileFormatTarget(xFilePath);

		DOMLSOutput *output = ((DOMImplementationLS*)implementation)->createLSOutput();
		output->setByteStream(formatTarget);

		// Write
		serializer->write(doc, output);

		// Release
        // TODO: xercesの仕様を再度チェック
		serializer->release();
		XMLString::release(&xFilePath);
		delete formatTarget;
		output->release();
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
        printf("string:%s\n", string);
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
    
    void FavWriter::appendCDATA(DOMElement* parent_elem, const char* child_elem_name, XMLCh* text) {
        DOMElement *child_elem = doc->createElement(XMLString::transcode(child_elem_name));
        DOMCDATASection *text_elem = doc->createCDATASection(text);
        child_elem->appendChild(text_elem);
        parent_elem->appendChild(child_elem);
    };
    
    void FavWriter::appendCDATA(DOMElement* parent_elem, const char* child_elem_name, const char* text) {
        DOMElement *child_elem = doc->createElement(XMLString::transcode(child_elem_name));
        DOMCDATASection *text_elem = doc->createCDATASection(XMLString::transcode(text));
        child_elem->appendChild(text_elem);
        parent_elem->appendChild(child_elem);
    };
    
    void FavWriter::appendCDATA(DOMElement* parent_elem, const char* child_elem_name, std::string text) {
        appendCDATA(parent_elem, child_elem_name, text.c_str());
    };
    
    
    void FavWriter::appendText(DOMElement* parent_elem, const char* child_elem_name, const char* text) {
        DOMElement *child_elem = doc->createElement(XMLString::transcode(child_elem_name));
        DOMText *text_elem = doc->createTextNode(XMLString::transcode(text));
        child_elem->appendChild(text_elem);
        parent_elem->appendChild(child_elem);
    };
    
    void FavWriter::appendText(DOMElement* parent_elem, const char* child_elem_name, std::string text) {
        appendText(parent_elem, child_elem_name, text.c_str());
    };
    
    void FavWriter::setAttribute(DOMElement *elem, const char* attr_name, const char* attr_value) {
        elem->setAttribute(XMLString::transcode(attr_name), XMLString::transcode(attr_value));
        
    };
    
    void FavWriter::setAttribute(DOMElement *elem, const char* attr_name, std::string attr_value) {
        setAttribute(elem, attr_name, attr_value.c_str());
    };
    
}