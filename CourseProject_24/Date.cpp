#include "Date.h"
#include <format>

//Date::Date() 
//{
//	year = 0;
//	month = 0;
//	day = 0;
//}
//
//Date::Date(short _year, short _month, short _day)
//{
//	year = _year;
//	month = _month;
//	day = _day;
//}
//
//int Date::compare(Date date) 
//{
//	if (year > date.year) return  1;
//	else if (year < date.year) return -1;
//	if (month > date.month) return 1;
//	else if (month < date.month) return -1;
//	if (day > date.day) return 1;
//	else if (day < date.day) return -1;
//	else return 0;
//}
//
//string Date::toString() 
//{
//	return format("{:02}.{:02}.{}", day, month, year);
//}
//
//string Date::toFileString() 
//{
//	return format("{} {} {}", day, month, year);
//}
