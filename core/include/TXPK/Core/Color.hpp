#pragma once

#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/Comparison.hpp"

namespace txpk
{
	/**
	* \brief The color struct.
	* \tparam size The size how big the struct should be.
	*/
	template<uint32 size>
	struct Color
	{
		uint8 data[size]; /**< The color data array */

		/**
		* \brief operator[] for getting data directly.
		* \param index The index to get the data from. Accesses the inner array.
		* \return Returns the value at the given index.
		*/
		inline uint8 operator [](const int32 index) const;
		/**
		* \brief operator[] for setting data directly.
		* \param index The index to set the data at. Accesses the inner array.
		* \return Returns the value reference at the given index.
		*/
		inline uint8& operator [](const int32 index);
		/**
		* \brief operator== for checking equality of two Color structs.
		* \param other The other color to check with.
		* \return Returns true if both are equal and false if not.
		*/
		bool operator ==(const Color& other);
		/**
		* \brief operator!= for checking inequality of two Color structs.
		* \param other The other color to check with.
		* \return Returns false if both are iequal and true if not.
		*/
		bool operator !=(const Color& other);
	};

	/**
	* \brief The in this project most used color struct with 4 components => RGBA.
	*/
	typedef Color<4> Color4;
}

#include "TXPK/Core/Color.inl"
