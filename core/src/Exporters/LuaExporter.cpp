#include "TXPK/Exporters/LuaExporter.hpp"

namespace txpk
{
	int conversion_function(lua_State* lua);

	void lua_pushtexture(lua_State* lua, const Texture& texture);
	void lua_pushrectangle(lua_State* lua, const Rectangle& rectangle);

	LuaExporter::LuaExporter(const std::string& script)
	{
		this->script = script;
	}

	void LuaExporter::exportData(TexturePtrs& textures, const uint32& width, const uint32& height, const std::string& imagePath, const std::string& outputDirectory, const std::string& outputName) const
	{
		const KeyConverterPtr converter = ServiceLocator::current()->resolve<IKeyConverter>();
		if (converter != NULL)
			converter->reset();

		lua_State* lua = luaL_newstate();
		luaL_openlibs(lua);

		if (luaL_dofile(lua, script.c_str()) != 0)
		{
			std::cout << lua_tostring(lua, -1) << std::endl;
			lua_pop(lua, -1);
			lua_close(lua);
			return;
		}

		lua_pushcfunction(lua, &conversion_function);
		lua_setglobal(lua, "convert");

		lua_getglobal(lua, "export");

		lua_newtable(lua);
		for (int i = 0; i < textures.size(); ++i)
		{
			lua_pushtexture(lua, *textures[i]);
			lua_rawseti(lua, -2, i + 1);
		}

		lua_pushinteger(lua, width);
		lua_pushinteger(lua, height);
		lua_pushstring(lua, imagePath.c_str());
		lua_pushstring(lua, outputDirectory.c_str());
		lua_pushstring(lua, outputName.c_str());

		if (lua_pcall(lua, 6, 0, 0) != 0)
		{
			std::cout << lua_tostring(lua, -1) << std::endl;
			lua_pop(lua, -1);
			lua_close(lua);
			return;
		}

		lua_close(lua);
	}

	int conversion_function(lua_State* lua)
	{
		const KeyConverterPtr converter = ServiceLocator::current()->resolve<IKeyConverter>();
		const int stackSize = lua_gettop(lua);

		if (converter == NULL)
		{
			if (lua_isstring(lua, stackSize))
				lua_settop(lua, stackSize - 1);
		}
		else
		{
			if (lua_isstring(lua, stackSize))
			{
				std::string value(lua_tostring(lua, stackSize));
				lua_settop(lua, stackSize - 1);
				std::string out = converter->convert(value);
				lua_pushstring(lua, out.c_str());
			}
			else
			{
				return 0;
			}
		}

		return 1;
	}

	void lua_pushtexture(lua_State* lua, const Texture& texture)
	{
		lua_createtable(lua, 0, 6);

		lua_pushstring(lua, texture.getPath().c_str());
		lua_setfield(lua, -2, "path");

		lua_pushrectangle(lua, *texture.getBounds());
		lua_setfield(lua, -2, "bounds");

		lua_pushinteger(lua, texture.getOffsetX());
		lua_setfield(lua, -2, "offsetX");

		lua_pushinteger(lua, texture.getOffsetY());
		lua_setfield(lua, -2, "offsetY");

		lua_pushinteger(lua, texture.getSourceWidth());
		lua_setfield(lua, -2, "sourceWidth");

		lua_pushinteger(lua, texture.getSourceHeight());
		lua_setfield(lua, -2, "sourceHeight");
	}

	void lua_pushrectangle(lua_State* lua, const Rectangle& rectangle)
	{
		lua_createtable(lua, 0, 5);

		lua_pushinteger(lua, rectangle.left);
		lua_setfield(lua, -2, "left");

		lua_pushinteger(lua, rectangle.top);
		lua_setfield(lua, -2, "top");

		lua_pushinteger(lua, rectangle.width);
		lua_setfield(lua, -2, "width");

		lua_pushinteger(lua, rectangle.height);
		lua_setfield(lua, -2, "height");

		lua_pushboolean(lua, rectangle.isRotated());
		lua_setfield(lua, -2, "rotated");
	}
}
