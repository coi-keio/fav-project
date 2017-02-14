#pragma once

#include <string>

class FavPrimitive
{
public:
	FavPrimitive(unsigned int id_)
	{
		setId(id_);
	};
	FavPrimitive(std::string name_)
	{
		setName(name_);
	};
	FavPrimitive(unsigned int id_, std::string name_)
	{
		setId(id_);
		setName(name_);
	};

	bool isRemoved() { return this->is_removed; }
	void remove() { this->is_removed = true; }

	unsigned int getId() { return identifier; };
    void setId(unsigned int id_){ identifier = id_; };
	std::string getName() { return name; };
	void setName(std::string name_) { name = name_; };

protected:
	FavPrimitive();
	~FavPrimitive();

	unsigned int identifier;
	std::string name;

private:

	bool is_removed = false;
};
