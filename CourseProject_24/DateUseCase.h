#include "Date.h"
#include <string>

class DateUseCase
{
public:
	int compareDate(Date date, Date date2);
	string dateToString(Date date);
	string dateToFileString(Date date);
};