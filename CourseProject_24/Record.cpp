#include <iostream>
#include <format>
#include "Record.h"

using namespace std;

//Record::Record() 
//{
//	groupCode = "";
//	personalId = 0;
//	name = "";
//	isMale = false;
//	educationForm = "";
//	birthdayDate = Date();
//	entranceDate = Date();
//	EGEPoints = 0;
//}
//
//Record::Record(string _groupCode, int _personalId, string _name, bool _isMale,
//	string _educationForm, Date _birthdayDate, Date _entranceDate, int _EGEPoints) 
//{
//	if (strlen(_groupCode.c_str()) != 6)
//	{
//		cout << "Ўифр группы должен быть 6 символов!" << endl;
//		return;
//	}
//	groupCode = _groupCode;
//	personalId = _personalId;
//	name = _name;
//	isMale = _isMale;
//	educationForm = _educationForm;
//	birthdayDate = _birthdayDate;
//	entranceDate = _entranceDate;
//	EGEPoints = _EGEPoints;
//}
//
//bool Record::operator>(const Record& record) 
//{
//	return strcmp(groupCode.c_str(), record.groupCode.c_str()) > 0;
//}
//
//string Record::toString() 
//{
//	return format("|   {:<9} | {:<10} | {:<19} | {:<7} |   {:<9} | {:<10} |    {:<13} |    {:<6} |", 
//		groupCode, personalId, name, isMale ? "мужской" : "женский",
//		educationForm, birthdayDate.toString(),
//		entranceDate.toString(), EGEPoints);
//}
//
//string Record::toFileString()
//{
//	return format("{} {} {} {} {} {} {} {}",
//		groupCode, personalId, name, isMale,
//		educationForm, birthdayDate.toFileString(),
//		entranceDate.toFileString(), EGEPoints);
//}