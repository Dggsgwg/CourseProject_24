#include "Date.h"
#include <format>

Date::Date() 
{
	year = 0;
	month = 0;
	day = 0;
}

Date::Date(int _year, int _month, int _day)
{
	year = _year;
	month = _month;
	day = _day;
}

string Date::toString() 
{
	return format("{}.{}.{}", day, month, year);
}
