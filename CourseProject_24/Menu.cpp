#pragma warning(disable : 4996)
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

void printMenu(int num) 
{
	switch (num) 
	{
	case 1:
		cout << "������ ������:" << endl
			<< "1 - �������� ����� �������" << endl
			<< "2 - �������� ������� �� �����" << endl
			<< "3 - ���������� ������� ������� � ����" << endl
			<< "0 - ����� �� ���������" << endl;
		break;
	case 2:
		cout << "������ ������:" << endl
			<< "1 - ���������� ������ � ��������" << endl
			<< "0 - ����� �� ���������" << endl;
		break;
	case 3:
		cout << "������ ������:" << endl
			<< "1 - �������� �������" << endl
			<< "2 - �������� ������" << endl
			<< "3 - ������� ������" << endl
			<< "4 - �������� ������" << endl
			<< "5 - ����������� �������" << endl
			<< "6 - ����� ������" << endl
			<< "7 - �������� 5 ������� ������ � �������" << endl
			<< "0 - ��������� � ������� ����" << endl;
		break;
	}
}

void Menu::start()
{
	int command;
	string tableName;

	do
	{
		system("cls");

		printMenu(1);

		command = getCommand(3);

		switch (command)
		{
		case 1:
			cout << "������� �������� �������:" << endl;
			cin >> tableName;

			s = Spreadsheet(tableName);
			operateWithTable();
			break;
		case 2:
			loadFromFile();
			break;
		case 3:
			saveToFile();
			break;
		}
	} while (command != 0);
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
	string fileName;
	int command;

	cout << "������� ��� ����� ��� ����������" << endl;
	cin >> fileName;

	s.saveToFile(fileName);

	do
	{
		system("cls");
		printMenu(2);

		command = getCommand(1);

		switch (command)
		{
		case 1:
			operateWithTable();
			break;
		}
	} while (command != 0);
	exit(0);
}

void Menu::operateWithTable()
{
	int command, numLine;
	string line;
	Node* n = NULL;

	do
	{
		system("cls");

		printMenu(3);

		command = getCommand(7);

		switch (command)
		{
		case 1:
			s.display();
			break;
		case 2:
			cout << "������� ������ ������ � �������:" << endl
				<< "��22-6 123456 ��������� � � true ����� 1 1 2008 1 1 2021 250" << endl;

			s.addRecord(s.getRecordFromStream(cin));
			s.display();
			break;
		case 3:
			cout << "������� ����� ������� ��� �������� ������:" << endl;
			cin >> numLine;
			s.removeRecord(numLine);
			s.display();
			break;
		case 4:
			cout << "������� ����� ������� ��� ��������� ������:" << endl;
			cin >> numLine;
			cout << "������� ����� ������ ������ � �������:" << endl
				<< "��22-6 123456 ��������� � � true ����� 1 1 2008 1 1 2021 250" << endl;
			s.editRecord(numLine, s.getRecordFromStream(cin));
			s.display();
			break;	
		case 5:
			s.sort();
			s.display();
			break;
		case 6:
			cout << "������� ����� ������� ��� ������ ������:" << endl;
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
			break;
		case 7:
			s.getFiveEldest();
			break;
		}
		if (command != 0)
		{
			system("pause");
		}
	} while (command != 0);

	delete n;
	n = nullptr;
}

int Menu::getCommand(int count)
{
	int variant;
	string s; // ������ ��� ���������� �������� ������
	getline(cin, s); // ��������� ������
	while (s.empty()) 
	{
		getline(cin, s);
	}

	// ���� ���� �����������, �������� �� ���� � ������ ��������� ���
	while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 0 || variant > count) {
		cout << "������������ ���: " << endl; // ������� ��������� �� ������
		getline(cin, s); // ��������� ������ ��������
	}

	return variant;
}