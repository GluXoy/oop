#include "CDate.h"
#include <iostream>
#include <set>
#include <tuple>
#include <iomanip>
#include <sstream>
#include <string>

const std::map<Month, unsigned int> CDate::daysInMonths = {
	{Month::JANUARY, 31},
	{Month::FEBRUARY, 28},
	{Month::MARCH, 31},
	{Month::APRIL, 30},
	{Month::MAY, 31},
	{Month::JUNE, 30},
	{Month::JULY, 31},
	{Month::AUGUST, 31},
	{Month::SEPTEMBER, 30},
	{Month::OCTOBER, 31},
	{Month::NOVEMBER, 30},
	{Month::DECEMBER, 31},
};

CDate operator+(unsigned int offset, const CDate& date)
{
	return CDate(date.m_timestamp + offset);
}

CDate& CDate::operator =(const CDate& other)
{
	if (this != &other)
	{
		m_timestamp = other.m_timestamp;
	}
	return *this;
}

CDate CDate::operator +(unsigned int offset) const
{
	CDate res(m_timestamp + offset);
	return res;
}

CDate CDate::operator -(unsigned int offset) const
{
	CDate res(m_timestamp - offset);
	return res;
}

int CDate::operator -(const CDate& other) const
{
	return m_timestamp - other.m_timestamp;
}

CDate& CDate::operator +=(unsigned int offset)
{
	m_timestamp += offset;
	return *this;
}

CDate& CDate::operator -=(unsigned int offset)
{
	m_timestamp -= offset;
	return *this;
}

bool CDate::operator ==(const CDate& other) const
{
	return m_timestamp == other.m_timestamp;
}

bool CDate::operator !=(const CDate& other) const
{
	return m_timestamp != other.m_timestamp;
}

bool CDate::operator <(const CDate& other) const
{
	return m_timestamp < other.m_timestamp;
}

bool CDate::operator>(const CDate& other) const
{
	return m_timestamp > other.m_timestamp;
}

bool CDate::operator<=(const CDate& other) const
{
	return m_timestamp <= other.m_timestamp;
}

bool CDate::operator>=(const CDate& other) const
{
	return m_timestamp >= other.m_timestamp;
}

CDate& CDate::operator++()
{
	++m_timestamp;
	return *this;
}

CDate CDate::operator++(int)
{
	CDate temp = *this;
	++m_timestamp;
	return temp;
}

CDate& CDate::operator--()
{
	--m_timestamp;
	return *this;
}

CDate CDate::operator--(int)
{
	CDate temp = *this;
	--m_timestamp;
	return temp;
}

std::ostream& operator <<(std::ostream& os, const CDate& date)
{
	if (!date.IsValid())
	{
		os << "INVALID";
	}
	else
	{
		os << std::setw(2) << std::setfill('0') << date.GetDay() << '/'
			<< std::setw(2) << std::setfill('0') << static_cast<unsigned int>(date.GetMonth()) << '/'
			<< date.GetYear();
	}
	return os;
}

std::istream& operator >>(std::istream& is, CDate& date)
{
	std::string input;
	is >> input;
	std::istringstream iss(input);
	unsigned int day, month, year;
	char slash1, slash2;

	if (iss >> day >> slash1 >> month >> slash2 >> year && slash1 == '/' && slash2 == '/')
	{
		date = CDate(day, static_cast<Month>(month), year);
	}
	else
	{
		date = CDate(static_cast<unsigned int>(-1));
	}

	return is;
}

bool CDate::IsLeapYear(unsigned int year)
{
	return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}


unsigned int CDate::CountDaysInYears(unsigned int year)
{
	unsigned int leapDays = (year / 4) - (year / 100) + (year / 400);
	return year * YEAR_DAYS + leapDays - TOTAL_DAYS_TO_BEGIN_YEAR;
}

