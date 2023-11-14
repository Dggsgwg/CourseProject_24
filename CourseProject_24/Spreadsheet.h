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
	Record getRecordFromStream(istream& in);
	bool removeRecord(int personalId);
	bool editRecord(int personalId, Record record);
	void sort();
	Node* seek(int personalId);
	void getFiveEldest();
	void saveToFile(string fileName);
	void readFromFile(string fileName);

private:
	void getFiveEldest(Node** array, bool isMale);
	void printHeader();
	void printBottom();
	bool displayPage(Node* showList, int rows, int page);

	int compareDate(Date date, Date date2);
	string dateToString(Date date);
	string dateToFileString(Date date);

	string recordToString(Record record);
	string recordToFileString(Record record);
	
	string nodeToString(Node* node);
	string nodeToFileString(Node* node);
};

