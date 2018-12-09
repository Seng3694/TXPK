#include "TXPK/Core/Project.hpp"

namespace txpk
{
	Project::Project()
	{
		name = std::string();

		recursiveFiles = false;
		inputDirectory = std::string();
		inputRegex = std::string(".+((.png)|(.jpg)|(.jpeg))$");
		scriptDirectory = std::string();
		outputImageDirectory = std::string();
		outputDataDirectory = std::string();
		outputName = std::string("txpk_export");
		outputImageFormat = std::string("png");

		packingAlgorithm = std::string("Default");
		dataExportAlgorithms = { std::string("Default") };
		keyConversionAlgorithm = std::string("Default");

		allowRotation = false;
		sizeConstraint = 0;
		constraintType = SizeContraintType::None;
		clearColor = { 0,0,0,0 };
		trimImages = false; 
		replaceSameTextures = false;

		dataExporters = DataExporterCreatorMap();
		keyConverters = KeyConverterCreatorMap();
		packers = PackerCreatorMap();

		dataExporters[""] =				     []() { return static_cast<DataExporterPtr>(NULL); };
		packers[""] =					     []() { return static_cast<PackerPtr>(NULL); };
		keyConverters[""] =				     []() { return static_cast<KeyConverterPtr>(NULL); };
		dataExporters["Default"] =		     []() { return std::make_shared<JsonExporter>(); };
		dataExporters["CppHeader"] =		 []() { return std::make_shared<CppHeaderExporter>(); };
		packers["Default"] =			     []() { return std::make_shared<BlackspawnPacker>(); };
		keyConverters["Default"] =		     []() { return std::make_shared<FileWithoutExtConverter>(); };
		dataExporters["Json"] =			     []() { return std::make_shared<JsonExporter>(); };
		keyConverters["FileWithoutExt"] =    []() { return std::make_shared<FileWithoutExtConverter>(); };
		keyConverters["NumericRegex"] =      []() { return std::make_shared<RegexConverter>("[0-9]+"); };
		keyConverters["Enumerator"] =        []() { return std::make_shared<EnumeratorConverter>(); };
		packers["SameSize"] =			     []() { return std::make_shared<SameSizePacker>(); };
		packers["Blackspawn"] =			     []() { return std::make_shared<BlackspawnPacker>(); };
	}

	ErrorCodes Project::load(const std::string& path)
	{
		ErrorCodes code = ErrorCodes::Success;

		std::ifstream stream(path);

		if (stream.is_open())
		{
			nlohmann::json json;
			
			try
			{
				stream >> json;
			}
			catch (const nlohmann::json::exception&)
			{
				stream.close();
				return ErrorCodes::InvalidProjectFile;
			}

			name = path;

			recursiveFiles = json.at("recursiveFiles").get<bool>();

			inputDirectory = json.at("inputDirectory").get<std::string>();
			inputRegex = json.at("inputRegex").get<std::string>();
			scriptDirectory = json.at("scriptDirectory").get<std::string>();
			outputImageDirectory = json.at("outputImageDirectory").get<std::string>();
			outputDataDirectory = json.at("outputDataDirectory").get<std::string>();
			outputName = json.at("outputName").get<std::string>();
			outputImageFormat = json.at("outputImageFormat").get<std::string>();

			packingAlgorithm = json.at("packingAlgorithm").get<std::string>();
			dataExportAlgorithms = json.at("dataExportAlgorithms").get<std::vector<std::string>>();
			keyConversionAlgorithm = json.at("keyConversionAlgorithm").get<std::string>();

			allowRotation = json.at("allowRotation").get<bool>();
			sizeConstraint = json.at("sizeConstraint").get<uint32>();
			constraintType = json.at("constraintType").get<SizeContraintType>();


			std::string hexColor = json.at("clearColor").get<std::string>();
			int32 color = 0;
			if (stoi(color, hexColor.c_str(), 16) == ConversionResult::Success)
			{
				clearColor.data[0] = static_cast<uint8>(((static_cast<uint32>(color) & 0xff000000) >> 24));
				clearColor.data[1] = static_cast<uint8>(((static_cast<uint32>(color) & 0x00ff0000) >> 16));
				clearColor.data[2] = static_cast<uint8>(((static_cast<uint32>(color) & 0x0000ff00) >> 8));
				clearColor.data[3] = static_cast<uint8>(((static_cast<uint32>(color) & 0x000000ff) >> 0));
			}
			else
			{
				clearColor.data[0] = 0;
				clearColor.data[1] = 0;
				clearColor.data[2] = 0;
				clearColor.data[3] = 0;
			}

			trimImages = json.at("trimImages").get<bool>();
			replaceSameTextures = json.at("replaceSameTextures").get<bool>();
			stream.close();
		}
		else
		{
			return ErrorCodes::ProjectFileNotFound;
		}

		code |= validate();

		return code;
	}

