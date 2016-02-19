//
//  object.cpp
//  fav_converter
//
//  Created by atsmsmr on 2016/01/30.
//  Copyright (c) 2016年 atsmsmr. All rights reserved.
//
#include <algorithm>
#include "object.h"

void VoxelData::setPosition(){
    
    for(int z=0; z<voxel_num[2]; z++){
        for(int y=0; y<voxel_num[1]; y++){
            for(int x=0; x<voxel_num[0]; x++){
                
                int index = (voxel_num[0]*voxel_num[1]*z) + (voxel_num[0]*y) + x;
                data[index].position[0] = x*voxel_size[0];
                data[index].position[1] = y*voxel_size[1];
                data[index].position[2] = z*voxel_size[2];
//                printf("%f,%f,%f\n",data[index].position[0],data[index].position[1],data[index].position[2]);

            }
        }
    }

}

int VoxelData::getIndex(int x, int y, int z){
    return (voxel_num[0]*voxel_num[1]*z) + (voxel_num[0]*y) + x;
}

int VoxelData::getNeighbors(int x, int y, int z){
    
    int neigbors =
    data[getIndex(x,y,z)].state +
    data[getIndex(x,y,z+1)].state +
    data[getIndex(x,y,z-1)].state +
    data[getIndex(x,y+1,z)].state +
    data[getIndex(x,y+1,z+1)].state +
    data[getIndex(x,y+1,z-1)].state +
    data[getIndex(x,y-1,z)].state +
    data[getIndex(x,y-1,z+1)].state +
    data[getIndex(x,y-1,z-1)].state +
    
    data[getIndex(x+1,y,z)].state +
    data[getIndex(x+1,y,z+1)].state +
    data[getIndex(x+1,y,z-1)].state +
    data[getIndex(x+1,y+1,z)].state +
    data[getIndex(x+1,y+1,z+1)].state +
    data[getIndex(x+1,y+1,z-1)].state +
    data[getIndex(x+1,y-1,z)].state +
    data[getIndex(x+1,y-1,z+1)].state +
    data[getIndex(x+1,y-1,z-1)].state +
    
    data[getIndex(x-1,y,z)].state +
    data[getIndex(x-1,y,z+1)].state +
    data[getIndex(x-1,y,z-1)].state +
    data[getIndex(x-1,y+1,z)].state +
    data[getIndex(x-1,y+1,z+1)].state +
    data[getIndex(x-1,y+1,z-1)].state +
    data[getIndex(x-1,y-1,z)].state +
    data[getIndex(x-1,y-1,z+1)].state +
    data[getIndex(x-1,y-1,z-1)].state;
    
    return neigbors;
}

void VoxelData::scale(float magni){
    if(magni < 1){
        reduct(magni);
    }else{
        expand(magni);
    }
}


