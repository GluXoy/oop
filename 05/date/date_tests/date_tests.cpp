#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include <set>
#include "../date/CDate.h"

bool IsLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

//TEST_CASE("Checking date methods every year in January")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::JANUARY, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::JANUARY);
//			
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in February")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 28; day++)
//		{
//			CDate date(day, Month::FEBRUARY, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::FEBRUARY);
//			REQUIRE(date.GetDay() == day);
//		}
//
//		if (IsLeapYear(year))
//		{
//			CDate date(29, Month::FEBRUARY, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::FEBRUARY);
//			REQUIRE(date.GetDay() == 29);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in March")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::MARCH, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::MARCH);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in April")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 30; day++)
//		{
//			CDate date(day, Month::APRIL, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::APRIL);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in May")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::MAY, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::MAY);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in June")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 30; day++)
//		{
//			CDate date(day, Month::JUNE, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::JUNE);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in July")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::JULY, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::JULY);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in August")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::AUGUST, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::AUGUST);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in September")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 30; day++)
//		{
//			CDate date(day, Month::SEPTEMBER, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::SEPTEMBER);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in October")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::OCTOBER, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::OCTOBER);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in November")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 30; day++)
//		{
//			CDate date(day, Month::NOVEMBER, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::NOVEMBER);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}
//
//TEST_CASE("Checking date methods every year in December")
//{
//	for (int year = 1970; year <= 9999; ++year)
//	{
//		for (int day = 1; day <= 31; day++)
//		{
//			CDate date(day, Month::DECEMBER, year);
//			unsigned int getyear = date.GetYear();
//			REQUIRE(getyear == year);
//			REQUIRE(date.GetMonth() == Month::DECEMBER);
//			REQUIRE(date.GetDay() == day);
//		}
//	}
//}


TEST_CASE("check CDate-constructor initialized first day without parameters")
{
	CDate date;
	unsigned int getyear = date.GetYear();
	REQUIRE(getyear == 1970);
	REQUIRE(date.GetMonth() == Month::JANUARY);
	REQUIRE(date.GetDay() == 1);
}

TEST_CASE("check CDate-constructor initialized with day-parameter")
{
	SECTION("Start day")
	{
		CDate date(0);
		CHECK(date.GetDay() == 1);
		CHECK(date.GetMonth() == Month::JANUARY);
		CHECK(date.GetYear() == 1970);
	}

	SECTION("Another day")
	{
		CDate date(2);
		unsigned int getyear = date.GetYear();
		REQUIRE(getyear == 1970);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetDay() == 3);
	}
}

TEST_CASE("check CDate constructor with timestamp throws exceptions")
{
    const unsigned int DAYS_TO_END_YEAR = 9999 * 365 + 2424;
    const unsigned int DAYS_TO_BEGIN_YEAR = (1970 - 1) * 365 + 477;

	SECTION("Final day")
	{
		CDate endDate(DAYS_TO_END_YEAR - DAYS_TO_BEGIN_YEAR - 1);
		CHECK(endDate.GetDay() == 31);
		CHECK(endDate.GetMonth() == Month::DECEMBER);
		CHECK(endDate.GetYear() == 9999);
	}


    REQUIRE_THROWS_AS(CDate(DAYS_TO_END_YEAR - DAYS_TO_BEGIN_YEAR), std::out_of_range);
    REQUIRE_THROWS_AS(CDate(-1), std::out_of_range);
}

TEST_CASE("check CDate constructor with date throws exceptions")
{
    REQUIRE_THROWS_AS(CDate(32, Month::JANUARY, 2000), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(0, Month::JANUARY, 2000), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(31, Month::FEBRUARY, 2000), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(30, Month::FEBRUARY, 2001), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(31, Month::APRIL, 2000), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(15, Month::JANUARY, 10000), std::invalid_argument);
    REQUIRE_THROWS_AS(CDate(15, Month::JANUARY, 0), std::invalid_argument);
}

