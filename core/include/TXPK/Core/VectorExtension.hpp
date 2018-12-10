#pragma once

#include <string.h>
#include <vector>

#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/Margin.hpp"

namespace txpk
{
	/**
	* \brief Applies a margin to the given data.
	* \param data The pointer to the one dimensional array to manipulate.
	* \param width The width of the array (seen as two dimensional array)
	* \param height The height of the array (seen as two dimensional array)
	* \param margin The margin to apply.
	* \sa Margin
	*/
	template<typename T>
	void apply_margin(T** data, const uint32& width, const uint32& height, const Margin& margin);

	/**
	* \brief Applies a margin to the given data.
	* \param data Vector of one dimensional data to manipulate.
	* \param width The width of the array (seen as two dimensional array)
	* \param height The height of the array (seen as two dimensional array)
	* \param margin The margin to apply.
	* \return Returns a new vector with the applied margin.
	* \sa Margin
	*/
	template<typename T>
	std::vector<T> apply_margin(const std::vector<T>& data, const uint32& width, const uint32& height, const Margin& margin);
}

#include "TXPK/Core/VectorExtension.inl"
