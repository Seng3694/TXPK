#include <catch2/catch.hpp>

#include <TXPK/Math/MathExtension.hpp>

TEST_CASE("is_prime test", "[TXPK/Math/MathExtension]")
{
	REQUIRE(txpk::is_prime(0) == false);
	REQUIRE(txpk::is_prime(1) == false);
	REQUIRE(txpk::is_prime(2) == true);
	REQUIRE(txpk::is_prime(3) == true);
	REQUIRE(txpk::is_prime(4) == false);
	REQUIRE(txpk::is_prime(5) == true);
	REQUIRE(txpk::is_prime(6) == false);
	REQUIRE(txpk::is_prime(7) == true);
	REQUIRE(txpk::is_prime(8) == false);
	REQUIRE(txpk::is_prime(9) == false);
	REQUIRE(txpk::is_prime(10) == false);
	REQUIRE(txpk::is_prime(11) == true);
	REQUIRE(txpk::is_prime(12) == false);
	REQUIRE(txpk::is_prime(13) == true);
	REQUIRE(txpk::is_prime(14) == false);
	REQUIRE(txpk::is_prime(15) == false);
	REQUIRE(txpk::is_prime(16) == false);
	REQUIRE(txpk::is_prime(17) == true);
	REQUIRE(txpk::is_prime(18) == false);
}

TEST_CASE("largest_prime_factor test", "[TXPK/Math/MathExtension]")
{
	REQUIRE(txpk::largest_prime_factor(0) == 1);
	REQUIRE(txpk::largest_prime_factor(1) == 1);
	REQUIRE(txpk::largest_prime_factor(2) == 1);
	REQUIRE(txpk::largest_prime_factor(3) == 1);
	REQUIRE(txpk::largest_prime_factor(4) == 2);
	REQUIRE(txpk::largest_prime_factor(5) == 1);
	REQUIRE(txpk::largest_prime_factor(6) == 3);
	REQUIRE(txpk::largest_prime_factor(7) == 1);
	REQUIRE(txpk::largest_prime_factor(8) == 2);
	REQUIRE(txpk::largest_prime_factor(9) == 3);
	REQUIRE(txpk::largest_prime_factor(10) == 5);
	REQUIRE(txpk::largest_prime_factor(11) == 1);
	REQUIRE(txpk::largest_prime_factor(12) == 3);
	REQUIRE(txpk::largest_prime_factor(13) == 1);
	REQUIRE(txpk::largest_prime_factor(14) == 7);
	REQUIRE(txpk::largest_prime_factor(15) == 5);
	REQUIRE(txpk::largest_prime_factor(16) == 2);
	REQUIRE(txpk::largest_prime_factor(17) == 1);
	REQUIRE(txpk::largest_prime_factor(18) == 3);
}

TEST_CASE("get_prime_factors test", "[TXPK/Math/MathExtension]")
{
	auto factors = txpk::get_prime_factors(0);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_prime_factors(1);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_prime_factors(2);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_prime_factors(3);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_prime_factors(4);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 2);
	REQUIRE(factors[1] == 2);

	factors = txpk::get_prime_factors(5);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_prime_factors(6);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 3);
	REQUIRE(factors[1] == 2);

	factors = txpk::get_prime_factors(7);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_prime_factors(8);
	REQUIRE(factors.size() == 3);
	REQUIRE(factors[0] == 2);
	REQUIRE(factors[1] == 2);
	REQUIRE(factors[2] == 2);

	factors = txpk::get_prime_factors(9);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 3);
	REQUIRE(factors[1] == 3);

	factors = txpk::get_prime_factors(10);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 5);
	REQUIRE(factors[1] == 2);

	int product = 1;
	for (int i = 0; i < 1000; ++i)
	{
		factors = txpk::get_prime_factors(i);
		if (factors.size() > 0)
		{
			product = 1;
			for (auto &factor : factors)
				product *= factor;

			REQUIRE(product == i);
		}
	}
}

TEST_CASE("get_two_large_factors test", "[TXPK/Math/MathExtension]")
{
	auto factors = txpk::get_two_large_factors(0);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_two_large_factors(1);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_two_large_factors(2);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_two_large_factors(3);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_two_large_factors(4);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 2);
	REQUIRE(factors[1] == 2);

	factors = txpk::get_two_large_factors(5);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_two_large_factors(6);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 3);
	REQUIRE(factors[1] == 2);

	factors = txpk::get_two_large_factors(7);
	REQUIRE(factors.size() == 0);

	factors = txpk::get_two_large_factors(8);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 4);
	REQUIRE(factors[1] == 2);

	factors = txpk::get_two_large_factors(9);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 3);
	REQUIRE(factors[1] == 3);

	factors = txpk::get_two_large_factors(10);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 5);
	REQUIRE(factors[1] == 2);

	factors = txpk::get_two_large_factors(16);
	REQUIRE(factors.size() == 2);
	REQUIRE(factors[0] == 4);
	REQUIRE(factors[1] == 4);

	int product = 1;
	for (int i = 0; i < 1000; ++i)
	{
		factors = txpk::get_two_large_factors(i);
		if (factors.size() > 0)
		{
			REQUIRE(factors.size() == 2);

			product = 1;
			for (auto &factor : factors)
				product *= factor;

			REQUIRE(product == i);
		}
	}
}

TEST_CASE("MAX test", "[TXPK/Math/MathExtension]")
{
	REQUIRE(MAX(10, 20) == 20);
	REQUIRE(MAX(20, 10) == 20);
	REQUIRE(MAX(10, 10) == 10);
	REQUIRE(MAX(-10, 10) == 10);
	REQUIRE(MAX(-10, -5) == -5);
}

TEST_CASE("MIN test", "[TXPK/Math/MathExtension]")
{
	REQUIRE(MIN(10, 20) == 10);
	REQUIRE(MIN(20, 10) == 10);
	REQUIRE(MIN(10, 10) == 10);
	REQUIRE(MIN(-10, 10) == -10);
	REQUIRE(MIN(-10, -5) == -10);
}
