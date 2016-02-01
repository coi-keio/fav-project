//
//  file_io.cpp
//  Voxelizer
//
//  Created by atsmsmr on 2015/10/28.
//  Copyright (c) 2015年 Atsushi Masumori. All rights reserved.
//

#include "file_io.h"


FileIO::MeshEntry::MeshEntry(aiMesh *a_mesh) {
    
    this->mesh = new MeshData;
    this->mesh->number_of_vertices = a_mesh->mNumVertices;
    this->mesh->number_of_faces = a_mesh->mNumFaces;
	
    if(a_mesh->HasPositions()) {
        this->mesh->vertices = new float[a_mesh->mNumVertices*3];
		for(int i = 0; i < a_mesh->mNumVertices; ++i) {
			this->mesh->vertices[i * 3] = a_mesh->mVertices[i].x;
			this->mesh->vertices[i * 3 + 1] = a_mesh->mVertices[i].y;
			this->mesh->vertices[i * 3 + 2] = a_mesh->mVertices[i].z;
		}
	}
    
	if(a_mesh->HasNormals()) {
		this->mesh->normals = new float[a_mesh->mNumVertices*3];
		for(int i = 0; i < a_mesh->mNumVertices; ++i) {
			this->mesh->normals[i * 3] = a_mesh->mNormals[i].x;
			this->mesh->normals[i * 3 + 1] = a_mesh->mNormals[i].y;
			this->mesh->normals[i * 3 + 2] = a_mesh->mNormals[i].z;
		}
	}
    
	if(a_mesh->HasFaces()) {
		this->mesh->faces = new GLuint[a_mesh->mNumFaces*3];
		for(int i = 0; i < a_mesh->mNumFaces; ++i) {
			this->mesh->faces[i * 3] = a_mesh->mFaces[i].mIndices[0];
			this->mesh->faces[i * 3 + 1] = a_mesh->mFaces[i].mIndices[1];
			this->mesh->faces[i * 3 + 2] = a_mesh->mFaces[i].mIndices[2];
		}
	}
    
    //    if(mesh->HasTextureCoords(0)) {
    //		float *texCoords = new float[mesh->mNumVertices * 2];
    //		for(int i = 0; i < mesh->mNumVertices; ++i) {
    //			texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
    //			texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
    //		}
    //	}
}

FileIO::MeshEntry::~MeshEntry(){
    delete mesh;
}

MeshData* FileIO::MeshEntry::getMeshData(){
    return this->mesh;
}

FileIO::FileIO(){}


FileIO::~FileIO()
{
	for(int i = 0; i < meshEntries.size(); ++i) {
		delete meshEntries.at(i);
	}
	meshEntries.clear();
}

MeshData* FileIO::importSTL(const char *filepath){
	Assimp::Importer importer;
	const aiScene *scene = importer.ReadFile(filepath,
                                             aiProcess_JoinIdenticalVertices    |
                                             aiProcess_CalcTangentSpace         |
                                             aiProcess_Triangulate              |
                                             aiProcess_SplitLargeMeshes         |
                                             aiProcess_GenNormals               |
                                             aiProcess_SortByPType);
	if(!scene) {
		printf("Unable to laod mesh: %s\n", importer.GetErrorString());
	}
    
	for(int i=0; i<scene->mNumMeshes; ++i) {
		meshEntries.push_back(new FileIO::MeshEntry(scene->mMeshes[i]));
	}
    
    return meshEntries[0]->mesh;
}
