#include "Record.h"
#include <format>

using namespace std;

Record::Record() 
{
	groupCode = {};
	personalId = 0;
	name = "";
	isMale = false;
	educationForm = "";
	birthdayDate = Date();
	entranceDate = Date();
	EGEPoints = 0;
}

Record::Record(const char* _groupCode, int _personalId, string _name, bool _isMale,
	string _educationForm, Date _birthdayDate, Date _entranceDate, int _EGEPoints) 
{
	groupCode = _groupCode;
	personalId = _personalId;
	name = _name;
	isMale = _isMale;
	educationForm = _educationForm;
	birthdayDate = _birthdayDate;
	entranceDate = _entranceDate;
	EGEPoints = _EGEPoints;
}

string Record::toString() 
{
	return format("{}, {}, {}, {}, {}, {}, {}, {}", 
		groupCode, personalId, name, isMale ? "true" : "false",
		educationForm, birthdayDate.toString(),
		entranceDate.toString(), EGEPoints);
}