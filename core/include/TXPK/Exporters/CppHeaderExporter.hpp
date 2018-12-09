#pragma once

#include <string>
#include <map>
#include <fstream>
#include <iostream>

#include "TXPK/Core/IDataExporter.hpp"
#include "TXPK/Core/Project.hpp"
#include "TXPK/Core/StringExtension.hpp"
#include "TXPK/FileSystem/FileSystem.hpp"

namespace txpk
{
	/**
	* \brief Exporter that creates a C++ header file and defines a key for each texture.
	*/
	class CppHeaderExporter : public IDataExporter
	{
	public:
		void exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const override;
	};
}
