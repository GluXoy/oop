#include <iostream>
#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primeNums;
	std::vector<bool> primes(upperBound, true);

	for (int i = 2; i * i <= upperBound; i++)
	{
		if (primes[i - 1] == true)
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				primes[j - 1] = false;
			}
		}
	}

	for (int i = 2; i <= upperBound; i++)
	{
		if (primes[i - 1])
		{
			primeNums.insert(i);
		}
	}

	return primeNums;
}