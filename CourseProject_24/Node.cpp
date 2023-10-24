#include "Node.h"

Node::Node(Record _record, Node* _next) 
{
	record = _record;
	next = _next;
}

string Node::toString() 
{
	return record.toString();
}