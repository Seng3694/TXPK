#include "MathHelper.h"
#include <math.h>

bool MathHelper::isPrime(const int &n) 
{
	for (int i = 2; i < sqrt(n); ++i) 
	{
		if (n % i == 0) 
			return false;
	}

	return true;
}