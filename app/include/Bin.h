#pragma once

#include <vector>

#include "TextureInfo.h"


class Bin
{
public:
	int width;
	int heigth;
	std::vector<TextureInfo*> infos;
};