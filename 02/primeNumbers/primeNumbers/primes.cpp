#include <iostream>
#include <set>
#include <vector>

std::set<int> GeneratePrimeNumbersSet(int upperBound)
{
	//каким образом хранятся значения в set
	std::set<int> primeNums;
	//поменять название
	std::vector<bool> primes(upperBound, true);

	//тесты не обнаруживают ошибку в этом условии
	for (int i = 2; i * i <= upperBound; i++)
	{
		//выделить на один элемент в массиве больше
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
			// ускорить вставку после прочтения про set
			primeNums.insert(i);
		}
	}

	return primeNums;
}