cmake_minimum_required(VERSION 3.5)

project (TexturePacker)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/modules/")
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(app)
add_subdirectory(example)