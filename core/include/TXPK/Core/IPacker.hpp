#pragma once

#include <vector>

#include "TXPK/Core/Bin.hpp"
#include "TXPK/Core/SizeConstraintType.hpp"

namespace txpk
{/**
	* \brief Interface used by all Packer implementations.
	*/
	class IPacker
	{
	public:
		/**
		* \brief Pure virtual interface needs a virtual destructor.
		*/
		virtual ~IPacker() {}
		/**
		* \brief Validates whether the given parameters are valid for the Packer implementation or not.
		* \param rectangles The rectangles to pack into one image.
		* \param sizeConstraint Size constraint to either width or height.
		* \param constraintType The constraint type (None, width or height).
		* \param allowRotation Whether rotation is allowed or not.
		* \return Returns if the given parameters are valid for the Packer implementation or not.
		*/
		virtual bool validate(RectanglePtrs& rectangles, const uint32& sizeConstraint = 0, const SizeContraintType& constraintType = SizeContraintType::None, const bool& allowRotation = false) const = 0;
		/**
		* \brief Packs the given rectangles in consideration of other parameters into one Bin.
		* \param rectangles The rectangles to pack into one image.
		* \param sizeConstraint Size constraint to either width or height.
		* \param constraintType The constraint type (None, width or height).
		* \param allowRotation Whether rotation is allowed or not.
		* \return Returns a Bin with packed rectangles.
		*/
		virtual Bin pack(RectanglePtrs& rectangles, const uint32& sizeConstraint = 0, const SizeContraintType& constraintType = SizeContraintType::None, const bool& allowRotation = false) const = 0;
	};

	typedef std::shared_ptr<IPacker> PackerPtr;
}
