### paths ###
set(INCLUDE_DIR include)
set(SOURCE_DIR src)

set(CORE_INCLUDE_DIR			${INCLUDE_DIR}/TXPK/Core)
set(EXPORTERS_INCLUDE_DIR		${INCLUDE_DIR}/TXPK/Exporters)
set(FILESYSTEM_INCLUDE_DIR		${INCLUDE_DIR}/TXPK/FileSystem)
set(KEYCONVERTERS_INCLUDE_DIR	${INCLUDE_DIR}/TXPK/KeyConverters)
set(MATH_INCLUDE_DIR			${INCLUDE_DIR}/TXPK/Math)
set(PACKERS_INCLUDE_DIR			${INCLUDE_DIR}/TXPK/Packers)

set(CORE_SOURCE_DIR				${SOURCE_DIR}/Core)
set(EXPORTERS_SOURCE_DIR		${SOURCE_DIR}/Exporters)
set(FILESYSTEM_SOURCE_DIR		${SOURCE_DIR}/FileSystem)
set(KEYCONVERTERS_SOURCE_DIR	${SOURCE_DIR}/KeyConverters)
set(MATH_SOURCE_DIR				${SOURCE_DIR}/Math)
set(PACKERS_SOURCE_DIR			${SOURCE_DIR}/Packers)


### headers ###
set(CORE_HEADERS
	${CORE_INCLUDE_DIR}/Common.hpp
	${CORE_INCLUDE_DIR}/Color.hpp
	${CORE_INCLUDE_DIR}/Bin.hpp
	${CORE_INCLUDE_DIR}/FitResult.hpp
	${CORE_INCLUDE_DIR}/Rectangle.hpp
	${CORE_INCLUDE_DIR}/Margin.hpp
	${CORE_INCLUDE_DIR}/Texture.hpp
	${CORE_INCLUDE_DIR}/SizeConstraintType.hpp
	${CORE_INCLUDE_DIR}/IPacker.hpp
	${CORE_INCLUDE_DIR}/IDataExporter.hpp
	${CORE_INCLUDE_DIR}/IKeyConverter.hpp
	${CORE_INCLUDE_DIR}/Comparison.hpp
	${CORE_INCLUDE_DIR}/Comparison.inl
	${CORE_INCLUDE_DIR}/VectorExtension.hpp
	${CORE_INCLUDE_DIR}/VectorExtension.inl
	${CORE_INCLUDE_DIR}/RectangleMerger.hpp
	${CORE_INCLUDE_DIR}/StringExtension.hpp
	${CORE_INCLUDE_DIR}/Project.hpp
	${CORE_INCLUDE_DIR}/ServiceLocator.hpp
)

set(EXPORTERS_HEADERS
	${EXPORTERS_INCLUDE_DIR}/JsonExporter.hpp
	${EXPORTERS_INCLUDE_DIR}/MultiExporter.hpp
	${EXPORTERS_INCLUDE_DIR}/LuaExporter.hpp
	${EXPORTERS_INCLUDE_DIR}/CppHeaderExporter.hpp
)

set(FILESYSTEM_HEADERS
	${FILESYSTEM_INCLUDE_DIR}/FileSystem.hpp
	${FILESYSTEM_INCLUDE_DIR}/FileNode.hpp
)

set(KEYCONVERTERS_HEADERS
	${KEYCONVERTERS_INCLUDE_DIR}/FileWithoutExtConverter.hpp
	${KEYCONVERTERS_INCLUDE_DIR}/RegexConverter.hpp
	${KEYCONVERTERS_INCLUDE_DIR}/LuaConverter.hpp
	${KEYCONVERTERS_INCLUDE_DIR}/EnumeratorConverter.hpp
)

set(MATH_HEADERS
	${MATH_INCLUDE_DIR}/MathExtension.hpp
)

set(PACKERS_HEADERS
	${PACKERS_INCLUDE_DIR}/SameSizePacker.hpp
	${PACKERS_INCLUDE_DIR}/BlackspawnPacker.hpp
)

