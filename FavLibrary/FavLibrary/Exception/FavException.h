#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>

enum FavExceptionCode
{
	Undefined,
	// 負の数は指定できません．
	NegativeValueRejected,

};

class FavException : public std::exception
{
protected:
	std::exception innerException;
	std::string message;
	FavExceptionCode code;
};

class FavInvalidArgumentException : public FavException, std::invalid_argument
{
public:
};

