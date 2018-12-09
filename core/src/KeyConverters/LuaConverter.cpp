#pragma once

#include "TXPK/KeyConverters/LuaConverter.hpp"

namespace txpk
{
	LuaConverter::LuaConverter(const std::string& script)
	{
		this->script = script;
		this->state = NULL;
	}

	LuaConverter::~LuaConverter()
	{
		if (state != NULL)
		{
			lua_close(state);
			state = NULL;
		}
	}

	std::string LuaConverter::convert(const std::string& input)
	{
		if (state == NULL)
		{
			state = luaL_newstate();
			luaL_openlibs(state);

			if (luaL_dofile(state, script.c_str()) != 0)
			{
				std::cout << lua_tostring(state, -1) << std::endl;
				lua_pop(state, -1);
				lua_close(state);
				state = NULL;
				return input;
			}
		}

		lua_getglobal(state, "convert");
		lua_pushstring(state, input.c_str());

		if (lua_pcall(state, 1, 1, 0) != 0)
		{
			std::cout << lua_tostring(state, -1) << std::endl;
			lua_pop(state, -1);
			lua_close(state);
			state = NULL;
			return input;
		}

		std::string output;

		int type = lua_type(state, -1);
		switch (type)
		{
		case LUA_TBOOLEAN:
		{
			output = lua_toboolean(state, -1) == 1 ? "true" : "false";
			break;
		}
		case LUA_TNUMBER:
		{
			int32 number = static_cast<int32>(lua_tonumber(state, -1));
			std::stringstream ss;
			ss << number;
			output = ss.str();
			break;
		}
		case LUA_TSTRING:
		{
			output = lua_tostring(state, -1);
			break;
		}
		}

		lua_pop(state, -1);
		return output;
	}

	void LuaConverter::reset()
	{
		if (state != NULL)
		{
			lua_getglobal(state, "reset");
			if (lua_pcall(state, 0, 0, 0) != 0)
			{
				std::cout << lua_tostring(state, -1) << std::endl;
				lua_pop(state, -1);
				lua_close(state);
				state = NULL;
			}
		}
	}
}
