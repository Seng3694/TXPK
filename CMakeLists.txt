cmake_minimum_required(VERSION 3.5)

project (TexturePacker)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_STANDARD 14)

if(WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(SFML_ROOT "C:/Program Files (x86)/SFML")

set(INCLUDE_DIRS
    include
)

set(SOURCES
	src/Main.cpp
	src/Rectangle.cpp
	src/Node.cpp
	src/Packer.cpp
	src/TextureInfo.cpp
	src/JsonConverter.cpp
	src/ImageRenderer.cpp
	src/MathHelper.cpp
)

include_directories(${INCLUDE_DIRS})

add_executable(${PROJECT_NAME} ${SOURCES})

find_package(SFML 2 REQUIRED graphics window audio system)

if(SFML_FOUND)
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( ${PROJECT_NAME}  ${SFML_LIBRARIES} )
	target_link_libraries( ${PROJECT_NAME}  ${SFML_DEPENDENCIES} )
endif()
