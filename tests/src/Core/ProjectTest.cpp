#include <catch2/catch.hpp>

#include <TXPK/Core/Project.hpp>

TEST_CASE("Project can be created", "[TXPK/Core/Project]")
{
	txpk::Project project;
	REQUIRE(project.name == "");
	REQUIRE(project.recursiveFiles == false);
	REQUIRE(project.inputDirectory == "");
	REQUIRE(project.inputRegex == ".+((.png)|(.jpg)|(.jpeg))$");
	REQUIRE(project.scriptDirectory == "");
	REQUIRE(project.outputImageDirectory == "");
	REQUIRE(project.outputDataDirectory == "");
	REQUIRE(project.outputName == "txpk_export");
	REQUIRE(project.outputImageFormat == "png");
	REQUIRE(project.packingAlgorithm == "Default");
	REQUIRE(project.dataExportAlgorithms.size() == 1);
	REQUIRE(project.dataExportAlgorithms[0] == "Default");
	REQUIRE(project.keyConversionAlgorithm == "Default");
	REQUIRE(project.allowRotation == false);
	REQUIRE(project.sizeConstraint == 0);
	REQUIRE(project.constraintType == txpk::SizeContraintType::None);
	REQUIRE((project.clearColor == txpk::Color4{0,0,0,0}) == true);
	REQUIRE(project.trimImages == false);
	REQUIRE(project.replaceSameTextures == false);
}

TEST_CASE("Project save and load", "[TXPK/Core/Project]")
{
	using namespace txpk;

	SECTION("The expected case")
	{
		Project project;
		project.name = "test.txpk";
		//change something for testing it
		project.clearColor = { 85, 170, 255, 255 };

		//should save as ./test.txpk
		ErrorCodes codes = project.save();
		REQUIRE(codes == ErrorCodes::Success);

		Project loadedProject;
		codes = loadedProject.load("test.txpk");
		REQUIRE(codes == ErrorCodes::Success);

		REQUIRE(loadedProject.name == project.name);
		REQUIRE((loadedProject.clearColor == project.clearColor) == true);

		std::remove("test.txpk");
	}

	SECTION("Save errors")
	{
		SECTION("SaveDirectoryNotFound")
		{
			Project project;
			project.name = "this/directory/does/not/exist/test.txpk";
			ErrorCodes codes = project.save();
			REQUIRE(HAS_FLAG(codes, ErrorCodes::SaveDirectoryNotFound));
		}

		SECTION("InvalidProjectName")
		{
			Project project;
			project.name = "";
			ErrorCodes codes = project.save();
			REQUIRE(HAS_FLAG(codes, ErrorCodes::InvalidProjectName));
		}

		//can't produce a CouldNotCreateProjectFile error. But it should occur when the save stream could not be opened.
		//probably when you don't have rights to access a directory or similar. Won't create that for a test case
	}

	SECTION("Load errors")
	{
		SECTION("ProjectFileNotFound")
		{
			Project project;
			ErrorCodes codes = project.load("this/file/should/not/exist.txpk");

			REQUIRE(HAS_FLAG(codes, ErrorCodes::ProjectFileNotFound));
		}

		SECTION("InvalidProjectFile")
		{
			std::ofstream stream("noprojectfile.txpk");
			if (stream.is_open())
			{
				stream << "<definetly no json>";
				stream.close();
			}

			Project project;
			ErrorCodes codes = project.load("noprojectfile.txpk");

			REQUIRE(HAS_FLAG(codes, ErrorCodes::InvalidProjectFile));

			std::remove("noprojectfile.txpk");
		}

		SECTION("No error with no algorithms")
		{
			Project project;
			project.name = "test.txpk";
			project.dataExportAlgorithms.clear();
			project.packingAlgorithm = "";
			project.keyConversionAlgorithm = "";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(codes == ErrorCodes::Success);
			std::remove("test.txpk");
		}

		SECTION("DataExportAlgorithmNotFound")
		{
			Project project;
			project.name = "test.txpk";
			project.dataExportAlgorithms.push_back("non existing algorithm");
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::DataExportAlgorithmNotFound));
			std::remove("test.txpk");
		}

		SECTION("PackerAlgorithmNotFound")
		{
			Project project;
			project.name = "test.txpk";
			project.packingAlgorithm = "non existing algorithm";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::PackerAlgorithmNotFound));
			std::remove("test.txpk");
		}

		SECTION("KeyConversionAlgorithmNotFound")
		{
			Project project;
			project.name = "test.txpk";
			project.keyConversionAlgorithm = "non existing algorithm";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::KeyConversionAlgorithmNotFound));
			std::remove("test.txpk");
		}

		SECTION("InputDirectoryNotFound")
		{
			Project project;
			project.name = "test.txpk";
			project.inputDirectory = "this/directory/should/not/exist";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::InputDirectoryNotFound));
			std::remove("test.txpk");
		}

		SECTION("InputDirectoryNotFound")
		{
			Project project;
			project.name = "test.txpk";
			project.inputDirectory = "this/directory/should/not/exist";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::InputDirectoryNotFound));
			std::remove("test.txpk");
		}

		SECTION("OutputDirectoryNotFound (Data)")
		{
			Project project;
			project.name = "test.txpk";
			project.outputDataDirectory = "this/directory/should/not/exist";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::OutputDirectoryNotFound));
			std::remove("test.txpk");
		}

		SECTION("OutputDirectoryNotFound (Image)")
		{
			Project project;
			project.name = "test.txpk";
			project.outputImageDirectory = "this/directory/should/not/exist";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::OutputDirectoryNotFound));
			std::remove("test.txpk");
		}

		SECTION("OutputNameInvalidCharacters")
		{
			Project project;
			project.name = "test.txpk";
			project.outputName = "some < invalid : file ? characters !";
			ErrorCodes codes = project.save();
			REQUIRE(codes == ErrorCodes::Success);

			codes = project.load("test.txpk");
			REQUIRE(HAS_FLAG(codes, ErrorCodes::OutputNameInvalidCharacters));
			std::remove("test.txpk");
		}

		SECTION("InvalidOutputFormat")
		{
			SECTION("png")
			{
				Project project;
				project.name = "test.txpk";
				project.outputImageFormat = "png";
				ErrorCodes codes = project.save();
				REQUIRE(codes == ErrorCodes::Success);

				codes = project.load("test.txpk");
				REQUIRE(codes == ErrorCodes::Success);
				std::remove("test.txpk");
			}

			SECTION("jpg")
			{
				Project project;
				project.name = "test.txpk";
				project.outputImageFormat = "jpg";
				ErrorCodes codes = project.save();
				REQUIRE(codes == ErrorCodes::Success);

				codes = project.load("test.txpk");
				REQUIRE(codes == ErrorCodes::Success);
				std::remove("test.txpk");
			}

			SECTION("jpeg")
			{
				Project project;
				project.name = "test.txpk";
				project.outputImageFormat = "jpeg";
				ErrorCodes codes = project.save();
				REQUIRE(codes == ErrorCodes::Success);

				codes = project.load("test.txpk");
				REQUIRE(codes == ErrorCodes::Success);
				std::remove("test.txpk");
			}

			SECTION("others")
			{
				Project project;
				project.name = "test.txpk";
				project.outputImageFormat = "bmp";
				ErrorCodes codes = project.save();
				REQUIRE(codes == ErrorCodes::Success);

				codes = project.load("test.txpk");
				REQUIRE(HAS_FLAG(codes, ErrorCodes::InvalidOutputFormat));
				std::remove("test.txpk");
			}
		}
	}
}

