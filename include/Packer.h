#pragma once

#include <vector>

#include "TextureInfo.h"
#include "Bin.h"

class Packer
{
public:
	static Bin pack(std::vector<TextureInfo>& infos, const bool& allowFlip);
};