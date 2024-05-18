#pragma once
#include <set>
#include <map>
#include <tuple>
#include <iostream>

enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

// ���� � ������� ����-�����-���. ��� � ��������� �� 1970 �� 9999
class CDate
{
public:
    CDate(unsigned day, Month month, unsigned int year);
    explicit CDate(unsigned int timestamp);
    CDate();

    unsigned GetDay() const;
    Month GetMonth() const;
    unsigned GetYear() const;
    WeekDay GetWeekDay() const;

    CDate& operator=(const CDate& other);

    CDate operator+(unsigned int offset) const;
    CDate operator-(unsigned int offset) const;
    int operator-(const CDate& other) const;
    CDate& operator+=(unsigned int offset);
    CDate& operator-=(unsigned int offset);
    bool operator==(const CDate& other) const;
    bool operator!=(const CDate& other) const;
    bool operator <(const CDate& other) const;
    bool operator >(const CDate& other) const;
    bool operator <=(const CDate& other) const;
    bool operator >=(const CDate& other) const;
    CDate& operator++();      
    CDate operator++(int);    
    CDate& operator--();
    CDate operator--(int);

    friend std::ostream& operator<<(std::ostream& os, const CDate& date);
    friend std::istream& operator>>(std::istream& is, CDate& date);

    bool IsValid() const;

private:
    const unsigned int BEGIN_YEAR = 1970;
    const unsigned int FIRST_LEAP_YEAR = 1972;
    const unsigned int END_YEAR = 9999;
    const unsigned int YEAR_DAYS = 365;
    const unsigned int WEEK_DAYS = 7;
    const unsigned int MONTHS = 12;
    const unsigned int LEAP_DAYS_TO_BEGIN_YEAR = 477;
    const unsigned int TOTAL_DAYS_TO_BEGIN_YEAR = (BEGIN_YEAR - 1) * YEAR_DAYS + LEAP_DAYS_TO_BEGIN_YEAR;
    const unsigned int TOTAL_DAYS_TO_END_YEAR = END_YEAR * YEAR_DAYS + 2424;
    const unsigned int DAYS = TOTAL_DAYS_TO_END_YEAR - TOTAL_DAYS_TO_BEGIN_YEAR - 1;

    bool IsLeapYear(unsigned int year) const;

    std::map<Month, unsigned int> daysInMonths = {
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

    unsigned int CountDaysInYears(unsigned int year);
    unsigned int CountDays(unsigned int day, Month month, unsigned int year);
    std::tuple<unsigned int, unsigned int> GetMonthAndDays() const;

    unsigned m_timestamp = 0;
};