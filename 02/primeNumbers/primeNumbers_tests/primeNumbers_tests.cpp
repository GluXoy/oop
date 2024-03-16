#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../primeNumbers/primes.h"

TEST_CASE("GeneratePrimeNumbersSet test")
{
    SECTION("Test with lower bound")
    {
        std::set<int> expected = {};
        CHECK(GeneratePrimeNumbersSet(1) == expected);
    }

    SECTION("Test with one prime number in range")
    {
        std::set<int> expected = { 2 };
        CHECK(GeneratePrimeNumbersSet(2) == expected);
    }

    SECTION("Test with upperBound where many prime numbers")
    {
        std::set<int> expected = { 2, 3, 5, 7, 11 };
        CHECK(GeneratePrimeNumbersSet(11) == expected);
    }

    SECTION("Test with middle upperBound")
    {
        std::set<int> expected = GeneratePrimeNumbersSet(100);
        CHECK(expected.size() == 25);
    }

    SECTION("Test with max upper bound")
    {
        std::set<int> expected = GeneratePrimeNumbersSet(100000000);
        CHECK(expected.size() == 5761455);
    }

}