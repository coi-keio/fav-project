cmake_minimum_required(VERSION 2.8)

#find_package(GLUT)
#find_package(OpenGL)
#find_package(OpenMP)
#add_definitions("-std=c++11")
include_directories(/usr/local/Cellar/xerces-c/3.1.4/include/)
link_directories(/usr/local/Cellar/xerces-c/3.1.4/lib/)
set(XercesLib xerces-c)
set(CMAKE_CXX_FLAGS "-std=c++11 -g -o3 -Wall")
#set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_executable(Main
	./FavLibrary/main.cpp
	./FavLibrary/Fav.cpp
	./FavLibrary/Primitive/Color.cpp
	./FavLibrary/Primitive/FavPrimitive.cpp
	./FavLibrary/Primitive/Point3D.cpp
	./FavLibrary/Primitive/Vector3D.cpp
	./FavLibrary/Object/Object.cpp
	./FavLibrary/Object/Grid.cpp
	./FavLibrary/Object/Structure.cpp
	./FavLibrary/Palette/Geometry.cpp
	./FavLibrary/Palette/Material.cpp
	./FavLibrary/Palette/Palette.cpp
	./FavLibrary/Voxel.cpp	
	./FavLibrary/Metadata.cpp
	./FavLibrary/FavWriter.cpp
	./FavLibrary/FavReader.cpp
)
target_link_libraries(Main ${XercesLib})
