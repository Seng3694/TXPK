#pragma once

#include <memory>
#include <vector>

#include "TXPK/Core/Common.hpp"
#include "TXPK/Core/FitResult.hpp"

namespace txpk
{
	/**
	* \brief The Rectangle class.
	*/
	class Rectangle
	{
	public:
		uint32 left; /**< The left value (x).  */
		uint32 top; /**< The top value (y). */
		uint32 width; /**< The width. */
		uint32 height; /**< The height */

		/**
		* \brief Default constructor.
		*/
		Rectangle();
		/**
		* \brief Constructs a rectangle with the given width and height.
		* \param width The width the rectangle should have.
		* \param height The height the rectangle should have.
		*/
		Rectangle(const uint32& width, const uint32& height);
		/**
		* \brief Constructs a rectangle with the given left, top, right and bottom values.
		* \param left The x value.
		* \param top The y value.
		* \param right The right side of the rectangle. right = left + width.
		* \param bottom The bottom side of the rectangle. bottom = top + height.
		*/
		Rectangle(const uint32& left, const uint32& top, const uint32& right, const uint32& bottom);

		/**
		* \brief Gets the right value.
		* \return Returns left + width
		*/
		uint32 getRight() const;
		/**
		* \brief Gets the bottom value.
		* \return Returns top + height
		*/
		uint32 getBottom() const;
		/**
		* \brief Calculates the area.
		* \return Returns the area width * height.
		*/
		uint32 getArea() const;
		/**
		* \brief Calculates the perimeter.
		* \return Returns the perimeter 2*width+2*height
		*/
		uint32 getPerimeter() const;

		/**
		* \brief Rotates the rectangle.
		* The rotation switches the width and height values and sets the rotate value.
		*/
		void rotate();
		/**
		* \brief Gets whether the rectangle is rotated or not.
		* \return Returns a boolean which indicates whether a rectangle is rotated or not.
		*/
		bool isRotated() const;

		/**
		* \brief Checks if this rectangle fits in another.
		* \param other The rectangle to check.
		* \param allowRotation Whether rotation is allowed or not.
		* \return Returns a result how this rectangle fits in the other one.
		* \sa FitResult
		*/
		FitResult fits(const Rectangle& other, bool allowRotation) const;

		/**
		* \brief Checks if this rectangle is equal to the other one.
		* \return Returns true if both are equal and false if not.
		*/
		bool operator ==(const Rectangle& other);
		/**
		* \brief Checks if this rectangle is unequal to the other one.
		* \return Returns true if both are unequal and false if not.
		*/
		bool operator !=(const Rectangle& other);

	private:
		bool rotated; /**< Indicates if the rectangle was rotated or not */
	};

	typedef std::shared_ptr<Rectangle> RectanglePtr;
	typedef std::vector<RectanglePtr> RectanglePtrs;
}


#include "TXPK/Core/Rectangle.inl"
