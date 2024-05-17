#define CATCH_CONFIG_MAIN
#include "../../../catch2/catch.hpp"
#include <iostream>
#include <set>
#include "../date/CDate.h"

bool isLeapYear(int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

TEST_CASE("Checking GetYear method every year in January")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::JANUARY, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::JANUARY);
			
		}
	}
}

TEST_CASE("Checking GetYear method every year in February")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 28; day++)
		{
			CDate date(day, Month::FEBRUARY, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::FEBRUARY);
			REQUIRE(date.GetDay() == day);
		}

		if (isLeapYear(year))
		{
			CDate date(29, Month::FEBRUARY, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::FEBRUARY);
			REQUIRE(date.GetDay() == 29);
		}
	}
}

TEST_CASE("Checking GetYear method every year in March")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::MARCH, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::MARCH);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in April")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 30; day++)
		{
			CDate date(day, Month::APRIL, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::APRIL);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in May")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::MAY, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::MAY);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in June")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 30; day++)
		{
			CDate date(day, Month::JUNE, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::JUNE);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in July")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::JULY, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::JULY);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in August")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::AUGUST, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::AUGUST);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in September")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 30; day++)
		{
			CDate date(day, Month::SEPTEMBER, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::SEPTEMBER);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in October")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::OCTOBER, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::OCTOBER);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in November")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 30; day++)
		{
			CDate date(day, Month::NOVEMBER, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::NOVEMBER);
			REQUIRE(date.GetDay() == day);
		}
	}
}

TEST_CASE("Checking GetYear method every year in December")
{
	for (int year = 1970; year <= 9999; ++year)
	{
		for (int day = 1; day <= 31; day++)
		{
			CDate date(day, Month::DECEMBER, year);
			unsigned int getyear = date.GetYear();
			REQUIRE(getyear == year);
			REQUIRE(date.GetMonth() == Month::DECEMBER);
			REQUIRE(date.GetDay() == day);
		}
	}
}



//bool IsLeapYear(unsigned int year)
//{
//	if (year % 4 == 0)
//	{
//		if (year % 100 == 0)
//		{
//			if (year % 400 == 0)
//			{
//				return true;
//			}
//		}
//		else
//		{
//			return true;
//		}
//	}
//
//	return false;
//}

//TEST_CASE("Checking")
//{
//
//	std::set<unsigned int> leaps;
//	for (unsigned int year = 1; year <= 9999; ++year)
//	{
//		if (IsLeapYear(year))
//		{
//			leaps.insert(year);
//		}
//	}
//
//	std::cout << leaps.size() << std::endl;

	//for (const auto& y : leaps)
	//{
	//	std::cout << y << ' ';
	//}
//}


int daysInMonth(int month, bool leapYear) {
	static const int days_in_month[2][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};
	return days_in_month[leapYear ? 1 : 0][month - 1];
}

int daysSinceEpoch(int year, int month, int day) {
	int days = 0;

	// Считаем количество дней в полных годах
	for (int y = 1; y < year; ++y) {
		days += isLeapYear(y) ? 366 : 365;
	}

	// Считаем количество дней в полных месяцах текущего года
	for (int m = 1; m < month; ++m) {
		days += daysInMonth(m, isLeapYear(year));
	}

	// Добавляем дни текущего месяца
	days += day;

	return days;
}

TEST_CASE("")
{
	//int year = 5019;
	//int month = 12;
	//int day = 31;
	//int total_days = daysSinceEpoch(year, month, day);
	//std::cout << "Количество дней с начала эры: " << total_days << std::endl;

	//CDate date(31, Month::DECEMBER, 1970);
}