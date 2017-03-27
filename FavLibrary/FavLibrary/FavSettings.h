#pragma once
//
//#ifdef DotNet ////////////////////////////////////////////////////////////////////////////////////////
//
//#define enum class __declspec(dllexport) public enum class
//#define class __declspec(dllexport) public ref class
////#define 
//
//#else ////////////////////////////////////////////////////////////////////////////////////////////////
//
//#define enum class __declspec(dllexport) enum class __declspec(dllexport) 
//#define class __declspec(dllexport) class __declspec(dllexport) 
//
////#ifdef FavLibraryExport
////#define __declspec(dllexport) 
////#else
////#define __declspec(dllimport) 
////#endif 
//
//#endif  //////////////////////////////////////////////////////////////////////////////////////////////

namespace FavLibrary
{
	enum class __declspec(dllexport) CompressionMode
    {
        none,
        base64,
        zlib
    };
}