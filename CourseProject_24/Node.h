#include "Record.h"

struct Node
{
public:
	Record record;
	Node* next;

	Node(Record _record, Node* _next);
	string toString();
};

