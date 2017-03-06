#pragma once

#ifdef FavLibraryExport
#define DllExport extern "C" __declspec(dllexport) 
#else
#define DllExport __declspec(dllimport) 
#endif 

