
#define TXPK_MAJOR_VERSION 1
#define TXPK_MINOR_VERSION 0

#include <iostream>

#include <cli.h>

#include <TXPK/Core/Project.hpp>

#define endln() std::cout << std::endl;
#define coutln(x) std::cout << x << std::endl;
#define cout(x) std::cout << x;

void print_help();
void print_version();
void print_errors(const txpk::ErrorCodes& error);
void pass_cli_args(CLI* cli, txpk::Project& project);

int main(int argc, char** argv)
{
	txpk::Project project;
	CLI* cli = CLI_Create(21);
	CLI_AddArgument(cli, 'p', ARG_TYPE_COMMAND);
	CLI_AddArgument(cli, 'i', ARG_TYPE_REQUIRED);
	CLI_AddArgument(cli, 'r', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'q', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'y', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'o', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'z', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'n', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'f', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'a', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'd', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'k', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 's', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'c', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 't', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'b', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'x', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'e', ARG_TYPE_OPTION);
	CLI_AddArgument(cli, 'h', ARG_TYPE_COMMAND);
	CLI_AddArgument(cli, 'v', ARG_TYPE_COMMAND);
	CLI_AddArgument(cli, 'g', ARG_TYPE_COMMAND);

	cli_errors cliErrors = CLI_Parse(cli, argc, argv);
	if (cliErrors != 0)
	{
		coutln("Error while parsing cli arguments:");
		if (HAS_FLAG(cliErrors, ERROR_ARGS_MISSING))
			coutln(" One or more required arguments are missing.");
		if (HAS_FLAG(cliErrors, ERROR_ARG_TOO_SHORT))
			coutln(" One or more arguments were too short.");
		if (HAS_FLAG(cliErrors, ERROR_NO_ARGS))
			coutln(" No arguments were provided.");

		endln();

		print_help();
		CLI_Destroy(cli);
		return cliErrors;
	}

	if (CLI_OptionSet(cli, 'h'))
	{
		endln();
		print_help();
		CLI_Destroy(cli);
		return 0;
	}

	if (CLI_OptionSet(cli, 'v'))
	{
		endln();
		print_version();
		CLI_Destroy(cli);
		return 0;
	}

	if (CLI_OptionSet(cli, 'g'))
	{
		project.name = "default.txpk";
		txpk::ErrorCodes txpkErrors = project.save();

		if (txpkErrors != txpk::ErrorCodes::Success)
			print_errors(txpkErrors);

		CLI_Destroy(cli);
		return static_cast<txpk::int32>(txpkErrors);
	}

	char* path = NULL;
	if (CLI_TryGetArgument(cli, 'p', &path))
	{
		txpk::ErrorCodes txpkErrors = project.load(path);
		if (txpkErrors != txpk::ErrorCodes::Success)
		{
			print_errors(txpkErrors);
			CLI_Destroy(cli);
			return static_cast<txpk::int32>(txpkErrors);
		}
	}
	else
	{
		pass_cli_args(cli, project);
	}

	txpk::ErrorCodes txpkErrors = project.run();

	if (txpkErrors != txpk::ErrorCodes::Success)
	{
		print_errors(txpkErrors);
		CLI_Destroy(cli);
		return static_cast<txpk::int32>(txpkErrors);
	}

	CLI_Destroy(cli);
	return 0;
}

