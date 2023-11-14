//#include "DateUseCase.h"
//#include <format>
//
//int DateUseCase::compareDate(Date date, Date date2) 
//{
//	if (date.year > date2.year) return  1;
//	else if (date.year < date2.year) return -1;
//	if (date.month > date2.month) return 1;
//	else if (date.month < date2.month) return -1;
//	if (date.day > date2.day) return 1;
//	else if (date.day < date2.day) return -1;
//	else return 0;
//}
//
//string DateUseCase::dateToString(Date date) 
//{
//	return format("{:02}.{:02}.{}", date.day, date.month, date.year);
//}
//
//string DateUseCase::dateToFileString(Date date) 
//{
//	return format("{} {} {}", date.day, date.month, date.year);
//}