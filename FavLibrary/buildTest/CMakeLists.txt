cmake_minimum_required(VERSION 2.8)

#find_package(GLUT)
#find_package(OpenGL)
#find_package(OpenMP)
#add_definitions("-std=c++11")
#include_directories(/usr/local/Cellar/xerces-c/3.1.4/include/)
#link_directories(/usr/local/Cellar/xerces-c/3.1.4/lib/)

#include_directories(/Users/atsmsmr/Documents/Developer/fav-project/FavLibrary/FavLibrary/)
#link_directories(/Users/atsmsmr/Documents/Developer/fav-project/FavLibrary/buildLib/build/)

# Directory settings for Docker
include_directories(/usr/local/fav/FavLibrary/FavLibrary/)
link_directories(/usr/local/fav/FavLibrary/buildLib/build/)

#set(XercesLib xerces-c)
set(CMAKE_CXX_FLAGS "-std=c++1y -g -O3 -Wall")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")

add_executable(a.out
	./testDLL.cpp
)

add_executable(reader
	./testReader.cpp
)

add_executable(writer
	./testWriter.cpp
)

#target_link_libraries(a.out fav ${XercesLib})
target_link_libraries(a.out fav)
target_link_libraries(reader fav)
target_link_libraries(writer fav)
#ADD_LIBRARY(fav SHARED)
