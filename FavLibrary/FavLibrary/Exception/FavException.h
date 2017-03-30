#pragma once

#include <stdio.h>
#include <exception>
#include <stdexcept>

#include "../FavSettings.h"

namespace FavLibrary
{
	enum class IDll FavExceptionCode
	{
		Undefined,
		// •‰‚Ì”‚Íw’è‚Å‚«‚Ü‚¹‚ñD
		NegativeValueRejected,

	};

	class IDll FavException : public std::exception
	{
	protected:
		std::exception innerException;
		std::string message;
		FavExceptionCode code;
	};

	class IDll FavInvalidArgumentException : public FavException, std::invalid_argument
	{
	public:
	};

}