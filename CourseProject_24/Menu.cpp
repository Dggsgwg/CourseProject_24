#include "Menu.h"
#include <stdlib.h>
#include <stdio.h>
#include <format>

Menu::Menu() 
{
	Record r = Record("ИТ22-2", 1, format("Ф И О1"), false, format("очная"), Date(2001, 1, 1), Date(2021, 1, 1), 250);
	Record r2 = Record("ИТ22-3", 2, format("Ф И О2"), true, format("очная"), Date(2002, 1, 1), Date(2021, 1, 1), 250);
	Record r3 = Record("ИТ22-4", 3, format("Ф И О3"), false, format("очная"), Date(2003, 1, 1), Date(2021, 1, 1), 250);
	Record r4 = Record("ИТ22-5", 4, format("Ф И О4"), true, format("очная"), Date(2004, 1, 1), Date(2021, 1, 1), 250);
	Record r5 = Record("ИТ22-6", 5, format("Ф И О5"), true, format("очная"), Date(2005, 1, 1), Date(2021, 1, 1), 250);
	Record r6 = Record("ИТ22-6", 6, format("Ф И О5"), true, format("очная"), Date(2006, 1, 1), Date(2021, 1, 1), 250);
	Record r7 = Record("ИТ22-6", 7, format("Ф И О5"), false, format("очная"), Date(2007, 1, 1), Date(2021, 1, 1), 250);
	Record r8 = Record("ИТ22-6", 8, format("Ф И О5"), true, format("очная"), Date(2008, 1, 1), Date(2021, 1, 1), 250);
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

	cout << "Список команд:" << endl
		<< "1 - Создание новой таблицы" << endl
		<< "2 - Загрузка таблицы из файла" << endl
		<< "3 - Сохранение текущей таблицы в файл" << endl
		<< "0 - Выход из программы" << endl;

	cin >> command;

	switch (command) 
	{
	case 1 :
		cout << "Введите название таблицы:" << endl;
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

	cout << "Введите имя файла для открытия" << endl;
	cin >> fileName;

	s.readFromFile(fileName);
	operateWithTable();
}

void Menu::saveToFile() 
{
	cin;

	string fileName;
	int command;
	
	cout << "Введите имя файла для сохранения" << endl;
	cin >> fileName;

	s.saveToFile(fileName);

	cout << "Список команд:" << endl
		<< "1 - Продолжить работу с таблицей" << endl
		<< "0 - Выход из программы" << endl;
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

	cout << "Список команд:" << endl
		<< "1 - Просмотр таблицы" << endl
		<< "2 - Добавить запись" << endl
		<< "3 - Удалить запись" << endl
		<< "4 - Изменить запись" << endl
		<< "5 - Сортировать таблицу" << endl
		<< "6 - Найти запись" << endl
		<< "7 - Получить 5 старших юношей и девушек" << endl
		<< "0 - Вернуться в главное меню" << endl;

	cin >> command;

	switch (command) 
	{
	case 1:
		s.display();
		operateWithTable();
		break;
	case 2:
		cout << "Введите данные записи в формате:" << endl
			<< "Шифр_группы_6_символов Фамилия Имя Отчество Параметр пол(true - мужской, false - женский)"
			<< "Форма_обучения(очная/заочная) день месяц год(рождения) день месяц год(поступления) балл_ЕГЭ" << endl;

		s.addRecord(s.getRecordFromStream(cin));
		s.display();
		operateWithTable();
		break;
	case 3:
		cout << "Введите номер зачетки для удаления записи:" << endl;
		cin >> numLine;
		s.removeRecord(numLine);
		s.display();
		operateWithTable();
		break;
	case 4:
		cout << "Введите номер зачетки для изменения записи:" << endl;
		cin >> numLine;
		cout << "Введите данные записи в формате:" << endl
			<< "Шифр_группы_6_символов Фамилия Имя Отчество Параметр пол(true - мужской, false - женский)"
			<< "Форма_обучения(очная/заочная) день месяц год(рождения) день месяц год(поступления) балл_ЕГЭ" << endl;
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
		cout << "Введите код зачетки для поиска записи:" << endl;
		cin >> numLine;
		n = s.seek(numLine);
		if (n != NULL) 
		{
			cout << "Искомая запись:" << endl 
				<< n->toString() << endl;
		}
		else 
		{
			cout << "Запись не найдена" << endl;
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