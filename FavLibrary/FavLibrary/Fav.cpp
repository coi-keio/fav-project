//
//  Object.h
//  FavLibrary
//
//  Created by Atsushi Masumori on 2016/09/15.
//  Copyright (c) 2016 Atsushi Masumori. All rights reserved.
//

#include "Fav.h"
#include "FavWriter.h"

Fav::Fav(){

}

Fav::~Fav(){
//    delete metadata;
}

bool Fav::read(const char* file_path){

    fav_reader = new FavReader(this);
    fav_reader->read(file_path);
    delete fav_reader;
    
    return 1;
}

bool Fav::write(const char* file_path){
    
    fav_writer = new FavWriter(this);
    fav_writer->write(file_path);
    delete fav_writer;
    
    return 1;
}