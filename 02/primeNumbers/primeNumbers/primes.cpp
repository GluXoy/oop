#include <iostream>
#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	std::set<int> primeNums;
	std::vector<bool> isPrimes(upperBound + 1, true);

	for (int i = 2; i * i <= upperBound; i++)
	{
		if (isPrimes[i] == true)
		{
			for (int j = i * i; j <= upperBound; j += i)
			{
				isPrimes[j] = false;
			}
		}
	}

	for (int i = 2; i <= upperBound; i++)
	{
		if (isPrimes[i])
		{
			primeNums.insert(primeNums.end(), i);
		}
	}

	return primeNums;
}