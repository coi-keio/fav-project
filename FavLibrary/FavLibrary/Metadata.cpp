//
//  MetaData.cpp
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//
#pragma once
#include "Metadata.h"


namespace FavLibrary
{
	Metadata::Metadata() {};
	Metadata::Metadata(std::string identifier_, std::string title_, std::string author_, std::string license_)
	{
		identifier = identifier_;
		title = title_;
		author = author_;
		license = license_;
	};
	Metadata::~Metadata() {};

	std::string Metadata::getId() { return identifier; };
	void Metadata::setId(std::string identifier_) { identifier = identifier_; };

	std::string Metadata::getTitle() { return title; };
	void Metadata::setTitle(std::string title_) { title = title_; };

	std::string Metadata::getAuthor() { return author; };
	void Metadata::setAuthor(std::string author_) { author = author_; };

	std::string Metadata::getLicense() { return license; };
	void Metadata::setLicense(std::string license_) { license = license_; };

	std::string Metadata::getNote() { return note; };
	void Metadata::setNote(std::string note_) { note = note_; };

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	MetadataObject::MetadataObject()  {  }
	MetadataObject::~MetadataObject() {  }

	std::string MetadataObject::getMetadataId() { return metadata.getId(); };
	void MetadataObject::setMetadataId(std::string id_) { metadata.setId(id_); };

	std::string MetadataObject::getMetadataAuthor() { return metadata.getAuthor(); };
	void MetadataObject::setMetadataAuthor(std::string author_) { metadata.setAuthor(author_); };

	std::string MetadataObject::getMetadataTitle() { return metadata.getTitle(); };
	void MetadataObject::setMetadataTitle(std::string title_) { metadata.setTitle(title_); };

	std::string MetadataObject::getMetadataLicense() { return metadata.getLicense(); };
	void MetadataObject::setMetadataLicense(std::string license_) { metadata.setLicense(license_); };

	std::string MetadataObject::getMetadataNote() { return metadata.getNote(); };
	void MetadataObject::setMetadataNote(std::string note_) { metadata.setNote(note_); };

}