#pragma once

namespace txpk
{
	typedef signed char        int8;
	typedef unsigned char      uint8;
	typedef signed short       int16;
	typedef unsigned short     uint16;
	typedef signed int         int32;
	typedef unsigned int       uint32;
	typedef signed long long   int64;
	typedef unsigned long long uint64;

/**
* \brief A macro for checking if an integer/enum has a flag set or not
* Example usage: HAS_FLAG(colors, Color::Red)
* \param value The value where to check.
* \param flag The flag to check.
* \return Returns true if the flag is set and false if not.
*/
#define HAS_FLAG(value, flag) ((value & flag) == flag)

/**
* \brief A macro for generating binary operators for an enum struct.
* Generates the |, &, |=, &= operators for the given enum struct. This makes using flags easier.
* Example usage: enum Colors {...}; GENERATE_FLAGS_OPERATORS(Colors);
* \param enumeration The enum struct.
*/
#define GENERATE_FLAGS_OPERATORS(enumeration)                       \
inline enumeration operator |(enumeration lhs, enumeration rhs)     \
{                                                                   \
    return static_cast<enumeration>(                                \
        static_cast<int>(lhs) | static_cast<int>(rhs));             \
}                                                                   \
inline enumeration operator &(enumeration lhs, enumeration rhs)     \
{                                                                   \
    return static_cast<enumeration>(                                \
    static_cast<int>(lhs) & static_cast<int>(rhs));                 \
}                                                                   \
inline enumeration& operator |=(enumeration& lhs, enumeration rhs)  \
{                                                                   \
    lhs = lhs | rhs;                                                \
    return lhs;                                                     \
}                                                                   \
inline enumeration& operator &=(enumeration& lhs, enumeration rhs)  \
{                                                                   \
    lhs = lhs & rhs;                                                \
    return lhs;                                                     \
}																 

}
