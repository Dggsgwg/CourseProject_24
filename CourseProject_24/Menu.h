#include "Spreadsheet.h"

class Menu
{
	Spreadsheet s;

public:
	Menu();
	void start();
	void loadFromFile();
	void saveToFile(bool leave);
	void operateWithTable();
	int getCommand(int count);
};

