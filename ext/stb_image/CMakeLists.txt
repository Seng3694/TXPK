set(INCLUDE_DIR
	include
)

set(HEADERS
	include/stb_image.h
	include/stb_image_write.h
)

set(SOURCES
	src/stb_image.cpp
)

include_directories(${INCLUDE_DIR})
add_library(stb_image ${HEADERS} ${SOURCES})
target_include_directories(stb_image PUBLIC ${INCLUDE_DIR})
