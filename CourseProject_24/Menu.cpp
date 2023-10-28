#include "Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <format>

Menu::Menu() 
{
	Record r = Record("��22-2", 1, format("� � �1"), false, format("�����"), Date(2001, 1, 1), Date(2021, 1, 1), 250);
	Record r2 = Record("��22-3", 2, format("� � �2"), true, format("�����"), Date(2002, 1, 1), Date(2021, 1, 1), 250);
	Record r3 = Record("��22-4", 3, format("� � �3"), false, format("�����"), Date(2003, 1, 1), Date(2021, 1, 1), 250);
	Record r4 = Record("��22-5", 4, format("� � �4"), true, format("�����"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
	Record r5 = Record("��22-6", 5, format("� � �5"), true, format("�����"), Date(2005, 1, 1), Date(2021, 1, 1), 250);
	Record r6 = Record("��22-6", 6, format("� � �5"), true, format("�����"), Date(2006, 1, 1), Date(2021, 1, 1), 250);
	Record r7 = Record("��22-6", 7, format("� � �5"), false, format("�����"), Date(2007, 1, 1), Date(2021, 1, 1), 250);
	Record r8 = Record("��22-6", 8, format("� � �5"), true, format("�����"), Date(2008, 1, 1), Date(2021, 1, 1), 250);
	s = Spreadsheet();
	/*s.addRecord(r);
	s.addRecord(r2);
	s.addRecord(r3);
	s.addRecord(r4);
	s.addRecord(r5);
	s.addRecord(r6);
	s.addRecord(r7);
	s.addRecord(r8);*/
}

void Menu::start() 
{
	int command;
	string tableName;

	cout << "������ ������:" << endl
		<< "1 - �������� ����� �������" << endl
		<< "2 - �������� ������� �� �����" << endl
		<< "3 - ���������� ������� ������� � ����" << endl
		<< "0 - ����� �� ���������" << endl;

	cin >> command;

	switch (command) 
	{
	case 1 :
		cout << "������� �������� �������:" << endl;
		cin >> tableName;

		s = Spreadsheet(tableName);
		operateWithTable();
		break;
	case 2:
		loadFromFile();
		operateWithTable();
		break;
	case 3:
		saveToFile();
		break;
	default: 
		cout << endl << endl;
		start();
		break;
	}
}

void Menu::loadFromFile() 
{
	string fileName;

	cout << "������� ��� ����� ��� ��������" << endl;
	cin >> fileName;

	s.readFromFile(fileName);
	operateWithTable();
}

void Menu::saveToFile() 
{
	cin;

	string fileName;
	int command;
	
	cout << "������� ��� ����� ��� ����������" << endl;
	cin >> fileName;

	s.saveToFile(fileName);

	cout << "������ ������:" << endl
		<< "1 - ���������� ������ � ��������" << endl
		<< "0 - ����� �� ���������" << endl;
	cin >> command;

	switch (command) 
	{
	case 1:
		operateWithTable();
		break;
	case 0:
		return;
	default:
		saveToFile();
		break;
	}
}

void Menu::operateWithTable() 
{
	cin;

	int command, numLine;
	string line;
	Node* n = NULL;

	cout << "������ ������:" << endl
		<< "1 - �������� �������" << endl
		<< "2 - �������� ������" << endl
		<< "3 - ������� ������" << endl
		<< "4 - �������� ������" << endl
		<< "5 - ����������� �������" << endl
		<< "6 - ����� ������" << endl
		<< "7 - �������� 5 ������� ������ � �������" << endl
		<< "0 - ��������� � ������� ����" << endl;

	cin >> command;

	switch (command) 
	{
	case 1:
		s.display();
		operateWithTable();
		break;
	case 2:
		cout << "������� ������ ������ � �������:" << endl
			<< "����_������_6_�������� ������� ��� �������� �������� ���(true - �������, false - �������)"
			<< "�����_��������(�����/�������) ���� ����� ���(��������) ���� ����� ���(�����������) ����_���" << endl;

		s.addRecord(s.getRecordFromStream(cin));
		s.display();
		operateWithTable();
		break;
	case 3:
		cout << "������� ����� ������� ��� �������� ������:" << endl;
		cin >> numLine;
		s.removeRecord(numLine);
		s.display();
		operateWithTable();
		break;
	case 4:
		cout << "������� ����� ������� ��� ��������� ������:" << endl;
		cin >> numLine;
		cout << "������� ������ ������ � �������:" << endl
			<< "����_������_6_�������� ������� ��� �������� �������� ���(true - �������, false - �������)"
			<< "�����_��������(�����/�������) ���� ����� ���(��������) ���� ����� ���(�����������) ����_���" << endl;
		s.editRecord(numLine, s.getRecordFromStream(cin));
		s.display();
		operateWithTable();
		break;
	case 5:
		s.sort();
		s.display();
		operateWithTable();
		break;
	case 6:
		cout << "������� ��� ������� ��� ������ ������:" << endl;
		cin >> numLine;
		n = s.seek(numLine);
		if (n != NULL) 
		{
			cout << "������� ������:" << endl 
				<< n->toString() << endl;
		}
		else 
		{
			cout << "������ �� �������" << endl;
		}
		operateWithTable();
		break;
	case 7:
		s.getFiveEldest();
		operateWithTable();
		break;
	case 0:
		start();
		break;
	default:
		operateWithTable();
		break;
	}

	delete n;
	n = nullptr;
}