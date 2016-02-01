//
//  file_io.h
//  Voxelizer
//
//  Created by atsmsmr on 2015/10/28.
//  Copyright (c) 2015年 Atsushi Masumori. All rights reserved.
//

#ifndef __Voxelizer__file_io__
#define __Voxelizer__file_io__

#include <OpenGL/gl.h>
#include <iostream>
#include <map>
#include <vector>
#include <assert.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "object.h"

class FileIO
{
private:
    
    public :
	class MeshEntry {
    public:
		MeshEntry(aiMesh *a_mesh);
		~MeshEntry();
        MeshData* getMeshData();
        MeshData* mesh;
        
        //        std::vector<float> texCoords;
    };
    
public:
    FileIO();
    ~FileIO();
    MeshData* importSTL(const char *filepath);
    bool importFAV(const char *filepath);
    
	std::vector<MeshEntry*> meshEntries;
};

#endif /* defined(__Voxelizer__file_io__) */