void VoxelData::reduct(float magni){
    
    int old_total_num = voxel_num[0]*voxel_num[1]*voxel_num[2];
    
    for(int i=0; i<old_total_num; i++){
        data[i].position[0] = data[i].position[0] * magni;
        data[i].position[1] = data[i].position[1] * magni;
        data[i].position[2] = data[i].position[2] * magni;
    }
    
    for(int i=0; i<3; i++){
        voxel_num[i] = ceil(voxel_num[i] * magni);
//        voxel_origin[i] = voxel_origin[i] * magni;
    }
    
    Voxel* new_data = new Voxel[voxel_num[0]*voxel_num[1]*voxel_num[2]];
    
    for(int i=0; i<old_total_num; i++){
        
        int x = (int)round((data[i].position[0])/(float)voxel_size[0]);
        int y = (int)round((data[i].position[1])/(float)voxel_size[1]);
        int z = (int)round((data[i].position[2])/(float)voxel_size[2]);
        
        
        if(x > 0 && y > 0 && z > 0 && x < voxel_num[0] && y < voxel_num[1] && z < voxel_num[2]){
            
            int index = (voxel_num[0]*voxel_num[1]*z) + (voxel_num[0]*y) + x;
            new_data[index] = data[i];
            data[i].state = NULL;
        }
    }
    
    
    delete[] data; data = nullptr;
    data = new_data;
    
    for(int z=0; z<voxel_num[2]; z++){
        for(int y=0; y<voxel_num[1]; y++){
            for(int x=0; x<voxel_num[0]; x++){
                
                if(x-1 > 0 && y-1 > 0 && z-1 > 0 && x+1 < voxel_num[0]-1 && y+1 < voxel_num[1]-1 && z+1 < voxel_num[2]-1){
                    
                    int index = (voxel_num[0]*voxel_num[1]*z) + (voxel_num[0]*y) + x;
                    
                    if(data[index].state == 0){
                        
                        if( (data[getIndex(x+1,y,z)].state != 0 && data[getIndex(x-1,y,z)].state != 0) ||
                           (data[getIndex(x,y+1,z)].state != 0 && data[getIndex(x,y-1,z)].state != 0) ||
                           (data[getIndex(x,y,z+1)].state != 0 && data[getIndex(x,y,z-1)].state != 0) ||
                           
                           (data[getIndex(x-1,y,z-1)].state != 0 && data[getIndex(x+1,y,z+1)].state != 0) ||
                           (data[getIndex(x-1,y,z+1)].state != 0 && data[getIndex(x+1,y,z-1)].state != 0) ||
                           (data[getIndex(x,y-1,z-1)].state != 0 && data[getIndex(x,y+1,z+1)].state != 0) ||
                           (data[getIndex(x,y-1,z+1)].state != 0 && data[getIndex(x,y+1,z-1)].state != 0) ||
                           
//                           (data[getIndex(x-1,y-1,z)].state != 0 && data[getIndex(x+1,y+1,z)].state != 0) ||
//                           (data[getIndex(x-1,y,z-1)].state != 0 && data[getIndex(x+1,y,z+1)].state != 0) ||
//                           (data[getIndex(x,y-1,z-1)].state != 0 && data[getIndex(x,y+1,z+1)].state != 0) ||
//                           
//                           (data[getIndex(x-1,y-1,z)].state != 0 && data[getIndex(x+1,y,z)].state != 0) ||
//                           (data[getIndex(x+1,y-1,z)].state != 0 && data[getIndex(x+1,y,z)].state != 0) ||
//
//                           (data[getIndex(x-1,y,z+1)].state != 0 && data[getIndex(x+1,y,z)].state != 0) ||
//                           (data[getIndex(x,y-1,z-1)].state != 0 && data[getIndex(x,y+1,z+1)].state != 0) ||
                           
                           (data[getIndex(x+1,y-1,z-1)].state != 0 && data[getIndex(x-1,y+1,z+1)].state != 0) ||
                           (data[getIndex(x-1,y+1,z-1)].state != 0 && data[getIndex(x+1,y-1,z+1)].state != 0) ||
                           (data[getIndex(x-1,y-1,z+1)].state != 0 && data[getIndex(x+1,y+1,z-1)].state != 0) ||
                           (data[getIndex(x-1,y-1,z-1)].state != 0 && data[getIndex(x+1,y+1,z+1)].state != 0)
                           
                           
                           )
                        {
                            data[index].state = 1;
                            data[index].color.r = 0.2;
                            data[index].color.g = 0.2;
                            data[index].color.b = 0.2;
                            data[index].color.a = 0.9;
                        }
                    }
                    
                }
            }
        }
    }
    
    //    // set continuous-transition color
    //    for(int z=0; z<voxel_num[2]; z++){
    //        for(int y=0; y<voxel_num[1]; y++){
    //            for(int x=0; x<voxel_num[0]; x++){
    //                int index = getIndex(x,y,z);
    //                data[index].color.r = (float)x/voxel_num[0];
    //                data[index].color.g = (float)y/voxel_num[1];
    //                data[index].color.b = (float)z/voxel_num[2];
    //            }
    //        }
    //    }
    
    setPosition();
}

