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
};

