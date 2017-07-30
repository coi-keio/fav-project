#include "FavPrimitive.h"

namespace FavLibrary
{
	FavPrimitive::FavPrimitive() {}
	FavPrimitive::~FavPrimitive() {}

	FavPrimitive::FavPrimitive(unsigned int id_)
	{
		setId(id_);
	};
	FavPrimitive::FavPrimitive(std::string name_)
	{
		setName(name_);
	};
	FavPrimitive::FavPrimitive(unsigned int id_, std::string name_)
	{
		setId(id_);
		setName(name_);
	};

	unsigned int FavPrimitive::getId() { return identifier; };
	void FavPrimitive::setId(unsigned int id_) { identifier = id_; };
	std::string FavPrimitive::getName() { return name; };
	void FavPrimitive::setName(std::string name_) { name = name_; };
}