void print_help()
{
	coutln("This is TXPK a free texture packer made by Seng.");
	coutln("It is meant to be highly configurable and easy to use as an automated texture packing process.");
	endln();
	coutln("-p Project file           Path to the project file. Positional argument.                [ Command  ]");
	coutln("-i InputDirectory         The directory to load the images from                         [ Required ]");
	coutln("-r InputRegex             The regex which decides which files to take                   [  Option  ]");
	coutln("-y ScriptDirectory        The directory to load scripts from                            [  Option  ]");
	coutln("-q RecursiveFiles         If true then get all files in directory recursively           [  Option  ]");
	coutln("-o OutputImageDirectory   The directory where the output image will be written to       [  Option  ]");
	coutln("-z OutputDataDirectory    The directory where the output data will be written to        [  Option  ]");
	coutln("-n OutputName             The name all files are getting called                         [ Required ]");
	coutln("-f OutputImageFormat      The image format of the resulting packed texture (png, jpg)   [  Option  ]");
	coutln("-a PackingAlgorithm       The algorithm to pack with                                    [  Option  ]");

	txpk::Project project;
	auto registrations = project.getRegisteredPackers();
	for (auto& packer : registrations)
	{
		cout("\t");
		if (packer.empty())
		{
			coutln("\"\" (empty)");
		}
		else
		{
			cout("\"");
			cout(packer);
			coutln("\"");
		}
	}

	coutln("-d DataExportAlgorithms   The algorithms to export data with (comma seperated)          [  Option  ]");

	registrations = project.getRegisteredDataExporters();
	for (auto& exporter : registrations)
	{
		cout("\t");
		if (exporter.empty())
		{
			coutln("\"\" (empty)");
		}
		else
		{
			cout("\"");
			cout(exporter);
			coutln("\"");
		}
	}

	coutln("-k KeyConversionAlgorithm The algorithm to convert keys with                            [  Option  ]");

	registrations = project.getRegisteredKeyConverters();
	for (auto& converter : registrations)
	{
		cout("\t");
		if (converter.empty())
		{
			coutln("\"\" (empty)");
		}
		else
		{
			cout("\"");
			cout(converter);
			coutln("\"");
		}
	}

	coutln("-s AllowRotation          Whether the algorithm is allowed to rotate images or not      [  Option  ]");
	coutln("-c SizeConstraint         Size constraint in either Width or Height                     [  Option  ]");
	coutln("-t ContraintType          Size constraint type (None, Width, Height)                    [  Option  ]");
	coutln("-b BackgroundClearColor   The color the image gets cleared                              [  Option  ]");
	coutln("-x TrimImages             Allow to cut the image so any transparency around will be cut [  Option  ]");
	coutln("-e ReplaceSameTextures    Allow to replace identical images                             [  Option  ]");
	coutln("-h Help                   Print help                                                    [ Command  ]");
	coutln("-v Version                Print version                                                 [ Command  ]");
	coutln("-g GenerateDefault        Generate default project file                                 [ Command  ]");
	endln();
	coutln("Using this rather complex CLI is not recommended. If your are using the -g command you can generate a default project file.");
	coutln("This project file has the json file format and has the same options as you have in the CLI.");
	coutln("You can use the -p Option and pass the path to the project file. All the options will be loaded automatically.");
	coutln("Example:  >TexturePacker.exe -p\"path/to/project/default.txpk\"");
	coutln("[.txpk] is the extension used for project files. But you can edit it with every editor.");
	endln();
}

void print_version()
{
	coutln("TXPK " << TXPK_MAJOR_VERSION << "." << TXPK_MINOR_VERSION);
	coutln("created by Seng");
	endln();
}

void print_errors(const txpk::ErrorCodes& error)
{
	typedef txpk::ErrorCodes Code;

	if (HAS_FLAG(error, Code::ProjectFileNotFound))				  coutln("The project file was not found.");
	if (HAS_FLAG(error, Code::InvalidProjectFile))				  coutln("The project file is invalid.");
	if (HAS_FLAG(error, Code::DataExportAlgorithmNotFound))		  coutln("The data export algorithm was not found.");
	if (HAS_FLAG(error, Code::PackerAlgorithmNotFound))			  coutln("The packer algorithm was not found.");
	if (HAS_FLAG(error, Code::KeyConversionAlgorithmNotFound))	  coutln("The key conversion algorithm was not found.");
	if (HAS_FLAG(error, Code::InputDirectoryNotFound))			  coutln("The input directory was not found.");
	if (HAS_FLAG(error, Code::OutputDirectoryNotFound))			  coutln("The output directory was not found.");
	if (HAS_FLAG(error, Code::OutputNameInvalidCharacters))		  coutln("The output name contains invalid characters.");
	if (HAS_FLAG(error, Code::InvalidOutputFormat))				  coutln("The output format is invalid.");
	if (HAS_FLAG(error, Code::SaveDirectoryNotFound))			  coutln("The save directory was not found.");
	if (HAS_FLAG(error, Code::InvalidProjectName))				  coutln("The project name is invalid.");
	if (HAS_FLAG(error, Code::CouldNotCreateProjectFile))		  coutln("The project file could not be created.");
	if (HAS_FLAG(error, Code::InputDirectoryDoesNotContainFiles)) coutln("The input directory does not contain any files or the regex did not match any.");
	if (HAS_FLAG(error, Code::FailedToLoadFile))		          coutln("One or more textures could not be loaded.");
	if (HAS_FLAG(error, Code::CouldNotCreatePackedTexture))       coutln("The textures could not be packed.");
	if (HAS_FLAG(error, Code::PackerGotInvalidTextures))          coutln("Packer got invalid textures. Textures got probably invalid after trimming. Please check the packers description, your textures and parameters.");
	
}

