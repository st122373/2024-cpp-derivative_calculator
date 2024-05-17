#include <cstdlib>
#include "linkedlist.h"
#include "parser.h"
#include "derivater.h"

 // function prototypes
std::ostream& operator << (std::ostream& os, Linkedlist& list);
std::ostream& operator << (std::ostream& os, Node*);


int main(int argc,char* argv[])
{
	char functions[] = "functions.txt";
	char derivatives[] = "derive.txt";
	std::ifstream file;
	Linkedlist list;

	file.open(functions);

	// if file unable to open
	if (!file.is_open())
	{
		std::cout << "error" << std::endl;
		return 1;
	} 
	// while not at end of file, loop
	while (!file.eof())
	{
		// clear list
		list.~Linkedlist();
		char* line = new char[100];
		// get next line in file
		file.getline(line, 100, '\n');
		std::cout << "Enter you function" << std::endl;
		std::cout << line << std::endl;
		Node* n = new Node();
		parser(line, n, list);

		// delete array
		delete[] line;
		// add last node to list
		list.addNode(n);
		// sort list
		list.sort();
		// output derivative to file
		derive(derivatives, list);
		// print list
		std::cout << "You entered" << std::endl;
		std::cout << list << std::endl;
		// clear list
		list.~Linkedlist();
	}
	// close file
	file.close();

	return 0;
}

std::ostream& operator << (std::ostream& os, Node* n)
{
	if (n == nullptr)
	{
		os << "0x0" << std::endl;
		return os;
	} 

	if (n->trig)
	{
		//os << "trig" << std::endl;
		if (n->outer != 1 && n->outer != -1)
			os << n->outer;
		if (n->trig == 1)
			os << "sin ";
		if (n->trig == 2)
			os << "cos ";
		if (n->trig == 3)
			os << "tan ";

		if (n->inner == 1)
			os << "x";
		else if (n->inner == -1)
			os << "-x";
		else
			os << n->inner << "x";
	}
	else
	{
		if (n->outer != 1 && n->outer != -1)
		{
			if (n->outer < 0)
				os << n->outer * -1;
			else
				os << n->outer;
		} 

		if (n->exponent != 0)
		{
			if (n->exponent == 1)
			{
				 
				os << "x";
			}
			else
			{
				os << "x^" << n->exponent;
			}
		} 

		else
		{
			if (n->outer == 1)
				os << 1;
			else if (n->outer == -1)
				os << -1;
		}
	}
	return os;
}

std::ostream& operator << (std::ostream& os, Linkedlist& list)
{
	int x = 0;
	while (list[x] != nullptr)
	{
		if (x != 0)
			os << " ";
		if (list[x]->getOuter() < 0)
			os << "- ";
		if (list[x]->getOuter() > 0 && x != 0)
			os << "+ ";
		os << list[x];
		x++;
	}
	return os;
}

