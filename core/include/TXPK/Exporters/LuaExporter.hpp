#pragma once

#include <iostream>
#include <string>

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include "TXPK/Core/IDataExporter.hpp"
#include "TXPK/Core/IKeyConverter.hpp"
#include "TXPK/Core/ServiceLocator.hpp"

namespace txpk
{
	/**
	* \brief Exporter that loads a lua script file and invokes it when exportData is called.
	* The script has to use following function if it should be invoked:
	*
	* function export(textures, width, height, imagePath, outputDirectory, outputName)
	*
	* "textures" is an iterable table. A texture has the following keys: 
	* "path"(string), "bounds"(rectangle), "offsetX"(number), "offsetY"(number), "sourceWidth"(number), "sourceHeight"(number)
	* "bounds" is a rectangle which has following keys: "left"(number), "top"(number), "width"(number), "height"(number), "rotated"(boolean)
	* so following code would be correct if textures had atleast one texture in it (remember Lua indexes begin at 1):
	* for i = 1, #textures, 1 do		--iterates over all textures
	*	 print(textures[i].bounds.left) --prints the left value of all texture bounds
	*
	* "width" is the width of the packed texture.
	* "height" is the height of the packed texture.
	* "imagePath" is the path to the packed texture.
	* "outputDirectory" is the directory path where any output should be saved to.
	* "outputName" is the name the exported output file should be saved with.
	*
	* For any more insight please look at the source code.
	*/
	class LuaExporter : public IDataExporter
	{
	public:
		LuaExporter(const std::string& script);

		void exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const override;

	private:
		std::string script; /**< The path to the script to load when executed */
	};
}
