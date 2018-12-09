#include "TXPK/Math/MathExtension.hpp"

namespace txpk
{
	bool is_prime(int number)
	{
		if (number == 2) return true;
		if (number < 2 || number % 2 == 0) return false;

		for (unsigned int i = 3; i <= sqrt(number); i += 2)
		{
			if (number % i == 0)
				return false;
		}

		return true;
	}

	int largest_prime_factor(int number)
	{
		if (number < 2) return 1;
		if (is_prime(number)) return 1;

		for (unsigned int i = number / 2; i > 2; --i)
		{
			if (is_prime(i) && number % i == 0)
				return i;
		}

		return 2;
	}

	std::vector<int> get_prime_factors(int number)
	{
		std::vector<int> factors;
		if (number <= 3) return factors;

		for (unsigned int i = number / 2; i > 1; --i)
		{
			while (is_prime(i) && number % i == 0)
			{
				factors.push_back(i);
				number /= i;
			}
		}

		return factors;
	}

	//Gets all prime factors and multiplies them until there are only two factors left. The smallest factors are multiplied first.
	std::vector<int> get_two_large_factors(int number)
	{
		std::vector<int> factors = get_prime_factors(number);

		if (factors.size() == 0)
			return factors;

		std::sort(factors.begin(), factors.end(), [](const auto& lhs, const auto &rhs) { return lhs > rhs; });

		int value = 0;
		while (factors.size() > 2)
		{
			value = factors[factors.size() - 1];
			factors.pop_back();
			factors[factors.size() - 1] *= value;
			std::sort(factors.begin(), factors.end(), [](const auto& lhs, const auto &rhs) { return lhs > rhs; });
		}

		return factors;
	}
}
