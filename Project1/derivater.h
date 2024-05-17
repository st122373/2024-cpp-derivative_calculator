#pragma once
#include "linkedlist.h"
#include <fstream>


void derive(char*, Linkedlist&);
void derive_tan(char* page, Linkedlist& list, int& x, std::ofstream& file);
void derive_sin(char* page, Linkedlist& list, int& x, std::ofstream& file);
void derive_cos(char* page, Linkedlist& list, int& x, std::ofstream& file);
