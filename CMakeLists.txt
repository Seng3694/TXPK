cmake_minimum_required(VERSION 3.5)

project (TXPK)
set(ENGINE_NAME TXPKCore)

if(CMAKE_SIZEOF_VOID_P EQUAL 8) 
	set(CONFIGURATION "x64")
else() 
	set(CONFIGURATION "x86")
endif() 

set(LUA_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/ext/LuaJIT/include")
set(LUA_LIBRARIES "${CMAKE_SOURCE_DIR}/ext/LuaJIT/lib/${CONFIGURATION}/lua51_s.lib")

add_subdirectory(ext)
add_subdirectory(core)
add_subdirectory(tests)
add_subdirectory(app)
add_subdirectory(example)