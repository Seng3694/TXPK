#include "TXPK/Exporters/JsonExporter.hpp"

namespace txpk
{
	void JsonExporter::exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const
	{
		std::string outputPath;
		if (outputDirectory != "")
			outputPath.append(outputDirectory + '/');

		outputPath.append(outputName + ".json");

		std::ofstream stream(outputPath);

		if (stream.is_open())
		{
			stream << "{";
			stream << "\"meta\":{";
			stream << "\"w\":" << width << ",";
			stream << "\"h\":" << height << ",";
			stream << "\"img\":\"" << imagePath << "\"";
			stream << "},";
			stream << "\"bin\":[";

			const KeyConverterPtr converter = ServiceLocator::current()->resolve<IKeyConverter>();
			if (converter != NULL)
				converter->reset();

			RectanglePtr bounds = NULL;
			std::string key;
			int32 integerKey = 0;
			for (auto itr = textures.begin(); itr != textures.end(); ++itr)
			{
				bounds = (*itr)->getBounds();
				stream << "{";

				key = (converter != NULL ? converter->convert((*itr)->getPath()) : (*itr)->getPath());
				if(stoi(integerKey, key.c_str()) == ConversionResult::Success)
					stream << "\"key\":" << integerKey << ",";
				else
					stream << "\"key\":\"" << key << "\",";

				stream << "\"x\":" << bounds->left << ",";
				stream << "\"y\":" << bounds->top << ",";
				stream << "\"w\":" << bounds->width << ",";
				stream << "\"h\":" << bounds->height << ",";

				stream << "\"ox\":" << (*itr)->getOffsetX() << ",";
				stream << "\"oy\":" << (*itr)->getOffsetY() << ",";
				stream << "\"sw\":" << (*itr)->getSourceWidth() << ",";
				stream << "\"sh\":" << (*itr)->getSourceHeight() << ",";

				stream << "\"r\":" << (bounds->isRotated() ? "true" : "false");

				stream << "}";
				if (static_cast<uint32>(itr - textures.begin()) < textures.size() - 1)
					stream << ",";
			}

			stream << "]}";

			stream.close();
		}

	}	
}
