#include "Voxel.h"
#include "Fav.h"

namespace FavLibrary
{
	VoxelInfo::VoxelInfo() {};
	VoxelInfo::VoxelInfo(unsigned int id_) { identifier = id_; };
	VoxelInfo::~VoxelInfo() {};

	unsigned int VoxelInfo::getId() { return identifier; };
	void VoxelInfo::setId(unsigned int id_) { identifier = id_; };

	GeometryInfo::GeometryInfo() : VoxelInfo() {};
	GeometryInfo::GeometryInfo(unsigned int id_) : VoxelInfo(id_) {};
	GeometryInfo::~GeometryInfo() {};

	MaterialInfo::MaterialInfo() : VoxelInfo() {};
	MaterialInfo::MaterialInfo(unsigned int id_) : VoxelInfo(id_) { };
	MaterialInfo::MaterialInfo(unsigned int id_, double ratio_) : VoxelInfo(id_) { ratio = ratio_; };
	MaterialInfo::~MaterialInfo() {};

	double MaterialInfo::getRatio() { return ratio; };
	void MaterialInfo::setRatio(double ratio_) { ratio = ratio_; };


	///////////////////////////////////////////
	////////////////class Voxel////////////////
	///////////////////////////////////////////
	Voxel::Voxel() : FavPrimitive()
	{
		m_reference_fav  = 0;
		m_reference_path = std::string("");
	}
	Voxel::Voxel(unsigned int id_ ) : FavPrimitive(id_  ) { Voxel(); }
	Voxel::Voxel(std::string name_) : FavPrimitive(name_) { Voxel(); }
	Voxel::Voxel(unsigned int id_, std::string name_) : FavPrimitive(id_, name_) { Voxel(); }
	
	Voxel::~Voxel() 
	{ 
		if(m_reference_fav!= 0) delete m_reference_fav;
		m_reference_fav = 0;
	}

	void Voxel::setGeometryInfo(GeometryInfo geometry_info_) { geometry_info = GeometryInfo(geometry_info_); }
	GeometryInfo Voxel::getGeometryInfo() { return geometry_info; }

	std::vector<MaterialInfo> Voxel::getMaterialInfo()
	{
		std::vector<MaterialInfo> res = material_info;
		return res;
	};
	MaterialInfo Voxel::getMaterialInfo(unsigned int id_) { return material_info[id_]; };
	void Voxel::addMaterialInfo(unsigned int id_, double ratio_) { material_info.push_back(MaterialInfo(id_, ratio_)); };
	void Voxel::unpdateMaterialInfo(unsigned int id_, double ratio_) { material_info[id_].setRatio(ratio_); };
	void Voxel::removeMaterialInfo(unsigned int id_) { material_info.erase(material_info.begin() + id_); }
	bool Voxel::existsMaterialInfo(unsigned int id_) { return material_info.size() > 0; }
	int Voxel::getNumMaterialInfo() { return (int)material_info.size(); };
	ColorRGBA Voxel::getDisplay() { return display; };
	void Voxel::setDisplay(unsigned char r_, unsigned char g_, unsigned char b_, unsigned char a_) { display.setColorRBGA(r_, g_, b_, a_); };
	void Voxel::setDisplay(ColorRGBA color_) { display.setColorRBGA(color_.getR(), color_.getG(), color_.getB(), color_.getA()); };

	unsigned char Voxel::getDisplayR() { return display.getR(); };
	void Voxel::setDisplayR(unsigned char r_) { display.setR(r_); };
	unsigned char Voxel::getDisplayG() { return display.getG(); };
	void Voxel::setDisplayG(unsigned char g_) { display.setG(g_); };
	unsigned char Voxel::getDisplayB() { return display.getB(); };
	void Voxel::setDisplayB(unsigned char b_) { display.setB(b_); };
	unsigned char Voxel::getDisplayA() { return display.getA(); };
	void Voxel::setDisplayA(unsigned char a_) { display.setA(a_); };

	std::string Voxel::getApplicationNote() { return application_note; };
	void Voxel::setApplicationNote(std::string note_) { application_note = note_; };


	void Voxel::setReferencePath(std::string reference_path)
	{
		//TODO load fav file!
		printf("todo load fav file\n");
		m_reference_path = reference_path;
	}

	std::string Voxel::getReferencePath()
	{
		return m_reference_path;
	}


}