set(INCLUDE_DIR
	include
)

set(HEADERS
	include/json.hpp
)

set(SOURCES
	src/json.cpp
)

include_directories(${INCLUDE_DIR})
add_library(json ${HEADERS} ${SOURCES})
target_include_directories(json PUBLIC ${INCLUDE_DIR})
