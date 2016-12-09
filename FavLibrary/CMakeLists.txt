cmake_minimum_required(VERSION 2.8)

find_package(GLUT)
find_package(OpenGL)
find_package(OpenMP)
#add_definitions("-std=c++11")
include_directories(/usr/local/Cellar/xerces-c/3.1.4/include/)
link_directories(/usr/local/Cellar/xerces-c/3.1.4/lib/)
set(XercesLib xerces-c)
set(CMAKE_CXX_FLAGS "-std=c++1y -g -O3 -Wall")

add_executable(Main
	./FavLibrary/main.cpp
	./FavLibrary/Fav.cpp
	./FavLibrary/Object.cpp
	./FavLibrary/Voxel.cpp	
	./FavLibrary/Metadata.cpp
	./FavLibrary/Palette.cpp
	./FavLibrary/Structure.cpp
)
target_link_libraries(Main ${XercesLib})
