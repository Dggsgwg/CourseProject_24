#pragma warning(disable : 4996)
#include "Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <format>
#include <conio.h>


Menu::Menu()
{
	s = Spreadsheet();
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
	case 4:
		cout << "������� ������ ������ � �������:" << endl
			<< "����� ������, ����� ���., � � �, ���(true = �), ���� ����, ��.��.��(��������), ��.��.��(�����������), ���" << endl
			<< "������: ��22-6 123456 ��������� � � true ����� 1 1 2008 1 1 2021 250" << endl;
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
			saveToFile(false);
			break;
		case 0:
			while (command != -1) {
				cout << "��������� ������� � ����? (y/n)" << endl;
				char ch = _getch();
				switch (ch)
				{
				case 'y':
					saveToFile(true);
					command = -1;
					break;
				case 'n':
					command = -1;
					break;
				default:
					break;
				}
			}
		}
	} while (command != -1);
}

void Menu::loadFromFile()
{
	string fileName;

	cout << "������� ��� ����� ��� ��������" << endl;
	cin >> fileName;

	s.readFromFile(fileName);
	operateWithTable();
}

void Menu::saveToFile(bool leave)
{
	string fileName;
	int command;

	cout << "������� ��� ����� ��� ����������" << endl;
	cin >> fileName;

	s.saveToFile(fileName);

	if (!leave) {
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
	}
	exit(0);
}

void Menu::operateWithTable()
{
	int command, numLine;
	string line;
	Node* n = NULL;
	bool pause = false;

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
			printMenu(4);

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
			printMenu(4);
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
					<< s.nodeToString(n) << endl;
			}
			else
			{
				cout << "������ �� �������" << endl;
			}
			pause = true;
			break;
		case 7:
			s.getFiveEldest();
			pause = true;
			break;
		}
		if (pause)
		{
			if (command != 0)
			{
				system("pause");
			}
			pause = false;
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