unsigned int CDate::CountDays(unsigned int day, Month month, unsigned int year)
{
	unsigned int pastDaysInCurrentYear = 0;

	for (const auto& m : daysInMonths)
	{
		if (month == m.first)
		{
			pastDaysInCurrentYear += day;
			break;
		}

		if (IsLeapYear(year) && m.first == Month::FEBRUARY)
		{
			pastDaysInCurrentYear++;
		}
		pastDaysInCurrentYear += m.second;
	}

	pastDaysInCurrentYear--;

	unsigned int pastDaysInOtherYears = 0;

	if (year != BEGIN_YEAR)
	{
		pastDaysInOtherYears = CountDaysInYears(year - 1);
	}

	return pastDaysInCurrentYear + pastDaysInOtherYears;
}


CDate::CDate(unsigned int day, Month month, unsigned int year)
{
	if (day > 31 || day < 1)
	{
		throw std::invalid_argument("invalid day!");
	}

	if (year < BEGIN_YEAR || year > END_YEAR)
	{
		throw std::invalid_argument("invalid year!");
	}

	if (!(IsLeapYear(year) && month == Month::FEBRUARY && day == 29))
	{
		if (!(day <= daysInMonths.at(month)))
		{
			throw std::invalid_argument("non-existing day in this month!");
		}
	}

	// ������� ���� ...
	m_timestamp = CountDays(day, month, year);
	//std::cout << m_timestamp + TOTAL_DAYS_TO_BEGIN_YEAR << std::endl;
}

CDate::CDate(unsigned int timestamp)
{
	if (!(timestamp <= DAYS && timestamp >= 0))
	{
		throw std::out_of_range("this day is out of date's range!");
	}
	m_timestamp = timestamp;
}


CDate::CDate() : m_timestamp(0)
{
}

std::tuple<unsigned int, unsigned int> CDate::GetMonthAndDays() const {
	unsigned int year = GetYear();
	unsigned int days = m_timestamp + TOTAL_DAYS_TO_BEGIN_YEAR;

	unsigned int fullYears = year - 1;
	days -= fullYears * YEAR_DAYS + fullYears / 4 - fullYears / 100 + fullYears / 400;

	bool isLeap = IsLeapYear(year);

	const unsigned int daysInMonth[2][12] = {
		{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
		{31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
	};

	unsigned int months = 0;
	while (days >= daysInMonth[isLeap][months])
	{
		days -= daysInMonth[isLeap][months];
		++months;
	}

	return std::make_tuple(months + 1, days + 1);
}

Month CDate::GetMonth() const {
	auto [month, day] = GetMonthAndDays();
	return static_cast<Month>(month);
}

unsigned CDate::GetDay() const {
	auto [month, day] = GetMonthAndDays();
	return day;
}

unsigned CDate::GetYear() const
{
	unsigned int days = m_timestamp + TOTAL_DAYS_TO_BEGIN_YEAR; // ���������� ���� � ������ ���
	const unsigned int days_in_4_years = 1461; // 4 * 365 + 1
	const unsigned int days_in_100_years = 36524; // 100 * 365 + 25 - 1
	const unsigned int days_in_400_years = 146097; // 400 * 365 + 100 - 3

	unsigned int n400 = days / days_in_400_years;
	days %= days_in_400_years;

	unsigned int n100 = days / days_in_100_years;
	days %= days_in_100_years;

	unsigned int n4 = days / days_in_4_years;
	days %= days_in_4_years;

	unsigned int n1 = days / YEAR_DAYS;
	if (n1 == 4)
	{
		n1 = 3;
	}
	days %= YEAR_DAYS;

	unsigned int years = 400 * n400 + 100 * n100 + 4 * n4 + n1;
	if (n100 == 4)
	{
		years--;
	}

	return years + 1;
}

WeekDay CDate::GetWeekDay() const
{
	unsigned int totalDays = m_timestamp + TOTAL_DAYS_TO_BEGIN_YEAR;

	// ��������� ��� ����������� ����������� ��� ������
	unsigned int weekDay = (totalDays + 1) % WEEK_DAYS; // ��������� 1 ��� ���������

	return static_cast<WeekDay>(weekDay);
}

bool CDate::IsValid() const
{
	return m_timestamp <= DAYS && m_timestamp >= 0;
}