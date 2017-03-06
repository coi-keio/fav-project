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

	bool FavWriter::write(const char* file_path, const char* version) {
		XMLPlatformUtils::Initialize();

		//インスタンス作成.
		DOMImplementation *tpImpl = DOMImplementationRegistry::getDOMImplementation(XMLString::transcode("Core"));

		//ドキュメント生成( エレメントをModelに設定 ).
		doc = tpImpl->createDocument(0, XMLString::transcode("fav"), 0);
		DOMElement	*fav_elem = doc->getDocumentElement();
		setAttribute(fav_elem, "version", version);

		// Add Elements to fav
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

	void FavWriter::writeMetadata(DOMElement *parent_elem) {

		DOMElement *metadata_elem = doc->createElement(XMLString::transcode("metadata"));

		appendCDATA(metadata_elem, "title", fav->getMetadataTitle());
		appendCDATA(metadata_elem, "author", fav->getMetadataAuthor());
		appendCDATA(metadata_elem, "license", fav->getMetadataLicense());

		// noteに関して追記
		parent_elem->appendChild(metadata_elem);
	}


	void FavWriter::writePalette(DOMElement *parent_elem) {

		DOMElement *palette_elem = doc->createElement(XMLString::transcode("palette"));


		// write geometry
		int number_of_geometries = fav->palette.getNumberOfGeometries();

		for (int i = 0; i < number_of_geometries; ++i) {

			Geometry tmp = fav->palette.getGeometryById(i + 1);
			DOMElement *geo_elem = doc->createElement(XMLString::transcode("geometry"));

			setAttribute(geo_elem, "id", std::to_string(tmp.getId()));

			// if(tmp->has_name){
			setAttribute(geo_elem, "name", tmp.getName());

			if (tmp.getShape() == GeometryShape::user_defined) {
				// under development : add reference path
				appendText(geo_elem, "shape", "user_defined");

			}
			else if (tmp.getShape() == GeometryShape::cube) {
				appendText(geo_elem, "shape", "cube");

			}
			else if (tmp.getShape() == GeometryShape::sphere) {
				appendText(geo_elem, "shape", "spehre");

			}

			DOMElement *scale_elem = doc->createElement(XMLString::transcode("scale"));
			appendText(scale_elem, "x", std::to_string(tmp.getScaleX()));
			appendText(scale_elem, "y", std::to_string(tmp.getScaleY()));
			appendText(scale_elem, "z", std::to_string(tmp.getScaleZ()));
			geo_elem->appendChild(scale_elem);

			palette_elem->appendChild(geo_elem);
		}


		// write material
		int number_of_materials = fav->palette.getNumberOfMaterials();
		std::cout << number_of_materials << std::endl;

		for (int i = 0; i < number_of_materials; ++i) {
			int index = i + 1;
			//        if(i==0) index = 1;
			//        else if(i==1)index = 3;
			Material tmp = fav->palette.getMaterialById(index);
			DOMElement *mat_elem = doc->createElement(XMLString::transcode("material"));

			setAttribute(mat_elem, "id", std::to_string(tmp.getId()));
			// if(tmp->has_name){
			setAttribute(mat_elem, "name", tmp.getName());

			// 優先順位問題をmaterialクラスの構造で解決する必要がある
			for (auto material : tmp.materials) {
				if (material->materialType == MaterialType::product_info) {
					ProductInfo* p_info = dynamic_cast<ProductInfo*>(material);
					DOMElement *pinfo_elem = doc->createElement(XMLString::transcode("product_info"));
					appendCDATA(pinfo_elem, "manufacturer", p_info->getManufacturer());
					appendCDATA(pinfo_elem, "product_name", p_info->getProductName());
					appendCDATA(pinfo_elem, "url", p_info->getUrl());
					mat_elem->appendChild(pinfo_elem);
				}
				else if (material->materialType == MaterialType::iso_standard) {

					DOMElement *iso_elem = doc->createElement(XMLString::transcode("iso_standard"));
					IsoStandard* iso = dynamic_cast<IsoStandard*>(material);
					appendCDATA(iso_elem, "iso_id", iso->getIsoId());
					appendCDATA(iso_elem, "iso_name", iso->getIsoName());
					mat_elem->appendChild(iso_elem);
				}

				else if (material->materialType == MaterialType::material_name) {
					DOMElement *name_elem = doc->createElement(XMLString::transcode("material_name"));
					MaterialName* material_name = dynamic_cast<MaterialName*>(material);
					appendCDATA(name_elem, "material_name", material_name->getMaterialName());
					mat_elem->appendChild(name_elem);
				}
			}
			palette_elem->appendChild(mat_elem);
		}

		parent_elem->appendChild(palette_elem);
	}

	void FavWriter::writeVoxel(DOMElement *parent_elem) {

		DOMElement *voxel_elem = doc->createElement(XMLString::transcode("voxel"));

		for (int i = 0, size = (int)fav->getNumVoxels(); i < size; ++i) {
			DOMElement *vox_elem = doc->createElement(XMLString::transcode("voxel"));
			Voxel tmp = fav->getVoxel(i + 1);
			setAttribute(vox_elem, "id", std::to_string(tmp.getId()));
			setAttribute(vox_elem, "name", tmp.getName());
			DOMElement *geo_elem = doc->createElement(XMLString::transcode("geometry_info"));
			appendText(geo_elem, "id", std::to_string(tmp.getGeometryInfo()));
			vox_elem->appendChild(geo_elem);


			for (int j = 0, size = tmp.getNumMaterialInfo(); j < size; ++j) {
				DOMElement *matinfo_elem = doc->createElement(XMLString::transcode("material_info"));
				appendText(matinfo_elem, "id", std::to_string(tmp.getMaterialInfo(j).getId()));
				appendText(matinfo_elem, "ratio", std::to_string(tmp.getMaterialInfo(j).getRatio()));
				vox_elem->appendChild(matinfo_elem);
			}
			voxel_elem->appendChild(vox_elem);
		}

		parent_elem->appendChild(voxel_elem);

	};

	void FavWriter::writeGrid(DOMElement* parent_elem, Grid* grid) {

		//    // waiting for grid class
		DOMElement *grid_elem = doc->createElement(XMLString::transcode("grid"));

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

	void str2bin(const unsigned char *str, unsigned char *hex, int len)
	{
		int i = 0;
		for (i = 0; i < (len >> 1); i++) {
			unsigned int tmp;
			sscanf_s((const char*)str + (i << 1), "%2x", &tmp);
			hex[i] = (unsigned char)tmp & 0xff;
		}
	}

	void BytesFromHexString(unsigned char *data, const char *string) {
		printf("string:%s\n", string);
		int len = (int)strlen(string);
		for (int i = 0; i < len; i += 2) {
			unsigned int x;
			sscanf_s((char *)(string + i), "%02x", &x);
			data[i / 2] = x;
		}
	}

	void deleteNewLine(std::string &targetStr)
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

	void FavWriter::writeVoxelMap(DOMElement* parent_elem, Structure* p_str) {

		// voxel_map
		// compression is under development
		const char* compression = "base64";
		DOMElement *vmap_elem = doc->createElement(XMLString::transcode("voxel_map"));
		setAttribute(vmap_elem, "compression", std::string(compression));
		setAttribute(vmap_elem, "bit_per_voxel", std::to_string(p_str->getBitPerVoxel()));

		std::string layer_data;
		for (int z = 0, size = p_str->grid->getDimensionZ(); z < size; ++z) {
			layer_data.clear();
			for (int y = 0, size = p_str->grid->getDimensionY(); y < size; ++y) {
				for (int x = 0, size = p_str->grid->getDimensionX(); x < size; ++x) {
					int data = p_str->getVoxel(x, y, z);

					if (p_str->getBitPerVoxel() == 4) {
						layer_data += std::to_string(data);

					}
					else if (p_str->getBitPerVoxel() == 8) {
						char buff[2];
						sprintf_s(buff, "%02x", data);
						layer_data.push_back(buff[0]);
						layer_data.push_back(buff[1]);

					}
					else if (p_str->getBitPerVoxel() == 16) {
						char buff[4];
						sprintf_s(buff, "%04x", data);
						layer_data.push_back(buff[0]);
						layer_data.push_back(buff[1]);
						layer_data.push_back(buff[2]);
						layer_data.push_back(buff[3]);
					}
					else {
						// error ただ、この辺はschemaのvaridationで全部省略できるのかな？？
					}
				}
			}

			if (compression == "none") {

				appendCDATA(vmap_elem, "layer", layer_data);

			}
			else if (compression == "base64") { // there are bugs here.

				int size = p_str->grid->getDimensionX() * p_str->grid->getDimensionY();
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


			}
			else {
				// error;
			}

			//        std::cout << layer_data << std::endl;
		}

		parent_elem->appendChild(vmap_elem);

	}

	void FavWriter::writeColorMap(DOMElement* parent_elem, Structure* p_str) {

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

	void FavWriter::writeStructure(DOMElement* parent_elem, Structure* p_str) {
		// waiting for structure class
		DOMElement *struct_elem = doc->createElement(XMLString::transcode("structure"));

		writeVoxelMap(struct_elem, p_str);
		writeColorMap(struct_elem, p_str);

		parent_elem->appendChild(struct_elem);
	}


	void FavWriter::writeObject(DOMElement* parent_elem) {

		for (int i = 0, size = fav->getNumObjects(); i < size; ++i) {
			Object tmp = fav->getObject(i);
			DOMElement *obj_elem = doc->createElement(XMLString::transcode("object"));
			setAttribute(obj_elem, "id", "1");
			//        setAttribute(obj_elem, "id", std::to_string(tmp->getId()));
			//        setAttribute(obj_elem, "name", tmp->getName());
			writeGrid(obj_elem, tmp.grid);
			writeStructure(obj_elem, tmp.structure);
			parent_elem->appendChild(obj_elem);
		}

	}

	void FavWriter::writeXML(const char *filePath) {
		// set LS (Load/Save)
		//        DOMImplementation *implementation = DOMImplementationRegistry::getDOMImplementation(L"LS");
		DOMImplementation *implementation = DOMImplementation::getImplementation();

		DOMLSSerializer *serializer = ((DOMImplementationLS*)implementation)->createLSSerializer();
		if (serializer->getDomConfig()->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true)) {
			serializer->getDomConfig()->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, true);
		}

		serializer->setNewLine(XMLString::transcode("\r\n"));

		// Change filepath to XMLCh type.
		XMLCh *tempFilePath = XMLString::transcode(filePath);

		// Create target file.
		XMLFormatTarget *formatTarget = new LocalFileFormatTarget(tempFilePath);

		DOMLSOutput *output = ((DOMImplementationLS*)implementation)->createLSOutput();
		output->setByteStream(formatTarget);

		// Write
		serializer->write(doc, output);

		// Release
		serializer->release();
		XMLString::release(&tempFilePath);
		delete formatTarget;
		output->release();
	};

}