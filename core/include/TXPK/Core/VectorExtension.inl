#include "TXPK/Core/VectorExtension.hpp"

namespace txpk
{
	template<typename T>
	void apply_margin(T** data, const uint32& width, const uint32& height, const Margin& margin)
	{
		/*
                    top
              ______________
             |  _____v____  |
             | |          | |
         left|>|          |<|right
             | |          | |
             | |__________| |
             |_______^______|
                  bottom
		*/

		const uint32 newWidth = width - margin.left - margin.right;
		const uint32 newHeight = height - margin.top - margin.bottom;
		T* newData = new T[newWidth * newHeight];

		//copy row by row
		for (uint32 row = 0; row < newHeight; ++row)
			memcpy(&newData[row * newWidth], &((*data)[(row + margin.top) * width + margin.left]), sizeof(T) * newWidth);

		//delete old array and assign new one
		delete[] (*data);
		(*data) = newData;
	}


	template<typename T>
	std::vector<T> apply_margin(const std::vector<T>& data, const uint32& width, const uint32& height, const Margin& margin)
	{
		const uint32 newWidth = width - margin.left - margin.right;
		const uint32 newHeight = height - margin.top - margin.bottom;
		std::vector<T> newData;
		newData.resize(newWidth * newHeight);

		//copy row by row
		for (uint32 row = 0; row < newHeight; ++row)
			memcpy(&newData[row * newWidth], &(data[(row + margin.top) * width + margin.left]), sizeof(T) * newWidth);

		return newData;
	}
}
