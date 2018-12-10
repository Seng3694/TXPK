#pragma once

#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>

#include <nlohmann/json.hpp>

#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/IDataExporter.hpp"
#include "TXPK/Core/IKeyConverter.hpp"
#include "TXPK/Core/IPacker.hpp"
#include "TXPK/Core/RectangleMerger.hpp"
#include "TXPK/Core/ServiceLocator.hpp"
#include "TXPK/Core/StringExtension.hpp"
#include "TXPK/Exporters/JsonExporter.hpp"
#include "TXPK/Exporters/LuaExporter.hpp"
#include "TXPK/Exporters/MultiExporter.hpp"
#include "TXPK/Exporters/CppHeaderExporter.hpp"
#include "TXPK/FileSystem/FileSystem.hpp"
#include "TXPK/KeyConverters/EnumeratorConverter.hpp"
#include "TXPK/KeyConverters/FileWithoutExtConverter.hpp"
#include "TXPK/KeyConverters/LuaConverter.hpp"
#include "TXPK/KeyConverters/RegexConverter.hpp"
#include "TXPK/Packers/BlackspawnPacker.hpp"
#include "TXPK/Packers/SameSizePacker.hpp"

namespace txpk
{
	/**
	* \brief The project will report errors in form of these error codes.
	*/
	enum class ErrorCodes
	{
		Success							  = 0, /**< No errors occured */
										  
		//load errors					  
		ProjectFileNotFound				  = 1 << 0, /**< The project file was not found */
		InvalidProjectFile				  = 1 << 1, /**< The project file has an invalid format */
		DataExportAlgorithmNotFound		  = 1 << 2, /**< The given data export algorithm was not found */
		PackerAlgorithmNotFound			  = 1 << 3, /**< The given packing algorithm was not found */
		KeyConversionAlgorithmNotFound	  = 1 << 4, /**< The given key conversion algorithm was not found */
										  
		//validation errors				  
		InputDirectoryNotFound			  = 1 << 5, /**< The given input directory was not found */
		OutputDirectoryNotFound			  = 1 << 6, /**< The given output directory was not found */
		OutputNameInvalidCharacters		  = 1 << 7, /**< The given output file name has invalid characters */
		InvalidOutputFormat				  = 1 << 8, /**< The given output image format is not supported */
										  
		//save errors					  
		SaveDirectoryNotFound			  = 1 << 9, /**< The given save directory was not found */
		InvalidProjectName			      = 1 << 10, /**< The given project name is invalid */
		CouldNotCreateProjectFile		  = 1 << 11, /**< Project could not be created */

		//run errors
		InputDirectoryDoesNotContainFiles = 1 << 12, /**< The given input directory does not contain any files */
		FailedToLoadFile				  = 1 << 13, /**< Failed to load any file in the input directory */
		CouldNotCreatePackedTexture		  = 1 << 14, /**< Packed texture could not be created */
		PackerGotInvalidTextures		  = 1 << 15	 /**< Packer got invalid textures/parameters */
	};

	GENERATE_FLAGS_OPERATORS(ErrorCodes)

	/**
	* \brief The project class.
	*/
	class Project
	{
		typedef std::function<DataExporterPtr(void)>	DataExporterCreator;
		typedef std::function<PackerPtr(void)>			PackerCreator;
		typedef std::function<KeyConverterPtr(void)>	KeyConverterCreator;

		typedef std::map<std::string, DataExporterCreator>	DataExporterCreatorMap;
		typedef std::map<std::string, PackerCreator>		PackerCreatorMap;
		typedef std::map<std::string, KeyConverterCreator>	KeyConverterCreatorMap;

	public:
		/**
		* \brief Default constructor.
		*/
		Project();

		std::string name; /**< The project name */

		bool recursiveFiles; /**< Whether files should be searched recursively or not */
		std::string inputDirectory; /**< The input directory to search for files */
		std::string inputRegex; /**< The regular expression to filter files */
		std::string scriptDirectory; /**< The directory where any script file is. Will be done recursively automatically */
		std::string outputImageDirectory; /**< The directory where the output image will be saved to */
		std::string outputDataDirectory; /**< The directory where any output data will be saved to */
		std::string outputName; /**< The name how any output file will be named */
		std::string outputImageFormat; /**< The output image format */

		std::string packingAlgorithm; /**< The texture packing algorithm */
		std::vector<std::string> dataExportAlgorithms; /**< The export algorithms */
		std::string keyConversionAlgorithm; /**< The key conversion algorithms */

		bool allowRotation; /**< Whether packers are allowed to rotate images or not */
		uint32 sizeConstraint; /**< Constraint to width or height */
		SizeContraintType constraintType; /**< Constraint type. None, width or height */
		Color4 clearColor; /**< Color to clear the resulting image with */
		bool trimImages; /**< Whether the images should be trimmed or not */
		bool replaceSameTextures; /**< Whether to remove redundant textures or not */

		/**
		* \brief Returns all registered data exporter names.
		* \return Returns a vector of strings which are representing the data exporter names
		*/
		std::vector<std::string> getRegisteredDataExporters() const;
		/**
		* \brief Returns all registered key converter names.
		* \return Returns a vector of strings which are representing the key converter names
		*/
		std::vector<std::string> getRegisteredKeyConverters() const;
		/**
		* \brief Returns all registered packer names.
		* \return Returns a vector of strings which are representing the packer names
		*/
		std::vector<std::string> getRegisteredPackers() const;

		/**
		* \brief Loads a project file from the given path.
		* \param path The path to load the project from.
		* \return Returns an error code whether the loading process was successful or not.
		*/
		ErrorCodes load(const std::string& path);

		/**
		* \brief Saves a project to the project names path.
		* \return Returns an error code whether the saving process was successful or not.
		*/
		ErrorCodes save();

		/**
		* \brief Runs the whole texture packing process.
		* \return Returns an error code whether the run process was successful or not.
		*/
		ErrorCodes run() const;

	private:
		DataExporterCreatorMap dataExporters; /**< The data exporter creation delegates */
		KeyConverterCreatorMap keyConverters; /**< The key converter creation delegates */
		PackerCreatorMap packers; /**< The packer creation delegates */

		/**
		* \brief Validates whether the parameters are valid for running or not.
		* \return Returns an error code whether the parameters are valid or not.
		*/
		ErrorCodes validate();
	};
}
