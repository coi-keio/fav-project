//
//  Palette.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__Palette__
#define __FavLibrary__Palette__

#include <stdio.h>
#include "Metadata.h"

class Geometry{
    
public:
    Geometry(){
        shape = "cube";
        scale.x = 1.0;
        scale.y = 1.0;
        scale.z = 1.0;
    };
    
    Geometry(int index_, std::string name_){
        index = index_;
        name = name_;
        shape = "cube";
        scale.x = 1.0;
        scale.y = 1.0;
        scale.z = 1.0;
    };
    
    Geometry(int index_, std::string name_, std::string shape_, float scale_x_, float scale_y_, float scale_z_)
    {
        index = index_;
        name = name_;
        shape = shape_;
        scale.x = scale_x_;
        scale.y = scale_y_;
        scale.z = scale_z_;
    };
    
    Geometry(int index_, std::string name_, std::string shape_, std::string shape_data_path_, float scale_x_, float scale_y_, float scale_z_)
    {
        index = index_;
        name = name_;
        shape = shape_;
        if(shape == "user_defined"){
            loadShapeData(shape_data_path_);
        }
        scale.x = scale_x_;
        scale.y = scale_y_;
        scale.z = scale_z_;
    };
    
    void loadShapeData(std::string file_path); //under development
    
    int getId(){ return index; };
    std::string getShape(){ return shape; };
    std::string getName(){ return name; };
    float getScaleX(){ return scale.x; };
    float getScaleY(){ return scale.y; };
    float getScaleZ(){ return scale.z; };
    
    void setId(int index_){ index = index_; };
    void setName(std::string name_){ name = name_; };
    void setShape(std::string shape_){ shape = shape_; };
    void setScale(double x_, double y_, double z_){ scale.x = x_; scale.y = y_; scale.z = z_; };
    void setScaleX(double x_){ scale.x = x_; };
    void setScaleY(double y_){ scale.y = y_; };
    void setScaleZ(double z_){ scale.z = z_; };

private:
    int index;
    std::string name;
    std::string shape;

    class Scale{
    public:
        double x;
        double y;
        double z;
    };
    
    Scale scale;
};

class Material{
    
public:
    Material(){ has_material_name = false; has_product_info = false; has_iso_standard = false; has_meta_data = false; };
    
    class ProductInfo{
    public:
        ProductInfo(std::string manufacturer_, std::string product_name_, std::string url_)
        {
            manufacturer = manufacturer_;
            product_name = product_name_;
            url = url_;
        };
        
        std::string getManufacturer(){ return manufacturer; };
        std::string getProductName(){ return product_name; };
        std::string getUrl(){ return url; };
        
        void setManufacturer(std::string manufacturer_){ manufacturer = manufacturer_; };
        void setProductName(std::string product_name_){ product_name = product_name_; };
        void setUrl(std::string url_){ url = url_; };
        
    private:
        std::string manufacturer;
        std::string product_name;
        std::string url;
    };
    
    class IsoStandard{
    public:
        IsoStandard(std::string iso_id_, std::string iso_name_){ iso_id = iso_id_, iso_name = iso_name_; };
        std::string getIsoId(){ return iso_id; };
        std::string getIsoName(){ return iso_name; };
        void setIsoId(std::string iso_id_){ iso_id = iso_id_; };
        void setIsoName(std::string iso_name_) {iso_name = iso_name_; };
        
    private:
        std::string iso_id;
        std::string iso_name;
    };
    
    bool hasMaterialName(){ return has_material_name; };
    bool hasProductInfo(){ return has_product_info; };
    bool hasIsoStandard(){ return has_iso_standard; };
    bool hasMetadata(){ return has_meta_data; };
    int getNumProductInfo(){ return int(product_info.size()); };
    
    void addMaterialName(std::string material_name_){ material_name.push_back(material_name_); has_material_name = true; };
    void addProductInfo(std::string manufacturer_, std::string product_name_, std::string url_){
        product_info.push_back(new ProductInfo(manufacturer_, product_name_, url_));
        has_product_info = true;
    };
    void addIsoStandard(std::string iso_id_, std::string iso_name_){
        iso_standard.push_back(new IsoStandard(iso_id_, iso_name_));
        has_iso_standard = true;
    };
    
    ProductInfo* getProductInfo(int index_){ return product_info[index_]; };
    IsoStandard* getIsoStandard(int index_){ return iso_standard[index_]; };
    void setMetadata(Metadata metadata_){ metadata = &metadata_; has_meta_data = true; };

private:
    int index;
    std::string name;
    
    std::vector<std::string> material_name;
    std::vector<ProductInfo*> product_info;
    std::vector<IsoStandard*> iso_standard;
    Metadata* metadata;
    
    bool has_material_name;
    bool has_product_info;
    bool has_iso_standard;
    bool has_meta_data;
    
};

class Palette{
    
public:
    void addGeometry(Geometry *geometry_){ geometry.push_back(geometry_); };
    void addMaterial(Material *material_){ material.push_back(material_); };
    Geometry* getGeometry(int index_){ return geometry[index_]; };
    Material* getMaterial(int index_){ return material[index_]; };
    int getNumberOfGeometries(){ return number_of_geometries; };
    int getNumberOfMaterials(){ return number_of_materials; };
    
private:
    int number_of_geometries;
    int number_of_materials;
    std::vector<Geometry*> geometry;
    std::vector<Material*> material;
};

#endif /* defined(__FavLibrary__Palette__) */
