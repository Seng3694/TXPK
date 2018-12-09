#include "TXPK/KeyConverters/FileWithoutExtConverter.hpp"

namespace txpk
{
	std::string FileWithoutExtConverter::convert(const std::string& input)
	{
		return get_file_name_without_ext(input);
	}

	void FileWithoutExtConverter::reset()
	{
	}
}
