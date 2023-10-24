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
	void removeRecord();
	void editRecord();
	void sort();
	void seek(string param);
	void saveToFile(string filename);
	void readFromFile(string filename);
};

