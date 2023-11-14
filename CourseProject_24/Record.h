#include <string>
#include <iostream>
#include "Date.h"

using namespace std;

struct Record
{
	string groupCode; //шифр группы
	int personalId; //номер зачетной книжки
	string name; //ФИО студента
	bool isMale; //пол true = мужской, false = женский
	string educationForm; //форма обучения
	Date birthdayDate; //дата рождения
	Date entranceDate; //дата поступления
	int EGEPoints; //баллы ЕГЭ
};

