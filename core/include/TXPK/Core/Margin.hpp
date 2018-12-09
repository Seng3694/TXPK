#pragma once

#include "TXPK/Core/Common.hpp"

namespace txpk
{
	/**
	* \brief The margin struct.
	* Margin defines the space between an inner and an outer rectangle.
	*/
	struct Margin
	{
		uint32 left; /**< Space between the left sides */
		uint32 top; /**< Space between the top sides */
		uint32 right; /**< Space between the right sides */
		uint32 bottom; /**< Space between the bottom sides */

		/**
		* \brief Default constructor.
		*/
		Margin();
		/**
		* \brief Creates a Margin struct with all values set to the given value.
		* \param all The value to set all fields with.
		*/
		Margin(uint32 all);
		/**
		* \brief Creates a Margin struct with the given values.
		* \param left The left value.
		* \param top The top value.
		* \param right The right value.
		* \param bottom The bottom value.
		*/
		Margin(uint32 left, uint32 top, uint32 right, uint32 bottom);
	};
}
