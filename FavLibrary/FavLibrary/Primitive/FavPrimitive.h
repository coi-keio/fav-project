#pragma once

#include <string>

class FavPrimitive
{
public:
	FavPrimitive();
	~FavPrimitive();

	bool isRemoved() { return this->is_removed; }
	void remove() { this->is_removed = true; }

	unsigned int getId() { return identifier; };

	std::string getName() { return name; };
	void setName(std::string name_) { name = name_; };

protected:
	static unsigned int counter;
	unsigned int identifier;
	std::string name;

private:
	bool is_removed = false;
};

