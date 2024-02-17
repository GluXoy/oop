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

    WHEN("Replacing single character with multiple characters")
    {
        istringstream input("a");
        ostringstream output;
        string search = ("a");
        string replacement = ("aa");

        THEN("Output file will be aa\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "aa\n");
        }
    }

    WHEN("Input data will not be looped: 1")
    {
        istringstream input("abb");
        ostringstream output;
        string search = ("ab");
        string replacement = ("a");

        THEN("Output file will be ab\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "ab\n");
        }
    }

    WHEN("Input data will not be looped: 2")
    {
        istringstream input("mama");
        ostringstream output;
        string search = ("ma");
        string replacement = ("mama");

        THEN("Output file will be mamamama\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "mamamama\n");
        }
    }

    WHEN("Input file is not empty")
    {
        istringstream input("12312312345");
        ostringstream output;
        string search = ("1231234");
        string replacement = ("X");

        THEN("Output file will be 123X5")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "123X5\n");
        }
    }

    WHEN("Input file data contains an itself string and replace with the same string")
    {
        istringstream input("apple");
        ostringstream output;
        string search = ("apple");
        string replacement = ("apple");

        THEN("Output file is apple\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "apple\n");
        }
    }

    WHEN("Replacing non-empty string with empty string")
    {
        istringstream input("abc");
        ostringstream output;
        string search = ("abc");
        string replacement = ("");

        THEN("Output file is \n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "\n");
        }
    }

    WHEN("Replacing non-empty substring with empty string")
    {
        istringstream input("1abc1");
        ostringstream output;
        string search = ("abc");
        string replacement = ("");

        THEN("Output file is 11\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "11\n");
        }
    }

    WHEN("Replacing empty string with any argiment")
    {
        istringstream input("aaaaaa");
        ostringstream output;
        string search = ("");
        string replacement = ("xxx");

        THEN("Output file should return the same string: aaaaaa\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "aaaaaa\n");
        }
    }

    WHEN("Input data contains the search string at the beginning of the line") {
        istringstream input("apple\nbanana\n");
        ostringstream output;
        string search = "apple";
        string replacement = "orange";

        THEN("Output file should contain 'orange\nbanana\n'") {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "orange\nbanana\n");
        }
    }

    WHEN("Input data contains the search string at the end of the line") {
        istringstream input("banana apple\norange apple");
        ostringstream output;
        string search = "apple";
        string replacement = "banana";

        THEN("Output file should contain 'banana banana\norange banana'") {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "banana banana\norange banana\n");
        }
    }

    WHEN("Replacing newline character")
    {
        istringstream input("abc\n123");
        ostringstream output;
        string search = ("\n");
        string replacement = ("xxx");

        THEN("Output file should be: abc\n123\n")
        {
            CopyStreamWithReplacement(input, output, search, replacement);
            REQUIRE(output.str() == "abc\n123\n");
        }
    }

}