#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>
#include "../FavSettings.h"

namespace FavLibrary
{
	enum class DllInterface FavExceptionCode
	{
		Undefined,
		// ���̐��͎w��ł��܂���D
		NegativeValueRejected,

	};

	class DllInterface FavException : public std::exception
	{
	protected:
		std::exception innerException;
		std::string message;
		FavExceptionCode code;
	};

	class DllInterface FavInvalidArgumentException : public FavException, std::invalid_argument
	{
	public:
	};

}