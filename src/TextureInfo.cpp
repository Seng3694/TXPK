#include "TextureInfo.h"

std::ostream& operator<<(std::ostream& stream, const TextureInfo& info)
{
	stream << "\"path\":\"" << info.path << "\",";
	stream << "\"x\":" << info.rectangle.left << ",";
	stream << "\"y\":" << info.rectangle.top << ",";
	stream << "\"w\":" << info.rectangle.width << ",";
	stream << "\"h\":" << info.rectangle.height << ",";
	stream << "\"flip\":" << (info.rectangle.isFlipped() ? "1" : "0");
	return stream;
}