#pragma once
#include <set>
#include <map>
#include <tuple>


// Месяц
enum class Month
{
    JANUARY = 1, FEBRUARY, MARCH, APRIL,
    MAY, JUNE, JULY, AUGUST, SEPTEMBER,
    OCTOBER, NOVEMBER, DECEMBER
};

// День недели
enum class WeekDay
{
    SUNDAY = 0, MONDAY, TUESDAY, WEDNESDAY,
    THURSDAY, FRIDAY, SATURDAY
};

// Дата в формате день-месяц-год. Год в диапазоне от 1970 до 9999
class CDate
{
public:
    // инициализируем дату заданными днем, месяцем и годом.
    // примечание: год >= 1970
    CDate(unsigned day, Month month, unsigned int year);

    // инициализируем дату количеством дней, прошедших после 1 января 1970 года
    // например, 2 = 3 января 1970, 32 = 2 февраля 1970 года и т.д.
    explicit CDate(unsigned int timestamp);

    // Конструктор по умолчанию. Создаёт дату, равную 1 января 1970.
    CDate();

    // возвращает день месяца (от 1 до 31)
    unsigned GetDay() const;

    // возвращает месяц
    Month GetMonth() const;

    // возвращает год
    unsigned GetYear() const;

    // возвращает день недели
    WeekDay GetWeekDay() const;

    // возвращает информацию о корректности хранимой даты.
    // Например, после вызова CDate date(99, static_cast<Month>(99), 10983);
    // или после:
    // CDate date(1, January, 1970); --date;
    // метод date.IsValid() должен вернуть false;
    bool IsValid() const; // См. примечание

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