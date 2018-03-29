set(SFML_ROOT "C:/Program Files (x86)/SFML")

if(WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

set(INCLUDE_DIRS
    include
)

set(SOURCES
	src/Main.cpp
	src/Animation.cpp
	src/Atlas.cpp
	src/AnimatedSprite.cpp
)

include_directories(${INCLUDE_DIRS})

add_executable(Example ${SOURCES})

find_package(SFML 2 REQUIRED graphics window audio system)

if(SFML_FOUND)
	include_directories( ${SFML_INCLUDE_DIR} )
	target_link_libraries( Example  ${SFML_LIBRARIES} )
	target_link_libraries( Example  ${SFML_DEPENDENCIES} )
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/example/content)
	add_custom_command(
		TARGET Example POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/example/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()