TEST_CASE("Checking operators")
{
	SECTION("Checking addition (+)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		unsigned int addition = 2;
		CDate d2 = d1 + addition;
		REQUIRE(d2.GetDay() == 3);
		REQUIRE(d2.GetMonth() == Month::JANUARY);
		REQUIRE(d2.GetYear() == 1970);
	}

	SECTION("Checking subtraction with offset (-)")
	{
		CDate d1(3, Month::JANUARY, 1970);
		unsigned int subtraction = 2;
		CDate d2 = d1 - subtraction;
		REQUIRE(d2.GetDay() == 1);
		REQUIRE(d2.GetMonth() == Month::JANUARY);
		REQUIRE(d2.GetYear() == 1970);
	}

	SECTION("Checking subtraction with another date (-)")
	{
		CDate d1(5, Month::JANUARY, 1970);
		CDate d2(1, Month::JANUARY, 1970);
		int difference = d1 - d2;
		REQUIRE(difference == 4);
	}

	SECTION("Checking subtraction with another date where first date is less than second (-)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2(5, Month::JANUARY, 1970);
		int difference = d1 - d2;
		REQUIRE(difference == -4);
	}

	SECTION("Checking addition assignment (+=)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		unsigned int addition = 2;
		d1 += addition;
		REQUIRE(d1.GetDay() == 3);
		REQUIRE(d1.GetMonth() == Month::JANUARY);
		REQUIRE(d1.GetYear() == 1970);
	}

	SECTION("Checking subtraction assignment (-=)")
	{
		CDate d1(3, Month::JANUARY, 1970);
		unsigned int subtraction = 2;
		d1 -= subtraction;
		REQUIRE(d1.GetDay() == 1);
		REQUIRE(d1.GetMonth() == Month::JANUARY);
		REQUIRE(d1.GetYear() == 1970);
	}

	SECTION("Checking equality (==)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2(1, Month::JANUARY, 1970);
		CDate d3(2, Month::JANUARY, 1970);
		REQUIRE(d1 == d2);
		REQUIRE(!(d2 == d3));
	}

	SECTION("Checking inequality (!=)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2(1, Month::JANUARY, 1970);
		CDate d3(2, Month::JANUARY, 1970);
		REQUIRE(d1 != d3);
		REQUIRE(!(d1 != d2));
	}

	//допилить тесты сравнения

	SECTION("Checking less than (<)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2(1, Month::JANUARY, 1970);
		CDate d3(2, Month::JANUARY, 1970);
		CDate d4(3, Month::JANUARY, 1970);

		REQUIRE(!(d3 < d2));
		REQUIRE(!(d2 < d1));
		REQUIRE(d3 < d4);
	}

	SECTION("Checking greater than (>)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2(1, Month::JANUARY, 1970);
		CDate d3(2, Month::JANUARY, 1970);
		CDate d4(3, Month::JANUARY, 1970);

		REQUIRE(d3 > d2);
		REQUIRE(!(d2 > d1));
		REQUIRE(!(d3 > d4));
	}

	SECTION("Checking less than or equal (<=)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2(2, Month::JANUARY, 1970);
		CDate d3(1, Month::JANUARY, 1970);
		REQUIRE(d1 <= d2);
		REQUIRE(d1 <= d3);
		REQUIRE(!(d2 <= d1));
	}

	SECTION("Checking greater than or equal (>=)")
	{
		CDate d1(2, Month::JANUARY, 1970);
		CDate d2(1, Month::JANUARY, 1970);
		CDate d3(2, Month::JANUARY, 1970);
		REQUIRE(d1 >= d2);
		REQUIRE(d1 >= d3);
		REQUIRE(!(d2 >= d1));
	}

	SECTION("Checking prefix increment (++)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		++d1;
		REQUIRE(d1.GetDay() == 2);
		REQUIRE(d1.GetMonth() == Month::JANUARY);
		REQUIRE(d1.GetYear() == 1970);
	}

	SECTION("Checking postfix increment (++)")
	{
		CDate d1(1, Month::JANUARY, 1970);
		CDate d2 = d1++;
		REQUIRE(d1.GetDay() == 2);
		REQUIRE(d1.GetMonth() == Month::JANUARY);
		REQUIRE(d1.GetYear() == 1970);
		REQUIRE(d2.GetDay() == 1);
		REQUIRE(d2.GetMonth() == Month::JANUARY);
		REQUIRE(d2.GetYear() == 1970);
	}

	SECTION("Checking prefix decrement (--)")
	{
		CDate d1(2, Month::JANUARY, 1970);
		--d1;
		REQUIRE(d1.GetDay() == 1);
		REQUIRE(d1.GetMonth() == Month::JANUARY);
		REQUIRE(d1.GetYear() == 1970);
	}

	SECTION("Checking postfix decrement (--)")
	{
		CDate d1(2, Month::JANUARY, 1970);
		CDate d2 = d1--;
		REQUIRE(d1.GetDay() == 1);
		REQUIRE(d1.GetMonth() == Month::JANUARY);
		REQUIRE(d1.GetYear() == 1970);
		REQUIRE(d2.GetDay() == 2);
		REQUIRE(d2.GetMonth() == Month::JANUARY);
		REQUIRE(d2.GetYear() == 1970);
	}

	SECTION("Output operator (<<)")
	{
		CDate validDate(1, Month::JANUARY, 1970);
		std::ostringstream os;
		os << validDate;
		REQUIRE(os.str() == "01/01/1970");

		CDate date(1, Month::JANUARY, 1970);
		date -= 1;
		std::ostringstream osInvalid;
		osInvalid << date;
		REQUIRE(osInvalid.str() == "INVALID");
	}

	SECTION("Input operator (>>)")
	{
		std::istringstream is("01/01/1970");
		CDate date;
		is >> date;
		REQUIRE(date.GetDay() == 1);
		REQUIRE(date.GetMonth() == Month::JANUARY);
		REQUIRE(date.GetYear() == 1970);
	}
}

TEST_CASE("Check weekday")
{
	CDate date1(18, Month::MAY, 2400);
	CDate date2(18, Month::MAY, 2024);
	unsigned int result = date1 - date2;
	REQUIRE(result == 137331);
	REQUIRE(date2 + result == date1);

	//должна быть возможность складывать дни с датами в обоих порядках
	REQUIRE(result + date2 == date1);
	REQUIRE(date2.GetDay() == 18);
	REQUIRE(date2.GetMonth() == Month::MAY);
	REQUIRE(date2.GetYear() == 2024);

	REQUIRE(date2.GetWeekDay() == WeekDay::SATURDAY);
}
