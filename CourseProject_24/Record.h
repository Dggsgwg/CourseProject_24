#include <string>
#include <iostream>
#include "Date.h"

using namespace std;

struct Record
{
	const char* groupCode = new char[6]; //шифр группы
	int personalId; //номер зачетной книжки
	string name; //ФИО студента
	bool isMale; //пол true = мужской, false = женский
	string educationForm; //форма обучения
	Date birthdayDate; //дата рождения
	Date entranceDate; //дата поступления
	int EGEPoints; //баллы ЕГЭ

	Record();
	Record(const char* _groupCode, int _personalId, string _name, bool _isMale, 
		string _educationForm, Date _birthdayDate, Date _entranceDate, int _EGEPoints);

	bool operator > (const Record& record);

	string toString();
	string toFileString();
};

