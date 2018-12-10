if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	set(CONFIGURATION "x64")
else() 
	set(CONFIGURATION "x86")
endif() 

set(SFML_DIR "/home/seng/Downloads/SFML-2.5.1-linux-gcc-64-bit/SFML-2.5.1/lib/cmake/SFML")

set(INCLUDE_DIRS
	include
	../content/meta
)

set(HEADERS
	include/Atlas.hpp
	include/CustomSprite.hpp
	include/Texture.hpp
)

set(SOURCES
	src/Main.cpp
	src/Atlas.cpp
	src/CustomSprite.cpp
)

include_directories(${INCLUDE_DIRS})
add_executable(example ${HEADERS} ${SOURCES})
target_link_libraries(example nlohmann_json)
target_link_libraries(example ${ENGINE_NAME})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

if(SFML_FOUND)
   include_directories(${SFML_DIR}/include)
   target_link_libraries(example sfml-graphics)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/example/content)
	add_custom_command(
		TARGET example POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/example/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
