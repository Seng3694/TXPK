#include "TXPK/Exporters/MultiExporter.hpp"

namespace txpk
{
	void MultiExporter::addExporter(DataExporterPtr exporter)
	{
		dataExporters.push_back(exporter);
	}

	void MultiExporter::exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const
	{
		for (uint32 i = 0; i < static_cast<uint32>(dataExporters.size()); ++i)
			dataExporters[i]->exportData(textures, width, height, imagePath, outputDirectory, outputName);
	}
}
