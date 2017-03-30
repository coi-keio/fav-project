#pragma once

#include <string>

#include "../FavSettings.h"

namespace FavLibrary
{
	class IDll FavPrimitive
	{
	public:
		FavPrimitive(unsigned int id_);
		FavPrimitive(std::string name_);
		FavPrimitive(unsigned int id_, std::string name_);

		bool isRemoved();
		void remove();

		unsigned int getId();
		void setId(unsigned int id_);
		std::string getName();
		void setName(std::string name_);

	protected:
		FavPrimitive();
		virtual ~FavPrimitive();

		unsigned int identifier;
		std::string name;

	private:

		bool is_removed = false;
	};

}