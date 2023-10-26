#include <iostream>
#include <format>
#include "Record.h"

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
	if (strlen(_groupCode) != 6)
	{
		cout << "Ўифр группы должен быть 6 символов!" << endl;
		return;
	}
	groupCode = _groupCode;
	personalId = _personalId;
	name = _name;
	isMale = _isMale;
	educationForm = _educationForm;
	birthdayDate = _birthdayDate;
	entranceDate = _entranceDate;
	EGEPoints = _EGEPoints;
}

bool Record::operator>(const Record& record) 
{
	return strcmp(groupCode, record.groupCode) >= 0;
}

string Record::toString() 
{
	return format("{}, {}, {}, {}, {}, {}, {}, {}", 
		groupCode, personalId, name, isMale ? "true" : "false",
		educationForm, birthdayDate.toString(),
		entranceDate.toString(), EGEPoints);
}

string Record::toFileString()
{
	return format("{} {} {} {} {} {} {} {}",
		groupCode, personalId, name, isMale ? "true" : "false",
		educationForm, birthdayDate.toString(),
		entranceDate.toString(), EGEPoints);
}