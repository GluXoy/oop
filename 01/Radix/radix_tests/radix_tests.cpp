#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Radix/Radix.h"


TEST_CASE("CharToInt converts characters to integers correctly", "[CharToInt]") {
    SECTION("Digits") {
        REQUIRE(CharToInt('0') == 0);
        REQUIRE(CharToInt('5') == 5);
        REQUIRE(CharToInt('9') == 9);
    }

    SECTION("Uppercase letters") {
        REQUIRE(CharToInt('A') == 10);
        REQUIRE(CharToInt('D') == 13);
        REQUIRE(CharToInt('Z') == 35);
    }

    SECTION("Lowercase letters") {
        REQUIRE(CharToInt('a') == 10);
        REQUIRE(CharToInt('d') == 13);
        REQUIRE(CharToInt('z') == 35);
    }

    SECTION("Invalid characters") {
        REQUIRE_THROWS_AS(CharToInt('$'), std::invalid_argument);
        REQUIRE_THROWS_AS(CharToInt(':'), std::invalid_argument);
        REQUIRE_THROWS_AS(CharToInt('Ш'), std::invalid_argument);
    }
}

TEST_CASE("IntToString converts integers to strings correctly", "[IntToString]") {
    SECTION("Decimal to binary") {
        REQUIRE(IntToString(10, 2) == "1010");
        REQUIRE(IntToString(15, 2) == "1111");
        REQUIRE(IntToString(16, 16) == "10");
    }

    SECTION("Decimal to hexadecimal") {
        REQUIRE(IntToString(26, 16) == "1A");
        REQUIRE(IntToString(255, 16) == "FF");
    }

    SECTION("Negative numbers") {
        REQUIRE(IntToString(-123, 10) == "-123");
        REQUIRE(IntToString(-10, 2) == "-1010");
        REQUIRE(IntToString(-26, 16) == "-1A");
    }

    SECTION("Zero") {
        REQUIRE(IntToString(0, 10) == "0");
        REQUIRE(IntToString(0, 2) == "0");
        REQUIRE(IntToString(0, 6) == "0");
        REQUIRE(IntToString(0, 8) == "0");
        REQUIRE(IntToString(0, 13) == "0");
        REQUIRE(IntToString(0, 16) == "0");
        REQUIRE(IntToString(0, 36) == "0");
    }
}

TEST_CASE("StringToInt converts strings to integers correctly", "[StringToInt]") {
    SECTION("Binary") {
        REQUIRE(StringToInt("1010", 2) == 10);
        REQUIRE(StringToInt("1111", 2) == 15);
    }

    SECTION("Decimal") {
        REQUIRE(StringToInt("123", 10) == 123);
        REQUIRE(StringToInt("0", 10) == 0);
    }

    SECTION("Hexadecimal") {
        REQUIRE(StringToInt("1A", 16) == 26);
        REQUIRE(StringToInt("FF", 16) == 255);
    }

    SECTION("Negative numbers") {
        REQUIRE(StringToInt("-123", 10) == -123);
        REQUIRE(StringToInt("-1010", 2) == -10);
        REQUIRE(StringToInt("-FF", 16) == -255);
    }

    SECTION("Invalid characters") {
        REQUIRE_THROWS_AS(StringToInt("120", 2), std::invalid_argument);
        REQUIRE_THROWS_AS(StringToInt("128", 8), std::invalid_argument);
        REQUIRE_THROWS_AS(StringToInt("FF", 10), std::invalid_argument);
        REQUIRE_THROWS_AS(StringToInt("12G", 16), std::invalid_argument);
        REQUIRE_THROWS_AS(StringToInt("ZZ", 34), std::invalid_argument);
    }
}