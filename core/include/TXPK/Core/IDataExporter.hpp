#pragma once

#include <memory>
#include <vector>

#include "TXPK/Core/Bin.hpp"
#include "TXPK/Core/IKeyConverter.hpp"

namespace txpk
{
	/**
	* \brief Interface used by all DataExporter implementations.
	*/
	class IDataExporter
	{
	public:
		/**
		* \brief Pure virtual interface needs a virtual destructor.
		*/
		virtual ~IDataExporter() {}

		/**
		* \brief Exports any of the given data in the way the implementation is defined.
		* \param textures Vector with Texture pointers.
		* \param width Width of the packed image.
		* \param height Height of the packed image.
		* \param imagePath The path where the image was saved to.
		* \param outputDirectory The directory where to put the exported data at.
		* \param outputName The name for the exported data file.
		*/
		virtual void exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const = 0;
	};

	typedef std::shared_ptr<IDataExporter> DataExporterPtr;
}
