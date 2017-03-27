#pragma once

namespace FavLibraryDotNet
{
	interface class IFavPrimitive
	{
	public:
		property bool IsRemoved { bool get(); }
		void Remove();

		property unsigned int ID { unsigned int get(); void set(unsigned int value); }
		property System::String^ Name { System::String^ get(); void set(System::String^ value); }
	};

}