#include <iostream>
#include <set>
#include "primes.h"


int main()
{
	const int UPPER_BOUND = 100000000;
	const int LOWER_BOUND = 1;
	std::cout << "Enter number bound: ";
	int setBound;
	std::cin >> setBound;
	if (setBound > UPPER_BOUND || setBound < LOWER_BOUND)
	{
		std::cout << "Upper bound must be equal or less than: " << UPPER_BOUND << " and more than " << LOWER_BOUND << '\n';
		return 1;
	}
	std::set<int> primeNums = GeneratePrimeNumbersSet(setBound);
	std::cout << "Prime numbers amount: " << primeNums.size() << '\n';

	return 0;
}

