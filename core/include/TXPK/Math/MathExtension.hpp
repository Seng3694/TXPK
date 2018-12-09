#pragma once

#include <algorithm>
#include <cmath>
#include <vector>

namespace txpk
{
	/**
	* \brief A macro which returns the larger value.
	* \param lhs The first value.
	* \param rhs The second value.
	* \return Returns the larger value.
	*/
	#define MAX(lhs, rhs) (lhs > rhs ? lhs : rhs)
	/**
	* \brief A macro which returns the smaller value.
	* \param lhs The first value.
	* \param rhs The second value.
	* \return Returns the smaller value.
	*/
	#define MIN(lhs, rhs) (lhs < rhs ? lhs : rhs)

	/**
	* \brief Checks whether the number is prime or not.
	* \param number The number to check.
	* \return Returns true if the number is prime.
	*/
	bool is_prime(int number);
	/**
	* \brief Calculates the largest prime factor of the number.
	* \param number The number to calculate the prime factor from.
	* \return Returns the prime factor.
	*/
	int largest_prime_factor(int number);
	/**
	* \brief Calculates all prime factors of the number.
	* \param number The number to calculate the prime factors from.
	* \return Returns a vector with the prime factors.
	*/
	std::vector<int> get_prime_factors(int number);
	/**
	* \brief Calculates two large factors which multiplied result in the number.
	* The function calculates the prime factors and multiplies the smallest factors until there are just factors left.
	* examples: 
	* number=8 => prime factors => 2*2*2 => resulting factors => 4*2
	* number=12 => prime factors => 2*2*3 => resulting factors => 4*3
	* \param number The number to calculate the factors from.
	* \return Returns a vector with the two factors.
	*/
	std::vector<int> get_two_large_factors(int number);
}
