#define CATCH_CONFIG_MAIN
#include "../replace/stdafx.h"
#include "../../../catch2/catch.hpp"
#include "../replace/CopyFileAndReplace.h"

using namespace std;

SCENARIO("Replace strings")
{
    WHEN("Input file is empty")
    {
        istringstream input("");
        ostringstream output;
        string search = ("");
        string replacement = ("");

        THEN("Output file will be empty")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str().empty());
        }
    }

    WHEN("Replacing character with other character")
    {
        istringstream input("aaa");
        ostringstream output;
        string search = ("a");
        string replacement = ("b");

        THEN("search character will be changed to another character")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "bbb\n");
        }
    }

    WHEN("search string can repeats in input file after replacing")
    {
        istringstream input("abb");
        ostringstream output;
        string search = ("ab");
        string replacement = ("a");

        THEN("Output file's data will not be looped")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "ab\n");
        }
    }

    WHEN("Search string repeats in input file")
    {
        istringstream input("mama");
        ostringstream output;
        string search = ("ma");
        string replacement = ("mama");

        THEN("Output file's data will not be looped")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "mamamama\n");
        }
    }

    WHEN("Part of search string is substring of input data")
    {
        istringstream input("12312312345");
        ostringstream output;
        string search = ("1231234");
        string replacement = ("X");

        THEN("Output file will be correctly replace search strings")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "123X5\n");
        }
    }

    WHEN("Input file data contains an itself string and replace with the same string")
    {
        istringstream input("123");
        ostringstream output;
        string search = ("123");
        string replacement = ("123");

        THEN("All search strings will be saved")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "123\n");
        }
    }

    WHEN("Replacing non-empty string with empty string")
    {
        istringstream input("abc");
        ostringstream output;
        string search = ("abc");
        string replacement = ("");

        THEN("Search strings must be changed with empty strings")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "\n");
        }
    }

    WHEN("Replacing empty string with any characters")
    {
        istringstream input("aaa");
        ostringstream output;
        string search = ("");
        string replacement = ("123");

        THEN("Output file should return the same string")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "aaa\n");
        }
    }

    WHEN("Replacing newline character")
    {
        istringstream input("abc\n123");
        ostringstream output;
        string search = ("\n");
        string replacement = ("x");

        THEN("Output file should return the uncanged input data")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "abc\n123\n");
        }
    }

}