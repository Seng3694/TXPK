#pragma once

#include <vector>

#include "TXPK/Core/IDataExporter.hpp"

namespace txpk
{
	/**
	* \brief Exporter which does nothing but storing other exporters and invokes them all when executed.
	*/
	class MultiExporter : public IDataExporter
	{
	public:
		/**
		* \brief Adds an exporter which will be invoked when exportData is called.
		* \param exporter The exporter to add.
		*/
		void addExporter(DataExporterPtr exporter);
		void exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const override;

	private:
		std::vector<DataExporterPtr> dataExporters; /**< All the stored exporters which will be invoked */
	};
}
