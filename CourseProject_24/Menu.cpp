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
		cout << "Список команд:" << endl
			<< "1 - Создание новой таблицы" << endl
			<< "2 - Загрузка таблицы из файла" << endl
			<< "3 - Сохранение текущей таблицы в файл" << endl
			<< "0 - Выход из программы" << endl;
		break;
	case 2:
		cout << "Список команд:" << endl
			<< "1 - Продолжить работу с таблицей" << endl
			<< "0 - Выход из программы" << endl;
		break;
	case 3:
		cout << "Список команд:" << endl
			<< "1 - Просмотр таблицы" << endl
			<< "2 - Добавить запись" << endl
			<< "3 - Удалить запись" << endl
			<< "4 - Изменить запись" << endl
			<< "5 - Сортировать таблицу" << endl
			<< "6 - Найти запись" << endl
			<< "7 - Получить 5 старших юношей и девушек" << endl
			<< "0 - Вернуться в главное меню" << endl;
		break;
	case 4:
		cout << "Введите данные записи в формате:" << endl
			<< "Номер группы, номер зач., Ф И О, пол(true = М), форм обуч, ДД.ММ.ГГ(рождения), ДД.ММ.ГГ(поступления), ЕГЭ" << endl
			<< "Пример: ИТ22-6 123456 Балабанов В Е true очная 1 1 2008 1 1 2021 250" << endl;
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
			cout << "Введите название таблицы:" << endl;
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
				cout << "Сохранить таблицу в файл? (y/n)" << endl;
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

	cout << "Введите имя файла для открытия" << endl;
	cin >> fileName;

	s.readFromFile(fileName);
	operateWithTable();
}

void Menu::saveToFile(bool leave)
{
	string fileName;
	int command;

	cout << "Введите имя файла для сохранения" << endl;
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
			cout << "Введите номер зачетки для удаления записи:" << endl;
			cin >> numLine;
			s.removeRecord(numLine);
			s.display();
			break;
		case 4:
			cout << "Введите номер зачетки для изменения записи:" << endl;
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
			cout << "Введите номер зачетки для поиска записи:" << endl;
			cin >> numLine;
			n = s.seek(numLine);
			if (n != NULL)
			{
				cout << "Искомая запись:" << endl
					<< s.nodeToString(n) << endl;
			}
			else
			{
				cout << "Запись не найдена" << endl;
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
	string s; // строка для считывания введённых данных
	getline(cin, s); // считываем строку
	while (s.empty()) 
	{
		getline(cin, s);
	}

	// пока ввод некорректен, сообщаем об этом и просим повторить его
	while (sscanf(s.c_str(), "%d", &variant) != 1 || variant < 0 || variant > count) {
		cout << "Неправильный код: " << endl; // выводим сообщение об ошибке
		getline(cin, s); // считываем строку повторно
	}

	return variant;
}