#ifdef FavLibraryExport
#define DllInterface __declspec(dllexport) 
#else
#define DllInterface __declspec(dllimport) 
#endif 
