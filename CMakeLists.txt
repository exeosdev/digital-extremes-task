
cmake_minimum_required( VERSION 3.10 )

set( CMAKE_C_STANDARD 11 )
set( CMAKE_C_STANDARD_REQUIRED ON )
set( CMAKE_C_EXTENSIONS OFF )

set( CMAKE_CXX_STANDARD 17 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

project( PathFinder )

set( SRC_FILES
		Armor.h
		Health.h
		PathNode.h
		PathNode.cpp
		PowerUp.h
		Vertex.h
		Weapon.h

		Main.cpp)

add_executable( PathFinder
        ${SRC_FILES} )

set_target_properties( PathFinder PROPERTIES
        OUTPUT_NAME "path-finder" )

target_include_directories( PathFinder PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR} )