	ErrorCodes Project::validate()
	{
		ErrorCodes codes = ErrorCodes::Success;

		const std::string workingDir = get_directory(name) + "/";

		if (!directory_exists(workingDir + inputDirectory))
			codes |= ErrorCodes::InputDirectoryNotFound;
		if (!directory_exists(workingDir + outputImageDirectory) || !directory_exists(workingDir + outputDataDirectory))
			codes |= ErrorCodes::OutputDirectoryNotFound;
		if (!name_is_valid(outputName))
			codes |= ErrorCodes::OutputNameInvalidCharacters;
		if (outputImageFormat != "png" && outputImageFormat != "jpg" && outputImageFormat != "jpeg")
			codes |= ErrorCodes::InvalidOutputFormat;

		if (directory_exists(workingDir + scriptDirectory))
		{
			typedef std::vector<std::shared_ptr<FileNode>> FileNodes;
			FileNodes luaFiles = get_files(workingDir + scriptDirectory, "^.+(.lua)$", true);

			for (uint32 i = 0; i < static_cast<uint32>(luaFiles.size()); ++i)
			{
				std::string path = luaFiles[i]->getFullPath();
				std::string name = get_file_name_without_ext(path);

				if (ends_with(path.c_str(), "Exporter.lua"))
				{
					auto itr = dataExporters.find(name);
					if (itr == dataExporters.end())
						dataExporters[name] = [=]() { return std::make_shared<LuaExporter>(LuaExporter(path)); };
				}
				else if (ends_with(path.c_str(), "KeyConverter.lua"))
				{
					auto itr = keyConverters.find(name);
					if (itr == keyConverters.end())
						keyConverters[name] = [=]() { return std::make_shared<LuaConverter>(LuaConverter(path)); };
				}
			}
		}
		
		if (packers.find(packingAlgorithm) == packers.end())
			codes |= ErrorCodes::PackerAlgorithmNotFound;

		for (uint32 i = 0; i < dataExportAlgorithms.size(); ++i)
		{
			if (dataExporters.find(dataExportAlgorithms[i]) == dataExporters.end())
				codes |= ErrorCodes::DataExportAlgorithmNotFound;
		}
		
		if (keyConverters.find(keyConversionAlgorithm) == keyConverters.end())
			codes |= ErrorCodes::KeyConversionAlgorithmNotFound;

		return codes;
	}

	ErrorCodes Project::run() const
	{
		typedef std::vector<std::shared_ptr<FileNode>> FileNodes;
		std::string workingDir;
		if(name != "")
			workingDir = get_directory(name) + "/";

		FileNodes files = get_files(workingDir + inputDirectory, inputRegex, recursiveFiles);

		if (files.size() == 0)
			return ErrorCodes::InputDirectoryDoesNotContainFiles;

		TexturePtrs textures;
		for (uint32 i = 0; i < static_cast<uint32>(files.size()); ++i)
		{
			Texture texture;
			if (!texture.loadFromFile(files[i]->getFullPath()))
				return ErrorCodes::FailedToLoadFile;

			if (trimImages)
				texture.trim();

			textures.push_back(std::make_unique<Texture>(texture));
		}

		RectanglePtrs rectangles;
		if (replaceSameTextures)
		{
			rectangles = merge_rectangles(textures);
		}
		else
		{
			rectangles.reserve(textures.size());
			for (uint32 i = 0; i < textures.size(); ++i)
				rectangles.push_back(textures[i]->getBounds());
		}

		const ServiceLocatorPtr locator = ServiceLocator::current();
		locator->registerInstance<IPacker>(packers.at(packingAlgorithm)());

		std::shared_ptr<MultiExporter> exporter = std::make_shared<MultiExporter>();
		for (uint32 i = 0; i < static_cast<uint32>(dataExportAlgorithms.size()); ++i)
			exporter->addExporter(dataExporters.at(dataExportAlgorithms[i])());

		locator->registerInstance<IDataExporter>(exporter);
		locator->registerInstance<IKeyConverter>(keyConverters.at(keyConversionAlgorithm)());

		PackerPtr packer = locator->resolve<IPacker>();
		if (packer == NULL)
			return ErrorCodes::Success;

		if (!packer->validate(rectangles, sizeConstraint, constraintType, allowRotation))
			return ErrorCodes::PackerGotInvalidTextures;

		Bin bin = packer->pack(rectangles, sizeConstraint, constraintType, allowRotation);

		//after packing rotate texture pixel data if rotation is allowed
		if (allowRotation)
		{
			for (uint32 i = 0; i < textures.size(); ++i)
				textures[i]->adjustRotation();
		}

		std::stringstream pathstream;
		pathstream << workingDir << outputImageDirectory << (outputImageDirectory == "" ? "" : "/") << outputName << "." << outputImageFormat;
		if (!bin.save(textures, clearColor, pathstream.str(), trimImages))
			return ErrorCodes::CouldNotCreatePackedTexture;

		std::sort(textures.begin(), textures.end(), [](const TexturePtr lhs, const TexturePtr rhs) 
		{
			return alphanumeric_compare()(lhs->getPath(), rhs->getPath());
		});

		pathstream.str("");
		pathstream << outputImageDirectory << (outputImageDirectory == "" ? "" : "/") << outputName << "." << outputImageFormat;
		DataExporterPtr dataExporter = locator->resolve<IDataExporter>();
		if(dataExporter != NULL)
			dataExporter->exportData(textures, bin.width, bin.height, pathstream.str(), outputDataDirectory, outputName);

		return ErrorCodes::Success;
	}

