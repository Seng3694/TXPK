#pragma once

#include <fstream>
#include <iostream>

#include "TXPK/Core/IDataExporter.hpp"
#include "TXPK/Core/Project.hpp"

namespace txpk
{
	/**
	* \brief Exporter that creates a json file and stores all relevant data in it.
	*/
	class JsonExporter : public IDataExporter
	{
	public:
		void exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const override;
	};
}
