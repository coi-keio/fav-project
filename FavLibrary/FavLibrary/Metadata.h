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
#include "FavSettings.h"

namespace FavLibrary
{
	RefClass Metadata {

	public:
		Metadata();
		Metadata(int identifier_, std::string title_, std::string author_, std::string license_);

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

	private:
		std::string identifier;
		std::string title;
		std::string author;
		std::string license;
		std::string note;
	};

	RefClass MetadataObject
	{
	public:
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
#endif /* defined(__FavLibrary__MetaData__) */
