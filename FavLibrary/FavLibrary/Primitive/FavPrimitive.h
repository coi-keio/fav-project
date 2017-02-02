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
    void setId(unsigned int id_){ identifier = id_; };
	std::string getName() { return name; };
	void setName(std::string name_) { name = name_; };

protected:
	unsigned int identifier;
	std::string name;

private:
	bool is_removed = false;
};

