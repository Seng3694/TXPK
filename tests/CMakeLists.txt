set(SOURCE_TEST_DIR src)

set(CORE_TEST_DIR ${SOURCE_TEST_DIR}/Core)
set(CORE_TEST_SOURCES
	${CORE_TEST_DIR}/BinTest.cpp
	${CORE_TEST_DIR}/ColorTest.cpp
	${CORE_TEST_DIR}/CommonTest.cpp
	${CORE_TEST_DIR}/ComparisonTest.cpp
	${CORE_TEST_DIR}/MarginTest.cpp
	${CORE_TEST_DIR}/ProjectTest.cpp
	${CORE_TEST_DIR}/RectangleMergerTest.cpp
	${CORE_TEST_DIR}/RectangleTest.cpp
	${CORE_TEST_DIR}/ServiceLocatorTest.cpp
	${CORE_TEST_DIR}/TextureTest.cpp
	${CORE_TEST_DIR}/VectorExtensionTest.cpp
)

set(EXPORTERS_TEST_DIR ${SOURCE_TEST_DIR}/Exporters)
set(EXPORTERS_TEST_SOURCES
	${EXPORTERS_TEST_DIR}/CppHeaderExporterTest.cpp
	${EXPORTERS_TEST_DIR}/JsonExporterTest.cpp
	${EXPORTERS_TEST_DIR}/LuaExporterTest.cpp
	${EXPORTERS_TEST_DIR}/MultiExporterTest.cpp
)

set(FILESYSTEM_TEST_DIR ${SOURCE_TEST_DIR}/FileSystem)
set(FILESYSTEM_TEST_SOURCES
	${FILESYSTEM_TEST_DIR}/FileNodeTest.cpp
	${FILESYSTEM_TEST_DIR}/FileSystemTest.cpp
)

set(KEYCONVERTERS_TEST_DIR ${SOURCE_TEST_DIR}/KeyConverters)
set(KEYCONVERTERS_TEST_SOURCES
	${KEYCONVERTERS_TEST_DIR}/EnumeratorConverterTest.cpp
	${KEYCONVERTERS_TEST_DIR}/FileWithoutExtConverterTest.cpp
	${KEYCONVERTERS_TEST_DIR}/RegexConverterTest.cpp
)

set(MATH_TEST_DIR ${SOURCE_TEST_DIR}/Math)
set(MATH_TEST_SOURCES
	${MATH_TEST_DIR}/MathExtensionsTest.cpp
)

set(PACKERS_TEST_DIR ${SOURCE_TEST_DIR}/Packers)
set(PACKERS_TEST_SOURCES
	${PACKERS_TEST_DIR}/BlackspawnPackerTest.cpp
	${PACKERS_TEST_DIR}/SameSizePacker.cpp
)

set(SOURCES
	${SOURCE_TEST_DIR}/Main.cpp
	${CORE_TEST_SOURCES}
	${EXPORTERS_TEST_SOURCES}
	${FILESYSTEM_TEST_SOURCES}
	${KEYCONVERTERS_TEST_SOURCES}
	${MATH_TEST_SOURCES}
	${PACKERS_TEST_SOURCES}
)

include_directories(${LUA_INCLUDE_DIR})
add_executable(tests ${SOURCES})

target_link_libraries(tests Catch2)
target_link_libraries(tests ${ENGINE_NAME})
target_link_libraries(tests nlohmann_json)

if(EXISTS ${CMAKE_SOURCE_DIR}/tests/content)
	add_custom_command(
		TARGET tests POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_directory
				${CMAKE_SOURCE_DIR}/tests/content
				${CMAKE_CURRENT_BINARY_DIR}/content
	)
endif()
