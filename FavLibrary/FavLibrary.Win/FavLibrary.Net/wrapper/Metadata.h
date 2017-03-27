#pragma once

#include "../../FavLibrary/Metadata.h"

namespace FavLibraryDotNet
{
	interface class IMetadata {

	public:
		property System::String^ ID { System::String^ get(); void set(System::String^ value); }
		property System::String^ Title { System::String^ get(); void set(System::String^ value); }
		property System::String^ Author { System::String^ get(); void set(System::String^ value); }
		property System::String^ License { System::String^ get(); void set(System::String^ value); }
		property System::String^ Note { System::String^ get(); void set(System::String^ value); }
	};

	public ref class Metadata /*: public IMetadata*/ {

	public:
		Metadata();
		//Metadata(System::String^ identifier_, System::String^ title_, System::String^ author_, System::String^ license_);
		~Metadata();

		//virtual property System::String^ ID { System::String^ get(); void set(System::String^ value); }
		//virtual property System::String^ Title { System::String^ get(); void set(System::String^ value); }
		//virtual property System::String^ Author { System::String^ get(); void set(System::String^ value); }
		//virtual property System::String^ License { System::String^ get(); void set(System::String^ value); }
		//virtual property System::String^ Note { System::String^ get(); void set(System::String^ value); }

	//internal:
	//	Metadata(FavLibrary::Metadata* metadata);

	//private:
	//	FavLibrary::Metadata* pMetadata;
	};
}
