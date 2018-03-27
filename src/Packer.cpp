#include <algorithm>
#include <math.h>

#include "MathHelper.h"
#include "Packer.h"
#include "Node.h"

Bin Packer::pack(std::vector<TextureInfo>& infos, const bool& allowFlip)
{
	TextureInfo* previous = nullptr;
	auto sameSize = true;
	auto bin = Bin();
	auto totalArea = 0;
	
	for (auto &info : infos)
	{
		totalArea += info.rectangle.getArea();
		bin.infos.push_back(&info);

		if (previous != nullptr && sameSize)
		{
			if (previous->rectangle.width != info.rectangle.width
				|| previous->rectangle.height != info.rectangle.height)
				sameSize = false;
		}

		previous = &info;
	}

	//calculate bin size if textures share all the same size
	if (sameSize)
	{
		auto count = infos.size();

		while (MathHelper::isPrime(count))
			count++;

		auto squared = static_cast<int>(round(sqrtf(count)));
		auto smallest = count;

		for (auto i = static_cast<int>(round(count / 2)); i > 0; --i)
		{
			auto height = static_cast<double>(count) / static_cast<double>(i);
			if (height == round(height) && (abs(squared- height) < smallest))
			{
				smallest = abs(squared - height);
				bin.width = (count / height) * bin.infos[0]->rectangle.width;
				bin.heigth = height * bin.infos[0]->rectangle.height;
			}
		}
	}
	//start with sqrt(area) x sqrt(area) and resize +1 in each direction if not enough space
	else
	{
		bin.width = static_cast<int>(round(sqrtf(totalArea)));
		bin.heigth = bin.width;
	}

	std::sort(infos.begin(), infos.end(), [](const auto& lhs, const auto& rhs)
	{
		return lhs.rectangle.getArea() > rhs.rectangle.getArea();
	});

	auto root = Node();
	root.bounds = Rectangle(bin.width, bin.heigth);

	auto error = true;

	while (error)
	{
		error = false;

		for (auto &info : infos)
		{
			auto node = root.insert(info, allowFlip);

			if (node == nullptr)
			{
				error = true;
				root.reset();
				bin.width += 1;
				bin.heigth += 1;
				root.bounds = Rectangle(bin.width, bin.heigth);
				break;
			}
		}
	}

	return bin;
}