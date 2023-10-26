#include <string>
#include <iostream>
#include "Date.h"

using namespace std;

struct Record
{
	const char* groupCode = new char[6]; //���� ������
	int personalId; //����� �������� ������
	string name; //��� ��������
	bool isMale; //��� true = �������, false = �������
	string educationForm; //����� ��������
	Date birthdayDate; //���� ��������
	Date entranceDate; //���� �����������
	int EGEPoints; //����� ���

	Record();
	Record(const char* _groupCode, int _personalId, string _name, bool _isMale, 
		string _educationForm, Date _birthdayDate, Date _entranceDate, int _EGEPoints);

	bool operator > (const Record& record);

	string toString();
	string toFileString();
};

