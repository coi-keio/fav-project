#pragma once
#include "Stdafx.h"
#include "MetaData.h"

namespace FavLibraryDotNet
{
	//Metadata::Metadata() { pMetadata = new FavLibrary::Metadata(); }
	//Metadata::Metadata(System::String^ identifier_, System::String^ title_, System::String^ author_, System::String^ license_)
	//{
	//	pMetadata = new FavLibrary::Metadata(
	//		marshal_as<std::string>(identifier_),
	//		marshal_as<std::string>(title_),
	//		marshal_as<std::string>(author_),
	//		marshal_as<std::string>(license_)
	//	);
	//}
	//Metadata::Metadata(FavLibrary::Metadata* metadata) 
	//{
	//	pMetadata = metadata;
	//}
	//Metadata::~Metadata() { delete pMetadata; }
	Metadata::Metadata() {}
	Metadata::~Metadata() {}

	//System::String^ Metadata::ID::get() { marshal_as<System::String^>(pMetadata->getId()); }
	//void Metadata::ID::set(System::String^ value) { pMetadata->setId(marshal_as<std::string>(value)); }

	//System::String^ Metadata::Title::get() { marshal_as<System::String^>(pMetadata->getTitle()); }
	//void Metadata::Title::set(System::String^ value) { pMetadata->setTitle(marshal_as<std::string>(value)); }

	//System::String^ Metadata::Author::get() { marshal_as<System::String^>(pMetadata->getAuthor()); }
	//void Metadata::Author::set(System::String^ value) { pMetadata->setAuthor(marshal_as<std::string>(value)); }

	//System::String^ Metadata::License::get() { marshal_as<System::String^>(pMetadata->getLicense()); }
	//void Metadata::License::set(System::String^ value) { pMetadata->setLicense(marshal_as<std::string>(value)); }

	//System::String^ Metadata::Note::get() { marshal_as<System::String^>(pMetadata->getNote()); }
	//void Metadata::Note::set(System::String^ value) { pMetadata->setNote(marshal_as<std::string>(value)); }

}