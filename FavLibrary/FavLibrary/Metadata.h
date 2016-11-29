//
//  MetaData.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#ifndef __FavLibrary__MetaData__
#define __FavLibrary__MetaData__

#include <stdio.h>
#include <string>
#include <vector>

class Metadata{
    
public:
    Metadata(){};
    Metadata(int index, std::string title, std::string author, std::string license)
    {
        this->index = index;
        this->title = title;
        this->author = author;
        this->license = license;
    
    };
    
    int getId();
    std::string getTitle(){ return title; };
    std::string getAuthor(){ return author; };
    std::string getLicense(){ return license; };
    std::string getNote(){ return note; };
    
    void setId(int index_){ index = index_; };
    void setTitle(std::string title_){ title = title_; };
    void setAuthor(std::string author_){ author = author_; };
    void setLicense(std::string license_){ license = license_; };
    void setNote(std::string note_){ note = note_; };
    
private:
    int index;
    std::string title;
    std::string author;
    std::string license;
    std::string note;
};

#endif /* defined(__FavLibrary__MetaData__) */
