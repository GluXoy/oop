#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include "../MyString/CMyString.h"
#include <iostream>
#include <string>
#include <fstream>

TEST_CASE("check CMyString() constructor")
{
	CMyString str;
	std::stringstream output;
	output << str;
	CHECK(output.str() == "");
	CHECK(str.GetLength() == 0);
}

TEST_CASE("check CMyString(const char* pString) constructor")
{
	SECTION("with non-empty string must return the same string")
	{
		CMyString str("privet");

		std::stringstream output;
		output << str;
		CHECK(output.str() == "privet");
		CHECK(str.GetLength() == 6);
	}

	SECTION("with empty string must return the empty string")
	{
		CMyString str("", 0);

		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
		CHECK(str.GetLength() == 0);
	}
}

TEST_CASE("check CMyString(const char* pString, size_t length) constructor")
{
	SECTION("with non-empty string must return the same string")
	{
		const char data[] = { 'H', 'e', 'l', 'l', 'o', '\0', 'W', 'o', 'r', 'l', 'd' };
		size_t length = sizeof(data) / sizeof(data[0]);
		CMyString str(data, length);

		std::stringstream output;
		output << str;
		CHECK(output.str() == "HelloWorld");
		CHECK(str.GetLength() == length);
	}
}

TEST_CASE("check CMyString(std::string const& stlString) constructor")
{
	SECTION("with non-empty string")
	{
		std::string stlStr = "hello";
		CMyString str(stlStr);

		std::stringstream output;
		output << str;
		CHECK(output.str() == "hello");
		CHECK(str.GetLength() == 5);
	}

	SECTION("with empty string must return the empty string")
	{
		std::string stlStr;
		CMyString str(stlStr);

		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
		CHECK(str.GetLength() == 0);
	}
}

TEST_CASE("check CMyString(CMyString const& other) copy constructor")
{
	SECTION("with non-empty string must return the same string")
	{
		CMyString str1("123");
		CMyString str2(str1);

		std::stringstream output;
		output << str2;
		CHECK(output.str() == "123");
		CHECK(str2.GetLength() == 3);
	}

	SECTION("with empty string must return the empty string")
	{
		CMyString str1;
		CMyString str2(str1);

		std::stringstream output;
		output << str2;
		CHECK(output.str() == "");
		CHECK(str2.GetLength() == 0);
	}
}

TEST_CASE("check operator =")
{
	SECTION("assign another string to empty string")
	{
		CMyString assignedStr("45");
		CMyString str;
		str = assignedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "45");
		CHECK(str.GetLength() == 2);
	}

	SECTION("assign another string to non-empty string")
	{
		CMyString assignedStr("45");
		CMyString str("123");
		str = assignedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "45");
		CHECK(str.GetLength() == 2);
	}

	SECTION("assign the same string")
	{
		CMyString str("45");
		str = str;
	
		std::stringstream output;
		output << str;
		CHECK(output.str() == "45");
		CHECK(str.GetLength() == 2);
	}

	SECTION("assign another empty string to non-empty string")
	{
		CMyString assignedStr;
		CMyString str("123");
		str = assignedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
		CHECK(str.GetLength() == 0);
	}

	SECTION("assign another empty string to empty string")
	{
		CMyString assignedStr;
		CMyString str;
		str = assignedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
		CHECK(str.GetLength() == 0);
	}

	SECTION("assign result of adding other strings to empty string")
	{
		CMyString str1("123");
		CMyString str2("45");

		CMyString str3;
		str3 = str1 + str2;

		std::stringstream output;
		output << str3;
		CHECK(output.str() == "12345");
	}

	SECTION("assign result of adding other strings to non-empty string")
	{
		CMyString str1("123");
		CMyString str2("45");

		CMyString str3("0");
		str3 = str1 + str2;

		std::stringstream output;
		output << str3;
		CHECK(output.str() == "12345");
	}
}

TEST_CASE("check operator +=")
{
	SECTION("both strings are non-empty")
	{
		CMyString str("123");
		CMyString addedStr("45");
		str += addedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "12345");
		CHECK(str.GetLength() == 5);
	}

	SECTION("both strings are empty")
	{
		CMyString str;
		CMyString addedStr;
		str += addedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
		CHECK(str.GetLength() == 0);
	}

	SECTION("current string is non-empty and added string is empty")
	{
		CMyString str("123");
		CMyString addedStr;
		str += addedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "123");
		CHECK(str.GetLength() == 3);
	}

	SECTION("current string is empty and added string is non-empty")
	{
		CMyString str;
		CMyString addedStr("45");
		str += addedStr;

		std::stringstream output;
		output << str;
		CHECK(output.str() == "45");
		CHECK(str.GetLength() == 2);
	}
}

