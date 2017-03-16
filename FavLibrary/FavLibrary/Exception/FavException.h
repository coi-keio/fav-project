#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>
#include "../FavSettings.h"

namespace FavLibrary
{
	enum RefClass DllInterface FavExceptionCode
	{
		Undefined,
		// ���̐��͎w��ł��܂���D
		NegativeValueRejected,

	};

	RefClass DllInterface FavException : public std::exception
	{
	protected:
		std::exception innerException;
		std::string message;
		FavExceptionCode code;
	};

	RefClass DllInterface FavInvalidArgumentException : public FavException, std::invalid_argument
	{
	public:
	};

}