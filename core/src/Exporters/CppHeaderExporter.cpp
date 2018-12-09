#include "TXPK/Exporters/CppHeaderExporter.hpp"

namespace txpk
{
	std::string all_caps_underscore_seperated(const std::string str);

	void CppHeaderExporter::exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const
	{
		std::string outputPath;
		if (outputDirectory != "")
			outputPath.append(outputDirectory + '/');

		outputPath.append(outputName + ".hpp");

		std::ofstream stream(outputPath);

		if (stream.is_open())
		{
			const KeyConverterPtr converter = ServiceLocator::current()->resolve<IKeyConverter>();
			if (converter != NULL)
				converter->reset();

			stream << "#pragma once\n\n";

			for (uint32 i = 0; i < textures.size(); ++i)
			{
				stream << "#define " << all_caps_underscore_seperated(textures[i]->getPath());
				stream << " " << converter->convert(textures[i]->getPath()) << "\n";
			}

			stream.close();
		}
	}

	std::string all_caps_underscore_seperated(const std::string str)
	{
		std::string output = get_file_name_without_ext(str);

		for (uint32 i = 0; i < static_cast<uint32>(output.size()); ++i)
		{
			if (output[i] >= 'a' && output[i] <= 'z')
				output[i] -= 32;
		}

		return output;
	}
}
