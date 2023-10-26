#include <string>
#include <iostream>
#include "Date.h"

using namespace std;

struct Record
{
	string groupCode; //���� ������
	int personalId; //����� �������� ������
	string name; //��� ��������
	bool isMale; //��� true = �������, false = �������
	string educationForm; //����� ��������
	Date birthdayDate; //���� ��������
	Date entranceDate; //���� �����������
	int EGEPoints; //����� ���

	Record();
	Record(string _groupCode, int _personalId, string _name, bool _isMale, 
		string _educationForm, Date _birthdayDate, Date _entranceDate, int _EGEPoints);

	bool operator > (const Record& record);

	string toString();
	string toFileString();
};

