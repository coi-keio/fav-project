//
//  object.cpp
//  fav_converter
//
//  Created by atsmsmr on 2016/01/30.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//

#include "object.h"

float* MeshData::getCenter(){
    
    //Initialize min and max values
    float min_x = this->vertices[0];
    float min_y = this->vertices[0];
    float min_z = this->vertices[0];
    float max_x = this->vertices[0];
    float max_y = this->vertices[0];
    float max_z = this->vertices[0];
    
    //Calculate center of meshes
    for(int i=0; i<this->number_of_vertices; i++){
        if(min_x > this->vertices[i*3]) min_x = this->vertices[i*3];
        if(min_y > this->vertices[i*3+1]) min_y = this->vertices[i*3+1];
        if(min_z > this->vertices[i*3+2]) min_z = this->vertices[i*3+2];
        
        if(max_x < this->vertices[i*3]) max_x = this->vertices[i*3];
        if(max_y < this->vertices[i*3+1]) max_y = this->vertices[i*3+1];
        if(max_z < this->vertices[i*3+2]) max_z = this->vertices[i*3+2];
    }
    
    float* center_of_meshes = new float[3]{(max_x+min_x)/2.0f,(max_y+min_y)/2.0f,(max_z+min_z)/2.0f};
    return center_of_meshes;
}

void MeshData::setAABB(){
    
    //Initialize min and max values
    float min_x = this->vertices[0];
    float min_y = this->vertices[0];
    float min_z = this->vertices[0];
    float max_x = this->vertices[0];
    float max_y = this->vertices[0];
    float max_z = this->vertices[0];
    
    //Calculate center of meshes
    for(int i=0; i<this->number_of_vertices; i++){
        if(min_x > this->vertices[i*3]) min_x = this->vertices[i*3];
        if(min_y > this->vertices[i*3+1]) min_y = this->vertices[i*3+1];
        if(min_z > this->vertices[i*3+2]) min_z = this->vertices[i*3+2];
        
        if(max_x < this->vertices[i*3]) max_x = this->vertices[i*3];
        if(max_y < this->vertices[i*3+1]) max_y = this->vertices[i*3+1];
        if(max_z < this->vertices[i*3+2]) max_z = this->vertices[i*3+2];
    }
    
    origin[0] = min_x;
    origin[1] = min_y;
    origin[2] = min_z;
    
    bounding_box.length[0] = fabs(max_x-min_x);// *1.1 is for avoiding rounding(?) error.
    bounding_box.length[1] = fabs(max_y-min_y);
    bounding_box.length[2] = fabs(max_z-min_z);
    bounding_box.max_length = std::max({bounding_box.length[0],bounding_box.length[1],bounding_box.length[2]});
    
    //set value to AABB
    for(int i=0; i<3; i++){
        bounding_box.position[i] = origin[i]+bounding_box.length[i]/2.0f;
    }

}

void MeshData::translate(float* destination){
    
    for(int i=0; i<this->number_of_vertices; i++){
        this->vertices[i*3] += destination[0];
        this->vertices[i*3+1] += destination[1];
        this->vertices[i*3+2] += destination[2];
    }
    
}

void MeshData::translateToOrigin(){
    
    float* center = this->getCenter();
    float destination[3] = {-center[0],-center[1],-center[2]};
    translate(destination);
}