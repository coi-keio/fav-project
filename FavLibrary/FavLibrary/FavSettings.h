#pragma once

#ifdef _WIN32  //////////////////////////////////////////////////////////////////////////////////////////////

//#define XERCES_STATIC_LIBRARY
#define IDll __declspec(dllexport)

#include <direct.h>
#define GetCurrentDir _getcwd

#else  /////////////////////////////////////////////////////////////////////////////////////////////////////

#define XERCES_STATIC_LIBRARY
#define IDll 

#include <unistd.h>
#define GetCurrentDir getcwd

#endif  ////////////////////////////////////////////////////////////////////////////////////////////////////

namespace FavLibrary
{
    enum class IDll CompressionMode
    {
        none,
        base64,
        zlib
    };
}