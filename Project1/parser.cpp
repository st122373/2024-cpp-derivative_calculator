#include "parser.h"

void parser(char*& line, Node*& n, Linkedlist& list)
{
	int count = 0;

	while (line[count] != '\0')
	{
		// if between terms in function
		if (line[count] == '+' || line[count] == '-') {
			parse_if_Is_Oper(count, line, n, list);
			continue;
		}
		//if found multiplication
		if (line[count] == '*')
		{
			parse_if_Is_MULTI(count, line, n, list);
			continue;
		}
		// if char is space
		if (line[count] == ' ') {
			count++;
			continue;
		}
		// if found sine, cos, or tan in function
		if (line[count] == 'c') {
			n->setTrig(2);
			count += 3;
			ifTrig(count, line, n);
			continue;
		}
		else if (line[count] == 's') {
			n->setTrig(1);
			count += 3;
			ifTrig(count, line, n);
			continue;
		}
		else if (line[count] == 't') {
			n->setTrig(3);
			count += 3;
			ifTrig(count, line, n);
			continue;
		}
		// if char is a number 0-9
		if (line[count] >= 48 && line[count] <= 57)
		{
			parse_if_is_NUM(count, line, n, list);
			continue;
		}
		// if char is X
		ifIsX(count, line, n);
		continue;
		count++;
	}
}

void parse_if_is_NUM(int& count, char*& line, Node*& n, Linkedlist& list)
{
	if (line[count] >= '0' && line[count] <= '9')
	{
		// Parse the entire number
		int num = 0;
		while (line[count] >= '0' && line[count] <= '9')
		{
			num = num * 10 + (line[count] - '0');
			count++;
		}
		n->setOuter(num);
	}
	else {
		n->setOuter(std::atoi(&line[count]));
		count++;
	}
}

char* parse_if_Is_MULTI(int& count, char*& line, Node*& n, Linkedlist& list)
{
	Linkedlist temp;
	char* tmp = new char[100];

	count += temp.getSize();
	return tmp;
}

void parse_if_Is_Oper(int& count, char*& line, Node*& n, Linkedlist& list)
{
	//create array
	list.addNode(n);
	n = new Node();

	if (line[count] == '-')
		n->setOuter(-1);
	count++;
}

int ifIsX(int& count, char* line, Node* n)
{
	if (line[count] == 'x')
	{
		if (line[count + 1] == '^')
		{
			count++;
			if (line[count + 1] == '-')
			{
				n->setExponent(-1);
				count++;
			}
			else if (line[count + 1] == '1' && line[count + 2] == '0')
			{
				n->setExponent(10);
				count += 2;
			}
			else
			{
				n->setExponent(std::atoi(&line[count + 1]));

				while (line[count + 1] >= '0' && line[count + 1] <= '9')
				{
					count++;
				}
			}
		}
		else
		{
			n->setExponent(1);
		}
		count++;
		return 0;
	}
	else
	{
		return 1;
	}
}

void ifTrig(int& count, char* line, Node* n)
{
	while (line[count] == ' ')
		count++;
	if (line[count] == '-')
	{
		n->setInner(-1);
		count++;
	}

	if (line[count] == '1' && line[count + 1] == '0')
	{
		n->setInner(10);
		count += 2;
	}

	else if (line[count] >= 48 && line[count] <= 57)
	{
		n->setInner(std::atoi(&line[count]));
		count++;
	}

	else
		n->setInner(1);

	if (line[count] == 'x')
	{
		return;
	}
}