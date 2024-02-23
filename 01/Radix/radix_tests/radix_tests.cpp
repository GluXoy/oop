#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../Radix/Radix.h"

const int RADIX_MIN = 2;
const int RADIX_MAX = 36;

SCENARIO("Converting positive numbers from any base to base 10")
{
    int destinationNotation = 10;

    WHEN("Converting positive number from base 2")
    {
        int sourceNotation = 2;
        std::string value = "1010";

        THEN("Result should be in correct 10 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "10");
        }
    }

    WHEN("Converting positive number from base 16")
    {
        int sourceNotation = 16;
        std::string value = "FF";

        THEN("Result should be in correct 10 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "255");
        }
    }

    WHEN("Converting positive number from base 2")
    {
        int sourceNotation = 36;
        std::string value = "ZZ";

        THEN("Result should be in correct 10 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "1295");
        }
    }
}

SCENARIO("Converting positive numbers from base 10 to another base")
{
    int sourceNotation = 10;

    WHEN("Converting positive number from base 10")
    {
        int destinationNotation = 2;
        std::string value = "10";

        THEN("Result should be in correct 2 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "1010");
        }
    }

    WHEN("Converting positive number from base 10")
    {
        int destinationNotation = 16;
        std::string value = "255";

        THEN("Result should be in correct 16 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "FF");
        }
    }

    WHEN("Converting positive number from base 10")
    {
        int destinationNotation = 36;
        std::string value = "1295";

        THEN("Result should be in correct 36 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "ZZ");
        }
    }
}

SCENARIO("Converting positive numbers from one non-10 base to another non-10 base")
{
    WHEN("Converting positive number from base 8")
    {
        int sourceNotation = 8;
        int destinationNotation = 16;
        std::string value = "123";

        THEN("Result should be in correct 16 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "53");
        }
    }

    WHEN("Converting positive number from base 16")
    {
        int sourceNotation = 16;
        int destinationNotation = 2;
        std::string value = "123";

        THEN("Result should be in correct 2 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "100100011");
        }
    }

    WHEN("Converting positive number from base 2")
    {
        int sourceNotation = 2;
        int destinationNotation = 36;
        std::string value = "110001011";

        THEN("Result should be in correct 36 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "AZ");
        }
    }
}

SCENARIO("Converting negative numbers")
{
    WHEN("Converting negative number from base 2")
    {
        int sourceNotation = 2;
        int destinationNotation = 10;
        std::string value = "-1001";

        THEN("Result should be in correct negative 10 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "-9");
        }
    }

    WHEN("Converting negative number from base 16")
    {
        int sourceNotation = 16;
        int destinationNotation = 10;
        std::string value = "-FF";

        THEN("Result should be in correct negative 10 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "-255");
        }
    }

    WHEN("Converting negative number from base 36")
    {
        int sourceNotation = 36;
        int destinationNotation = 10;
        std::string value = "-ZZ";

        THEN("Result should be in correct negative 10 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "-1295");
        }
    }

    WHEN("Converting negative number from base 10")
    {
        int sourceNotation = 10;
        int destinationNotation = 16;
        std::string value = "-123";

        THEN("Result should be in correct negative 16 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "-7B");
        }
    }
}

SCENARIO("Checking for overflow")
{
    WHEN("Converting MAX_INT number from base 10")
    {
        int sourceNotation = 10;
        int destinationNotation = 16;
        std::string value = "2147483647";

        THEN("Result should be in correct positive 16 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "7FFFFFFF");
        }
    }

    WHEN("Converting MAX_INT + 1 number from base 10")
    {
        int sourceNotation = 10;
        int destinationNotation = 16;
        std::string value = "2147483648";

        THEN("Overflow error")
        {
            REQUIRE_THROWS_AS(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX), std::overflow_error);
        }
    }

    WHEN("Converting MIN_INT number from base 10")
    {
        int sourceNotation = 10;
        int destinationNotation = 16;
        std::string value = "-2147483648";

        THEN("Result should be in correct negative 16 base form")
        {
            REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX) == "-80000000");
        }
    }

    WHEN("Converting MIN_INT - 1 number from base 10")
    {
        int sourceNotation = 10;
        int destinationNotation = 16;
        std::string value = "-2147483649";

        THEN("Overflow error")
        {
            REQUIRE_THROWS_AS(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX), std::overflow_error);
        }
    }
}

SCENARIO("Checking for correct input source notation with number")
{
    WHEN("Any digit in number more than source notation")
    {
        int sourceNotation = 2;
        int destinationNotation = 16;
        std::string value = "1211";

        THEN("Error message: Invalid number format")
        {
            REQUIRE_THROWS_AS(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX), std::invalid_argument);
        }
    }
}

SCENARIO("Converting invalid input")
{
    WHEN("Invalid input symbols")
    {
        int sourceNotation = 2;
        int destinationNotation = 16;
        std::string value = "11$1";

        THEN("Error message: Invalid number format")
        {
            REQUIRE_THROWS_AS(ConvertNotation(sourceNotation, destinationNotation, value, RADIX_MAX), std::invalid_argument);
        }
    }
}

    //WHEN("Converting negative number from base 16 to base 8") {
    //    int sourceNotation = 16;
    //    int destinationNotation = 8;
    //    std::string value = "-FF";
    //    std::string expected_result = "-377";
    //    THEN("Result should be octal representation") {
    //        REQUIRE(ConvertNotation(sourceNotation, destinationNotation, value, 16) == expected_result);
    //    }
    //}

    //WHEN("Converting invalid input") {
    //    int sourceNotation = 10;
    //    int destinationNotation = 2;
    //    std::string value = "1Z";
    //    THEN("Exception should be thrown") {
    //        REQUIRE_THROWS_AS(ConvertNotation(sourceNotation, destinationNotation, value, 16), std::invalid_argument);
    //    }
    //}
