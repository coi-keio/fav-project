#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>


namespace FavLibrary
{
	enum class __declspec(dllexport) FavExceptionCode
	{
		Undefined,
		// 負の数は指定できません．
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