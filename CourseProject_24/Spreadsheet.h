#include "Node.h"

class Spreadsheet
{
	string tableName;
	Node* list;
	
public:
	Spreadsheet(string _tableName);
	Spreadsheet(string _tableName, Node* _list);

	void display();
	void addRecord(Record record);
	bool removeRecord(const char* groupCode);
	bool editRecord(const char* groupCode, Record record);
	void sort();
	Node* seek(int personalId);
	void saveToFile(string fileName);
	void readFromFile(string fileName);
};

