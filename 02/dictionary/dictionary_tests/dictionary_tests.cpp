#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/translate.h"
#include <map>
#include <string>
#include <fstream>
#include <Windows.h> 


TEST_CASE("PrintTranslatedWord prints correct translation")
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Dictionary testDictionary;
    testDictionary.emplace("hello", "привет");
    testDictionary.emplace("The Red Square", "Красная площадь");
    testDictionary.emplace("cat", "кот");
    testDictionary.emplace("cat", "кошка");

    SECTION("Existing word")
    {
        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        PrintTranslatedWord(testDictionary, "hello");
        std::cout.rdbuf(oldCout);
        CHECK(output.str() == "привет\n");
    }

    SECTION("Checking many translations of one word")
    {
        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        PrintTranslatedWord(testDictionary, "cat");
        std::cout.rdbuf(oldCout);
        CHECK(output.str() == "кот, кошка\n"); 
    }

    SECTION("Checking if spaces in word")
    {
        std::stringstream output;
        std::streambuf* oldCout = std::cout.rdbuf();
        std::cout.rdbuf(output.rdbuf());

        PrintTranslatedWord(testDictionary, "The Red Square");
        std::cout.rdbuf(oldCout);
        CHECK(output.str() == "Красная площадь\n");
    }
}