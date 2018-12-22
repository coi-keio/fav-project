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

		unsigned int getId() const ;
		void setId(unsigned int id_);
		std::string getName() const ;
		void setName(std::string name_);

	protected:
		FavPrimitive();
		virtual ~FavPrimitive();

		unsigned int identifier;
		std::string name;

	private:
	};

}