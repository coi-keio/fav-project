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
		// 負の数は指定できません．
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