TEST_CASE("check operator +")
{
	SECTION("with CMyString argument")
	{
		CMyString str1("123");
		CMyString str2("45");
		
		std::stringstream output;
		output << str1 + str2;
		CHECK(output.str() == "12345");
	}
	
	SECTION("with string argument")
	{
		CMyString str1("123");
		std::string str2("45");

		std::stringstream output;
		output << str1 + str2;
		CHECK(output.str() == "12345");
	}

	SECTION("with char* argument")
	{
		CMyString str1("123");
		const char* str2 = "45";

		std::stringstream output;
		output << str1 + str2;
		CHECK(output.str() == "12345");
	}
}

TEST_CASE("check operator ==")
{
	SECTION("both string are equal; must return true")
	{
		CMyString str1("123");
		CMyString str2("123");

		REQUIRE(str1 == str2);
	}

	SECTION("strings are unequal; must return false")
	{
		CMyString str1("123");
		CMyString str2("124");

		REQUIRE(!(str1 == str2));
	}

	SECTION("one string is a strict substring of the other; must return false")
	{
		CMyString str1("123");
		CMyString str2("12");

		REQUIRE(!(str1 == str2));
	}

	SECTION("both strings are empty; must return true")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(str1 == str2);
	}
}

TEST_CASE("check operator !=")
{
	SECTION("both string are equal; must return false")
	{
		CMyString str1("123");
		CMyString str2("123");

		REQUIRE(!(str1 != str2));
	}

	SECTION("strings are unequal; must return true")
	{
		CMyString str1("123");
		CMyString str2("124");

		REQUIRE(str1 != str2);
	}

	SECTION("one string is a strict substring of the other; must return true")
	{
		CMyString str1("123");
		CMyString str2("12");

		REQUIRE(str1 != str2);
	}

	SECTION("both strings are empty; must return false")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(!(str1 != str2));
	}
}

TEST_CASE("check operator []")
{
	SECTION("check for reading if string isn't empty; must return char")
	{
		const CMyString str("123");
		REQUIRE(str[2] == '3');
	}

	SECTION("check for reading if string isn't empty and index more than string length; must throw exception")
	{
		const CMyString str("123");
		REQUIRE_THROWS_AS(str[3] == '3', std::out_of_range);
	}

	SECTION("check for reading if string is empty; must throw exception")
	{
		const CMyString str;
		REQUIRE_THROWS_AS(str[0] == '1', std::out_of_range);
	}

	SECTION("check for writing if string isn't empty; must return char")
	{
		CMyString str("123");
		REQUIRE(str[2] == '3');
	}

	SECTION("check for writing if string isn't empty and index more than string length; must throw exception")
	{
		CMyString str("123");
		REQUIRE_THROWS_AS(str[3] == '3', std::out_of_range);
	}

	SECTION("check for writing if string is empty; must throw exception")
	{
		CMyString str;
		REQUIRE_THROWS_AS(str[0] == '1', std::out_of_range);
	}

	SECTION("check for writing if string isn't empty and change char; must return changed string")
	{
		CMyString str("123");
		str[2] = '4';

		std::stringstream output;
		output << str;
		CHECK(output.str() == "124");
	}
}

TEST_CASE("check operator >")
{
	SECTION("two empty strings; return false")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(!(str2 > str1));
	}

	SECTION("two empty strings; return false")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(!(str1 > str2));
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(str2 > str1);
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(!(str1 > str2));
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(str2 > str1);
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(!(str1 > str2));
	}

	SECTION("two equal strings; return false")
	{
		CMyString str1("123");
		CMyString str2("123");

		REQUIRE(!(str2 > str1));
	}

	SECTION("one string is substring of an other string and it more in lexic order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(str1 > str2);
	}

	SECTION("one string is substring of an other string and it more in lexic order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(!(str2 > str1));
	}
}


TEST_CASE("check operator >=")
{
	SECTION("two empty strings; return true")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(str2 >= str1);
	}

	SECTION("two empty strings; return true")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(str1 >= str2);
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(str2 >= str1);
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(!(str1 >= str2));
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(str2 >= str1);
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(!(str1 >= str2));
	}

	SECTION("two equal strings; return true")
	{
		CMyString str1("123");
		CMyString str2("123");

		REQUIRE(str2 >= str1);
	}

	SECTION("one string is substring of another string and it more in lexical order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(str1 >= str2);
	}

	SECTION("one string is substring of an other string and it more in lexical order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(!(str2 >= str1));
	}
}


TEST_CASE("check operator <")
{
	SECTION("two empty strings; return false")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(!(str2 < str1));
	}

	SECTION("two empty strings; return false")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(!(str1 < str2));
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(!(str2 < str1));
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(str1 < str2);
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(str1 < str2);
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(!(str2 < str1));
	}

	SECTION("two equal strings; return false")
	{
		CMyString str1("123");
		CMyString str2("123");

		REQUIRE(!(str2 < str1));
	}

	SECTION("one string is substring of an other string and it more in lexic order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(str2 < str1);
	}

	SECTION("one string is substring of an other string and it more in lexic order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(!(str1 < str2));
	}
}

