#pragma once
#include "linkedlist.h"

void parser(char*& line, Node*& n, Linkedlist& list);
void parse_if_Is_Oper(int& count, char*& line, Node*& n, Linkedlist& list);
void parse_if_is_NUM(int& count, char*& line, Node*& n, Linkedlist& list);
char* parse_if_Is_MULTI(int& count, char*& line, Node*& n, Linkedlist& list);
int ifIsX(int&, char*, Node*);
void ifTrig(int&, char*, Node*);