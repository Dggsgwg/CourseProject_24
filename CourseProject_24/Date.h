#include <string>

using namespace std;

struct Date
{
	int year;
	int month;
	int day;

	Date();
	Date(int _year, int _month, int _day);

	string toString();
};

