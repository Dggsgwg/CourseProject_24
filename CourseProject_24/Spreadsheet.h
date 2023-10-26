#include "Node.h"

class Spreadsheet
{
	string tableName;
	Node* list;
	
public:
	Spreadsheet();
	Spreadsheet(string _tableName);
	Spreadsheet(string _tableName, Node* _list);

	void display();
	void addRecord(Record record);
	bool removeRecord(string groupCode);
	bool editRecord(string groupCode, Record record);
	void sort();
	Node* seek(int personalId);
	void getFiveEldest();
	void saveToFile(string fileName);
	void readFromFile(string fileName);

private:
	void getFiveEldest(Node** array, bool isMale);
};

