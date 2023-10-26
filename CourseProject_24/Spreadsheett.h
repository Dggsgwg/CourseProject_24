#include <string>
#include "Node.h"

using namespace std;

class Spreadsheett
{
public:
	void saveToFile(string fileName, Node* list);
	Node* openFromFile(string filename);
};