void VoxelData::expand(float magni){
    
    int old_total_num = voxel_num[0]*voxel_num[1]*voxel_num[2];
    
    for(int i=0; i<old_total_num; i++){
        data[i].position[0] = data[i].position[0] * magni;
        data[i].position[1] = data[i].position[1] * magni;
        data[i].position[2] = data[i].position[2] * magni;
    }

    for(int i=0; i<3; i++){
        voxel_num[i] = ceil(voxel_num[i] * magni)+1;
        voxel_origin[i] = voxel_origin[i] * magni;
    }
    
    Voxel* new_data = new Voxel[voxel_num[0]*voxel_num[1]*voxel_num[2]];
//    Voxel* new_data2 = new Voxel[voxel_num[0]*voxel_num[1]*voxel_num[2]];

    for(int i=0; i<old_total_num; i++){
        
        int x = (int)round((data[i].position[0])/voxel_size[0]);
        int y = (int)round((data[i].position[1])/voxel_size[1]);
        int z = (int)round((data[i].position[2])/voxel_size[2]);
        
//        printf("%f,%f,%f\n",data[i].position[0], data[i].position[1], data[i].position[2]);
//        std::cout << x << "," << y << "," << z << std::endl;
      
        if(x > 0 && y > 0 && z > 0 && x < voxel_num[0] && y < voxel_num[1] && z < voxel_num[2]){
            
            int index = (voxel_num[0]*voxel_num[1]*z) + (voxel_num[0]*y) + x;
            new_data[index] = data[i];
//            new_data2[index] = data[i];

        }
    }
    
    delete[] data; data = nullptr;
    data = new_data;
    
    for(int z=0; z<voxel_num[2]; z++){
        for(int y=0; y<voxel_num[1]; y++){
            for(int x=0; x<voxel_num[0]; x++){
                
                if(x-1 > 0 && y-1 > 0 && z-1 > 0 && x+1 < voxel_num[0]-1 && y+1 < voxel_num[1]-1 && z+1 < voxel_num[2]-1){
                    
                    int index = (voxel_num[0]*voxel_num[1]*z) + (voxel_num[0]*y) + x;
                    
                    if(data[index].state == 0){
                        
                        if( (data[getIndex(x+1,y,z)].state != 0 && data[getIndex(x-1,y,z)].state != 0) ||
                           (data[getIndex(x,y+1,z)].state != 0 && data[getIndex(x,y-1,z)].state != 0) ||
                           (data[getIndex(x,y,z+1)].state != 0 && data[getIndex(x,y,z-1)].state != 0) ||
                           
                           (data[getIndex(x-1,y,z-1)].state != 0 && data[getIndex(x+1,y,z+1)].state != 0) ||
                           (data[getIndex(x-1,y,z+1)].state != 0 && data[getIndex(x+1,y,z-1)].state != 0) ||
                           (data[getIndex(x,y-1,z-1)].state != 0 && data[getIndex(x,y+1,z+1)].state != 0) ||
                           (data[getIndex(x,y-1,z+1)].state != 0 && data[getIndex(x,y+1,z-1)].state != 0) ||
                           
//                           (data[getIndex(x-1,y-1,z)].state != 0 && data[getIndex(x+1,y+1,z)].state != 0) ||
//                           (data[getIndex(x-1,y,z-1)].state != 0 && data[getIndex(x+1,y,z+1)].state != 0) ||
//                           (data[getIndex(x,y-1,z-1)].state != 0 && data[getIndex(x,y+1,z+1)].state != 0) ||
//                           
//                           (data[getIndex(x-1,y-1,z)].state != 0 && data[getIndex(x+1,y,z)].state != 0) ||
//                           (data[getIndex(x+1,y-1,z)].state != 0 && data[getIndex(x+1,y,z)].state != 0) ||
//                           
//                           (data[getIndex(x-1,y,z+1)].state != 0 && data[getIndex(x+1,y,z)].state != 0) ||
//                           (data[getIndex(x,y-1,z-1)].state != 0 && data[getIndex(x,y+1,z+1)].state != 0) ||
                           
                           (data[getIndex(x+1,y-1,z-1)].state != 0 && data[getIndex(x-1,y+1,z+1)].state != 0) ||
                           (data[getIndex(x-1,y+1,z-1)].state != 0 && data[getIndex(x+1,y-1,z+1)].state != 0) ||
                           (data[getIndex(x-1,y-1,z+1)].state != 0 && data[getIndex(x+1,y+1,z-1)].state != 0) ||
                           (data[getIndex(x-1,y-1,z-1)].state != 0 && data[getIndex(x+1,y+1,z+1)].state != 0)
                           )
                        {
                            data[index].state = 1;
                            data[index].color.r = 0.2;
                            data[index].color.g = 0.2;
                            data[index].color.b = 0.2;
                            data[index].color.a = 0.9;
                        }
                    }
                
                }
            }
        }
    }
    
//    // set continuous-transition color
//    for(int z=0; z<voxel_num[2]; z++){
//        for(int y=0; y<voxel_num[1]; y++){
//            for(int x=0; x<voxel_num[0]; x++){
//                int index = getIndex(x,y,z);
//                data[index].color.r = (float)x/voxel_num[0];
//                data[index].color.g = (float)y/voxel_num[1];
//                data[index].color.b = (float)z/voxel_num[2];
//            }
//        }
//    }
    
//    delete[] data; data=nullptr;
//    data = new_data2;
    setPosition();
}

void VoxelData::rotateX(float angle){
    
}

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