TEST_CASE("check operator <=")
{
	SECTION("two empty strings; return true")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(str1 <= str2);
	}

	SECTION("two empty strings; return true")
	{
		CMyString str1;
		CMyString str2;

		REQUIRE(str2 <= str1);
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(str1 <= str2);
	}

	SECTION("one string is empty and other string is non-empty")
	{
		CMyString str1;
		CMyString str2("1");
		REQUIRE(!(str2 <= str1));
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(str1 <= str2);
	}

	SECTION("two different strings with the same length; must return string with more lexic order value")
	{
		CMyString str1("123");
		CMyString str2("456");

		REQUIRE(!(str2 <= str1));
	}

	SECTION("two equal strings; return true")
	{
		CMyString str1("123");
		CMyString str2("123");

		REQUIRE(str2 <= str1);
	}

	SECTION("one string is substring of another string and it more in lexical order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(str2 <= str1);
	}

	SECTION("one string is substring of an other string and it more in lexical order than longer string")
	{
		CMyString str1("123");
		CMyString str2("1234");

		REQUIRE(!(str1 <= str2));
	}
}

TEST_CASE("RValue manipulations")
{
	SECTION("operator = for RValue must called")
	{
		CMyString str1("123");
		CMyString str2("45");
		CMyString str3;
		str3 = str1 + str2;

		std::stringstream output;
		output << str3;
		CHECK(output.str() == "12345");
	}

	SECTION("check moving constructor")
	{
		CMyString str1("123");
		CMyString str2("45");
		CMyString str3(std::move(str1 + str2));

		std::stringstream output;
		output << str3;
		CHECK(output.str() == "12345");
	}
}


TEST_CASE("check substring() method") 
{
	SECTION("start position is 0 and substring length = string length")
	{
		CMyString str("0123");
		CMyString subStr = str.SubString(0, str.GetLength());

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "0123");
	}

	SECTION("start position is 1 and substring length is 2")
	{
		CMyString str("0123");
		CMyString subStr = str.SubString(1, 2);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "12");
	}

	SECTION("start position is 2 and substring length is more than remaining string length")
	{
		CMyString str("0123");
		CMyString subStr = str.SubString(2, 10);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "23");
	}

	SECTION("start position is 3 and default substring length (to end of string)")
	{
		CMyString str("0123");
		CMyString subStr = str.SubString(3);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "3");
	}

	SECTION("start position is out of range must return empty string")
	{
		CMyString str("0123");
		CMyString subStr = str.SubString(4);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "");
	}

	SECTION("substring of an empty string")
	{
		CMyString str;
		CMyString subStr = str.SubString(0);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "");
	}

	SECTION("substring of an empty string with start index > 0")
	{
		CMyString str;
		CMyString subStr = str.SubString(1);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "");
	}

	SECTION("substring with length 0")
	{
		CMyString str("0123");
		CMyString subStr = str.SubString(2, 0);

		std::stringstream output;
		output << subStr;
		CHECK(output.str() == "");
	}
}

TEST_CASE("check clear() method")
{
	SECTION("string must be empty after using clear() method")
	{
		CMyString str("123");
		str.Clear();
		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
	}

	SECTION("empty string must be empty after using clear() method")
	{
		CMyString str;
		str.Clear();
		std::stringstream output;
		output << str;
		CHECK(output.str() == "");
	}
}


TEST_CASE("check GetStringData() method")
{
	SECTION("empty string; must return empty data string")
	{
		CMyString str;
		CHECK(std::strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("non-empty string; must return non-empty data string")
	{
		CMyString str("123");
		const char* data = "123";
		CHECK(std::strcmp(str.GetStringData(), data) == 0);
	}
}


TEST_CASE("check operator>>")
{
	SECTION("input empty string using operator>>") 
	{
		CMyString str;
		std::istringstream input("");
		input >> str;
		CHECK(std::strcmp(str.GetStringData(), "") == 0);
	}

	SECTION("input non-empty string using operator>>")
	{
		CMyString str;
		std::istringstream input("Hello, world!");
		input >> str;
		CHECK(std::strcmp(str.GetStringData(), "Hello, world!") == 0);
	}

	SECTION("input string with leading and trailing spaces using operator>>")
	{
		CMyString str;
		std::istringstream input("  Hello, world!  ");
		input >> str;
		CHECK(std::strcmp(str.GetStringData(), "  Hello, world!  ") == 0);
	}

	SECTION("multiple inputs using operator>>")
	{
		CMyString str1, str2;
		std::istringstream input("Hello\nworld");
		input >> str1;
		input >> str2;
		CHECK(std::strcmp(str1.GetStringData(), "Hello") == 0);
		CHECK(std::strcmp(str2.GetStringData(), "world") == 0);
	}

	SECTION("input long string using operator>>")
	{
		CMyString str;
		std::istringstream input("This is a very long string used for testing the input operator.");
		input >> str;
		CHECK(std::strcmp(str.GetStringData(), "This is a very long string used for testing the input operator.") == 0);
	}
}