cmake_minimum_required(VERSION 3.5)

set(CMAKE_CXX_STANDARD 14)

project (TXPK)
set(ENGINE_NAME TXPKCore)

add_subdirectory(ext)
add_subdirectory(core)

if(BUILD_TXPK_TESTS)
	add_subdirectory(tests)
endif()

add_subdirectory(app)

if(BUILD_TXPK_EXAMPLE)
	add_subdirectory(example)
endif()