	ErrorCodes Project::save()
	{
		ErrorCodes codes = ErrorCodes::Success;

		if (name == "")
			return ErrorCodes::InvalidProjectName;

		if (!directory_exists(get_directory(name)))
			return ErrorCodes::SaveDirectoryNotFound;

		std::ofstream stream(name);

		if (stream.is_open())
		{
			stream << "{\n";
			stream << "\t\"recursiveFiles\" : " << (recursiveFiles ? "true" : "false") << ",\n";
			stream << "\t\"inputDirectory\" : \"" << inputDirectory << "\",\n";
			stream << "\t\"inputRegex\" : \"" << inputRegex << "\",\n";
			stream << "\t\"scriptDirectory\" : \"" << scriptDirectory << "\",\n";
			stream << "\t\"outputImageDirectory\" : \"" << outputImageDirectory << "\",\n";
			stream << "\t\"outputDataDirectory\" : \"" << outputDataDirectory << "\",\n";
			stream << "\t\"outputName\" : \"" << outputName << "\",\n";
			stream << "\t\"outputImageFormat\" : \"" << outputImageFormat << "\",\n";
			stream << "\t\"packingAlgorithm\" : \"" << packingAlgorithm << "\",\n";

			stream << "\t\"dataExportAlgorithms\" : [\n";
			for (uint32 i = 0; i < static_cast<uint32>(dataExportAlgorithms.size()); ++i)
			{
				stream << "\t\t\"" << dataExportAlgorithms[i] << "\"";
				if (i < static_cast<uint32>(dataExportAlgorithms.size() - 1))
					stream << ",\n";
				else
					stream << "\n";
			}
			stream << "\t\t],\n";

			stream << "\t\"keyConversionAlgorithm\" : \"" << keyConversionAlgorithm << "\",\n";
			
			stream << "\t\"allowRotation\" : " << (allowRotation ? "true" : "false") << ",\n";
			stream << "\t\"sizeConstraint\" : " << sizeConstraint << ",\n";
			stream << "\t\"constraintType\" : " << static_cast<uint32>(constraintType) << ",\n";

			uint32 color = 0;
			color += static_cast<uint32>(clearColor.data[0] << 24);
			color += static_cast<uint32>(clearColor.data[1] << 16);
			color += static_cast<uint32>(clearColor.data[2] << 8);
			color += static_cast<uint32>(clearColor.data[3] << 0);
			stream << "\t\"clearColor\" : \"" << std::hex << color << "\",\n";
			stream << "\t\"trimImages\" : " << (trimImages ? "true" : "false") << ",\n";
			stream << "\t\"replaceSameTextures\" : " << (replaceSameTextures ? "true\n" : "false\n");

			stream << "}\n";
			stream.close();
		}
		else
		{
			codes |= ErrorCodes::CouldNotCreateProjectFile;
		}

		return codes;
	}

	std::vector<std::string> Project::getRegisteredDataExporters() const
	{
		std::vector<std::string> exporterKeys;
		exporterKeys.reserve(dataExporters.size());
		for (auto itr = dataExporters.begin(); itr != dataExporters.end(); ++itr)
			exporterKeys.push_back(itr->first);
		return exporterKeys;
	}

	std::vector<std::string> Project::getRegisteredKeyConverters() const
	{
		std::vector<std::string> keyConverterKeys;
		keyConverterKeys.reserve(keyConverters.size());
		for (auto itr = keyConverters.begin(); itr != keyConverters.end(); ++itr)
			keyConverterKeys.push_back(itr->first);
		return keyConverterKeys;
	}

	std::vector<std::string> Project::getRegisteredPackers() const
	{
		std::vector<std::string> packerKeys;
		packerKeys.reserve(packers.size());
		for (auto itr = packers.begin(); itr != packers.end(); ++itr)
			packerKeys.push_back(itr->first);
		return packerKeys;
	}
}