set(HEADERS
	${CORE_HEADERS}
	${EXPORTERS_HEADERS}
	${FILESYSTEM_HEADERS}
	${KEYCONVERTERS_HEADERS}
	${MATH_HEADERS}
	${PACKERS_HEADERS}
)


### inlines ###
set(CORE_INLINES
	${CORE_INCLUDE_DIR}/Comparison.inl
	${CORE_INCLUDE_DIR}/Color.inl
	${CORE_INCLUDE_DIR}/Rectangle.inl
	${CORE_INCLUDE_DIR}/Texture.inl
	${CORE_INCLUDE_DIR}/VectorExtension.inl
	${CORE_INCLUDE_DIR}/StringExtension.inl
	${CORE_INCLUDE_DIR}/ServiceLocator.inl
)

set(EXPORTERS_INLINES
)

set(FILESYSTEM_INLINES
)

set(KEYCONVERTERS_INLINES
)

set(MATH_INLINES
)

set(PACKERS_INLINES
)

set(INLINES
	${CORE_INLINES}
	${EXPORTERS_INLINES}
	${FILESYSTEM_INLINES}
	${KEYCONVERTERS_INLINES}
	${MATH_INLINES}
	${PACKERS_INLINES}
)


### sources ###
set(CORE_SOURCES
	${CORE_SOURCE_DIR}/Rectangle.cpp
	${CORE_SOURCE_DIR}/Margin.cpp
	${CORE_SOURCE_DIR}/Bin.cpp
	${CORE_SOURCE_DIR}/Texture.cpp
	${CORE_SOURCE_DIR}/RectangleMerger.cpp
	${CORE_SOURCE_DIR}/Project.cpp
	${CORE_SOURCE_DIR}/ServiceLocator.cpp
	${CORE_SOURCE_DIR}/StringExtension.cpp
)

set(EXPORTERS_SOURCES
	${EXPORTERS_SOURCE_DIR}/JsonExporter.cpp
	${EXPORTERS_SOURCE_DIR}/LuaExporter.cpp
	${EXPORTERS_SOURCE_DIR}/MultiExporter.cpp
	${EXPORTERS_SOURCE_DIR}/CppHeaderExporter.cpp
)

set(FILESYSTEM_SOURCES
	${FILESYSTEM_SOURCE_DIR}/FileSystem.cpp
	${FILESYSTEM_SOURCE_DIR}/FileNode.cpp
)

set(KEYCONVERTERS_SOURCES
	${KEYCONVERTERS_SOURCE_DIR}/FileWithoutExtConverter.cpp
	${KEYCONVERTERS_SOURCE_DIR}/RegexConverter.cpp
	${KEYCONVERTERS_SOURCE_DIR}/LuaConverter.cpp
	${KEYCONVERTERS_SOURCE_DIR}/EnumeratorConverter.cpp
)

set(MATH_SOURCES
	${MATH_SOURCE_DIR}/MathExtension.cpp
)

set(PACKERS_SOURCES
	${PACKERS_SOURCE_DIR}/SameSizePacker.cpp
	${PACKERS_SOURCE_DIR}/BlackspawnPacker.cpp
)

set(SOURCES
	${CORE_SOURCES}
	${EXPORTERS_SOURCES}
	${FILESYSTEM_SOURCES}
	${KEYCONVERTERS_SOURCES}
	${MATH_SOURCES}
	${PACKERS_SOURCES}
)

add_library(${ENGINE_NAME} ${HEADERS} ${INLINES} ${SOURCES})
target_include_directories(${ENGINE_NAME} PUBLIC ${INCLUDE_DIR} ${LUA_INCLUDE_DIR})
target_link_libraries(${ENGINE_NAME} json)
target_link_libraries(${ENGINE_NAME} dirent)
target_link_libraries(${ENGINE_NAME} stb_image)
target_link_libraries(${ENGINE_NAME} ${LUA_LIBRARIES})