TEST_CASE("Project run", "[TXPK/Core/Project]")
{
	using namespace txpk;

	SECTION("The expected case")
	{
		//first we have to create atleast one valid image
		Color4 raw[] = 
		{
			{ 255,0,0,255 },{   0,255,0,255 },
			{ 0,0,255,255 },{ 255,255,0,255 }
		};
		
		Texture texture;
		texture.loadFromMemory(raw, 2, 2);
		REQUIRE(texture.save("test_image.png"));

		Project project;
		project.inputRegex = ".+(.png)$";
		project.outputName = "testout";
		project.outputImageFormat = "png";

		ErrorCodes codes = project.run();
		REQUIRE(codes == ErrorCodes::Success);

		std::remove("test_image.png");
		std::remove("testout.png");
		std::remove("testout.json");
	}

	SECTION("InputDirectoryDoesNotContainFiles")
	{
		Project project;
		project.inputRegex = ".+(.png)$";
		project.outputName = "testout";

		ErrorCodes codes = project.run();
		REQUIRE(codes == ErrorCodes::InputDirectoryDoesNotContainFiles);
	}

	SECTION("FailedToLoadFile")
	{
		Project project;
		project.inputRegex = ".+(.exe)$";
		project.outputName = "testout";

		ErrorCodes codes = project.run();
		REQUIRE(codes == ErrorCodes::FailedToLoadFile);
	}

	//CouldNotCreatePackedTexture can't produce this error. Probably something with access rights

	//PackerGotInvalidTextures is dependant on the IPacker implementation => check the packers for it
}

TEST_CASE("Project can load script files", "[TXPK/Core/Project]")
{
	using namespace txpk;

	Project project;
	project.name = "test.txpk";
	project.scriptDirectory = "content";

	ErrorCodes codes = project.save();
	REQUIRE(codes == ErrorCodes::Success);

	codes = project.load("test.txpk");
	REQUIRE(codes == ErrorCodes::Success);
	std::remove("test.txpk");

	bool containsTxtExporter = false;
	auto exporters = project.getRegisteredDataExporters();

	for (auto& exporter : exporters)
	{
		if (exporter == "TxtExporter")
			containsTxtExporter = true;
	}

	REQUIRE(containsTxtExporter);
}