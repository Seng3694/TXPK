#include "TXPK/Core/Margin.hpp"

namespace txpk
{
	Margin::Margin()
	{
		left = 0;
		top = 0;
		right = 0;
		bottom = 0;
	}

	Margin::Margin(uint32 all) 
	{
		left = all;
		top = all;
		right = all;
		bottom = all;
	}

	Margin::Margin(uint32 left, uint32 top, uint32 right, uint32 bottom) 
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}
}
