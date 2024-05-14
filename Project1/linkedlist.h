#ifndef Linkedlist_H
#define Linkedlist_H

#include "Node.h"

class Linkedlist {
	Node* head;

public:
	friend std::ostream& operator << (std::ostream& os, Linkedlist& list);

	Linkedlist();

	Linkedlist(Linkedlist& list);

	~Linkedlist();

	void deleteList();

	void addNode(Node* n);

	Node* getHead();

	int getSize();

	void sort();

	void operator ++ ();

	Node* operator [] (int i);

};

#endif 
