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
	Metadata() {};
    Metadata(int identifier_, std::string title_, std::string author_, std::string license_)
    {
        identifier = identifier_;
        title = title_;
        author = author_;
        license = license_;
    };
    
	std::string getId() { return identifier; };
	void setId(std::string identifier_) { identifier = identifier_; };
	
	std::string getTitle(){ return title; };
	void setTitle(std::string title_) { title = title_; };
	
	std::string getAuthor(){ return author; };
	void setAuthor(std::string author_) { author = author_; };
	
	std::string getLicense(){ return license; };
	void setLicense(std::string license_) { license = license_; };
	
	std::string getNote(){ return note; };
    void setNote(std::string note_){ note = note_; };
    
private:
	std::string identifier;
    std::string title;
    std::string author;
    std::string license;
    std::string note;
};

class MetadataObject
{
public:
	Metadata getMetadata() { return metadata; };
	void setMetadata(Metadata metadata_) {
		metadata.setId(metadata_.getId());
		metadata.setAuthor(metadata_.getAuthor());
		metadata.setTitle(metadata_.getTitle());
		metadata.setLicense(metadata_.getLicense());
		metadata.setNote(metadata_.getNote());
	};

	std::string getMetadataId() { return metadata.getId(); };
	void setMetadataId(std::string id_) { metadata.setId(id_); };

	std::string getMetadataAuthor() { return metadata.getAuthor(); };
	void setMetadataAuthor(std::string author_) { metadata.setAuthor(author_); };

	std::string getMetadataTitle() { return metadata.getTitle(); };
	void setMetadataTitle(std::string title_) { metadata.setTitle(title_); };

	std::string getMetadataLicense() { return metadata.getLicense(); };
	void setMetadataLicense(std::string license_) { metadata.setLicense(license_); };

	std::string getMetadataNote() { return metadata.getNote(); };
	void setMetadataNote(std::string note_) { metadata.setNote(note_); };

private:
	Metadata metadata;
};

#endif /* defined(__FavLibrary__MetaData__) */
