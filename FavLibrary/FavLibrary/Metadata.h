//
//  MetaData.h
//  FavLibrary
//
//  Created by atsmsmr on 2016/11/14.
//  Copyright (c) 2016年 Atsushi Masumori. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <vector>

#include "FavSettings.h"

namespace FavLibrary
{
	class IDll Metadata {

	public:
		Metadata();
		Metadata(std::string identifier_, std::string title_, std::string author_, std::string license_);
		virtual ~Metadata();

		std::string getId();
		void setId(std::string identifier_);

		std::string getTitle();
		void setTitle(std::string title_);

		std::string getAuthor();
		void setAuthor(std::string author_);

		std::string getLicense();
		void setLicense(std::string license_);

		std::string getNote();
		void setNote(std::string note_);

	protected:
		std::string identifier;
		std::string title;
		std::string author;
		std::string license;
		std::string note;
	};

	class IDll MetadataObject
	{
	public:
		MetadataObject();
		virtual ~MetadataObject();

		Metadata getMetadata();
		void setMetadata(Metadata metadata_);

		std::string getMetadataId();
		void setMetadataId(std::string id_);

		std::string getMetadataAuthor();
		void setMetadataAuthor(std::string author_);

		std::string getMetadataTitle();
		void setMetadataTitle(std::string title_);

		std::string getMetadataLicense();
		void setMetadataLicense(std::string license_);

		std::string getMetadataNote();
		void setMetadataNote(std::string note_);

	private:
		Metadata metadata;
	};

}