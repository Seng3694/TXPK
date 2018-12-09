#pragma once

#include "TXPK/Core/IKeyConverter.hpp"
#include "TXPK/FileSystem/FileSystem.hpp"

namespace txpk
{
	/**
	* \brief A converter which converts any file path to just the file name without the extension.
	*/
	class FileWithoutExtConverter : public IKeyConverter
	{
	public:
		std::string convert(const std::string& input) override;
		void reset() override;
	};
}
