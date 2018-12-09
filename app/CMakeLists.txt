set(INCLUDE_DIR
	include
)

set(HEADERS
	
)

set(SOURCES
	src/Main.cpp
)

include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${ENGINE_NAME})
target_link_libraries(${PROJECT_NAME} CLI)
