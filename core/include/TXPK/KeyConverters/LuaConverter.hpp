#pragma once

#include <iostream>
#include <sstream>
#include <string>

#include <lua.hpp>
#include <lauxlib.h>
#include <lualib.h>

#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/IKeyConverter.hpp"

namespace txpk
{
	/**
	* \brief Key converter that loads a lua script file and loads it once.
	* The script has to use following functions if it should be invoked:
	* 
	* function convert(input)
	* function reset()
	*
	* "input" is a string. The convert function has to return either an integer or a string. 
	* The reset function is optional and can be used to reset any state.
	*/
	class LuaConverter : public IKeyConverter
	{
	public:
		LuaConverter(const std::string& script);
		~LuaConverter();

		std::string convert(const std::string& input) override;
		void reset() override; 

	private:
		lua_State* state; /**< The lua state */
		std::string script; /** The path to the script to load */
	};
}
