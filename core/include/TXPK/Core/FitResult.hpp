#pragma once

namespace txpk
{
	/**
	* \brief Enum used to define how a rectangle fits in another.
	*/
	enum class FitResult
	{
		No, /**< Does not fit. */
		Yes, /**< Does fit. */
		Rotated, /**< Does fit when rotated. */
		Perfect, /**< Does fit perfectly without any space left. */
		PerfectRotated /**< Does fit perfectly without any space left when rotated. */
	};
}
