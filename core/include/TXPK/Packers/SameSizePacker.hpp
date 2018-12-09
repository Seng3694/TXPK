#pragma once

#include "TXPK/Core/IPacker.hpp"
#include "TXPK/Math/MathExtension.hpp"

namespace txpk
{
	/**
	* \brief A packer which packs only textures of the same size but very efficiently.
	* Warning: trimming images before packing could lead to textures which had the same size before but not after.
	* This will result in the SameSizePacker invalidating the textures and not packing them.
	*/
	class SameSizePacker : public IPacker
	{
	public:
		Bin pack(RectanglePtrs& rectangles, const uint32& sizeConstraint, const SizeContraintType& constraintType, const bool& allowRotation) const override;
		bool validate(RectanglePtrs& rectangles, const uint32& sizeConstraint = 0, const SizeContraintType& constraintType = SizeContraintType::None, const bool& allowRotation = false) const override;
	};
}
