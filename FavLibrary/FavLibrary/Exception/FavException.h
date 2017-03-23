#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>
#include "../FavSettings.h"

namespace FavLibrary
{
	enum class __declspec(dllexport) FavExceptionCode
	{
		Undefined,
		// ���̐��͎w��ł��܂���D
		NegativeValueRejected,

	};

	class __declspec(dllexport) FavException : public std::exception
	{
	protected:
		std::exception innerException;
		std::string message;
		FavExceptionCode code;
	};

	class __declspec(dllexport) FavInvalidArgumentException : public FavException, std::invalid_argument
	{
	public:
	};

}