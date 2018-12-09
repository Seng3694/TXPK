set(INCLUDE_DIR
	include
)

set(HEADERS
	include/dirent.h
)

set(SOURCES
	src/dirent.c
)

include_directories(${INCLUDE_DIR})
add_library(dirent ${HEADERS} ${SOURCES})
target_include_directories(dirent PUBLIC ${INCLUDE_DIR})