void pass_cli_args(CLI* cli, txpk::Project& project)
{
	char* data = NULL;
	int32 dump = 0;

	if (CLI_TryGetArgument(cli, 'i', &data))	
		project.inputDirectory = std::string(data);

	if (CLI_TryGetArgument(cli, 'r', &data))
		project.inputRegex = std::string(data);

	if (CLI_TryGetArgument(cli, 'y', &data))
		project.scriptDirectory = std::string(data);

	project.recursiveFiles = CLI_OptionSet(cli, 'q');

	if (CLI_TryGetArgument(cli, 'o', &data))
		project.outputImageDirectory = std::string(data);

	if (CLI_TryGetArgument(cli, 'z', &data))
		project.outputDataDirectory = std::string(data);

	if (CLI_TryGetArgument(cli, 'n', &data))
		project.outputName = std::string(data);

	if (CLI_TryGetArgument(cli, 'f', &data))
		project.outputImageFormat = std::string(data);

	if (CLI_TryGetArgument(cli, 'a', &data))
		project.packingAlgorithm = std::string(data);

	if (CLI_TryGetArgument(cli, 'd', &data))
	{
		std::string str(data);
		std::size_t current, previous = 0;
		current = str.find(',');
		while (current != std::string::npos) 
		{
			project.dataExportAlgorithms.push_back(str.substr(previous, current - previous));
			previous = current + 1;
			current = str.find(',', previous);
		}
		project.dataExportAlgorithms.push_back(str.substr(previous, current - previous));
	}

	if (CLI_TryGetArgument(cli, 'k', &data))
		project.keyConversionAlgorithm = std::string(data);

	project.allowRotation = CLI_OptionSet(cli, 's');

	if (CLI_TryGetArgument(cli, 'c', &data) && txpk::stoi(dump, data, 10) == txpk::ConversionResult::Success)
		project.sizeConstraint = static_cast<uint32>(dump);

	if (CLI_TryGetArgument(cli, 't', &data) && txpk::stoi(dump, data, 10) == txpk::ConversionResult::Success)
		project.constraintType = static_cast<txpk::SizeContraintType>(dump);

	if (CLI_TryGetArgument(cli, 'b', &data))
	{
		std::cout << "color " << data << std::endl;
		if (txpk::stoi(dump, data, 16) == txpk::ConversionResult::Success)
		{
			project.clearColor.data[0] = static_cast<txpk::uint8>(((static_cast<txpk::uint32>(dump) & 0xff000000) >> 24));
			project.clearColor.data[1] = static_cast<txpk::uint8>(((static_cast<txpk::uint32>(dump) & 0x00ff0000) >> 16));
			project.clearColor.data[2] = static_cast<txpk::uint8>(((static_cast<txpk::uint32>(dump) & 0x0000ff00) >> 8));
			project.clearColor.data[3] = static_cast<txpk::uint8>(((static_cast<txpk::uint32>(dump) & 0x000000ff) >> 0));
		}
		else
		{
			std::cout << (int32)txpk::stoi(dump, data, 16) << std::endl;
		}
	}

	project.trimImages = CLI_OptionSet(cli, 'x');
}