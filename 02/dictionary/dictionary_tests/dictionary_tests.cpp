#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../dictionary/translate.h"
#include <map>
#include <string>
#include <fstream>
#include <Windows.h> 

TEST_CASE("FillDictionary Test")
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    std::fstream file("test_file.txt", std::ios::out);
    file << "apple:яблоко\n";
    file << "banana:банан\n";
    file << "cat:кот\n";
    file << "cat:кошка\n";
    file.close();

    std::fstream testFile("test_file.txt", std::ios::in);
    std::multimap<std::string, std::string> dictionary = FillDictionary(testFile);

    SECTION("Check if dictionary is filled correctly")
    {
        CHECK(dictionary.size() == 4);
        CHECK(dictionary.find("apple")->second == "яблоко");
        CHECK(dictionary.find("banana")->second == "банан");
        auto range = dictionary.equal_range("cat");
        bool found = false;
        for (auto it = range.first; it != range.second; ++it)
        {
            if (it->second == "кот")
            {
                found = true;
                break;
            }
        }
        CHECK(found == true);
    }
}
