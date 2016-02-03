//
//  Fav.cpp
//  fav_converter
//
//  Created by atsmsmr on 2016/01/15.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//

#include "Fav.h"

FabAbleVoxel::FabAbleVoxel()
{
    
}

FabAbleVoxel::~FabAbleVoxel()
{
    if(objects.size()>0){
        for(int i=0; i<objects.size(); i++){
            deleteObject(objects[i]);
        }
    }
    objects.clear();
}

void FabAbleVoxel::deleteObject(Object* object){
    delete object;
    object = nullptr;
};

bool FabAbleVoxel::importSTL(const char* filepath){
    
    FileIO* importer = new FileIO;
    Object* object = new Object;
    object->mesh = importer->importSTL(filepath);
    number_of_object = number_of_object + 1;
    delete importer;

    if(object->mesh != NULL){
        object->has_mesh = true;
        this->objects.push_back(object);
        printf("Finished to import STL file.\n vertices: %d\n faces: %d\n",object->mesh->number_of_vertices, object->mesh->number_of_faces);
        return 1;
    }
    
    return 0;
}

bool FabAbleVoxel::importOBJ(const char* filepath){
    
    // under developing...
    return 0;
}

bool FabAbleVoxel::voxelize(Object *object, float voxel_size[3]){
    
    object->voxel = new VoxelData;
    Voxelizer* voxelizer = new Voxelizer;
    voxelizer->voxelize(object->mesh->vertices, object->mesh->number_of_vertices, voxel_size);
    object->has_voxel = true;
    
    for(int i=0; i<3; i++){
        object->voxel->voxel_size[i] = voxelizer->voxel_size[i];
        object->voxel->voxel_origin[i] = voxelizer->voxel_origin[i];
        object->voxel->voxel_num[i] = voxelizer->voxel_num[i];
    }
    
    int total_voxel_num = object->voxel->voxel_num[0]*object->voxel->voxel_num[1]*object->voxel->voxel_num[2];
    object->voxel->data = new Voxel[total_voxel_num];

    for(int i=0; i<total_voxel_num; i++){
        object->voxel->data[i].state = voxelizer->voxel_data[i];
    }
    
    delete voxelizer; voxelizer=nullptr;
    return 0;
}

bool FabAbleVoxel::voxelize(Object *object, int voxel_num[3]){
    
    object->mesh->setAABB();
    float voxel_size[3] = {
        object->mesh->bounding_box.length[0] / (float)voxel_num[0],
        object->mesh->bounding_box.length[1] / (float)voxel_num[1],
        object->mesh->bounding_box.length[2] / (float)voxel_num[2]
    };
    
    object->voxel = new VoxelData;
    Voxelizer* voxelizer = new Voxelizer;
    voxelizer->voxelize(object->mesh->vertices, object->mesh->number_of_vertices, voxel_size);
    object->has_voxel = true;
    
    for(int i=0; i<3; i++){
        object->voxel->voxel_size[i] = voxelizer->voxel_size[i];
        object->voxel->voxel_origin[i] = voxelizer->voxel_origin[i];
        object->voxel->voxel_num[i] = voxelizer->voxel_num[i];
    }
    
    int total_voxel_num = object->voxel->voxel_num[0]*object->voxel->voxel_num[1]*object->voxel->voxel_num[2];
    object->voxel->data = new Voxel[total_voxel_num];
    
    for(int i=0; i<total_voxel_num; i++){
        object->voxel->data[i].state = voxelizer->voxel_data[i];
    }
    
    delete voxelizer; voxelizer=nullptr;
    return 0;
}

int FabAbleVoxel::getNumberOfObject(){
    return number_of_object;
}