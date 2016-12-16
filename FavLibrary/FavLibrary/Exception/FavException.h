#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>

enum FavExceptionCode
{
	Undefined,
	// •‰‚Ì”‚Íw’è‚Å‚«‚Ü‚¹‚ñD
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

