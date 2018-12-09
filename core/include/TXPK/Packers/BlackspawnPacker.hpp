#pragma once

#include <algorithm>
#include <memory>
#include <numeric>

#include "TXPK/Core/IPacker.hpp"

namespace txpk
{
	/**
	* \brief A packer which packs any texture of any size in a bin.
	* Algorithm taken from: http://blackpawn.com/texts/lightmaps/default.html
	*/
	class BlackspawnPacker : public IPacker
	{
	public:
		Bin pack(RectanglePtrs& rectangles, const uint32& sizeConstraint, const SizeContraintType& constraintType, const bool& allowRotation) const override;
		inline bool validate(RectanglePtrs& rectangles, const uint32& sizeConstraint = 0, const SizeContraintType& constraintType = SizeContraintType::None, const bool& allowRotation = false) const override { return true; }

	private:
		class Node
		{
		public:
			typedef std::unique_ptr<Node> NodePtr;

			Node();

			Rectangle bounds;

			bool insert(RectanglePtr bounds, const bool& allowRotation);
			void reset();

		private:
			NodePtr left;
			NodePtr right;
			bool isFilled;
		};
	};
}
