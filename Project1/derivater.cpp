#include "derivater.h"

void derive(char* page, Linkedlist& list)
{
	std::ofstream file;
	file.open(page, std::ios::app);

	int x = 0;
	while (list[x] != nullptr)
	{
		if (list[x]->getTrig())
		{
			if (list[x]->getTrig() == TAN)
			{
				derive_tan(page, list, x, file);
			}
			else if (list[x]->getTrig() == SIN)
			{
				derive_sin(page, list, x, file);
			}
			else if (list[x]->getTrig() == COS)
			{
				derive_cos(page, list, x, file);
			}
		}
		else if (list[x]->getExponent() == 0)
		{
			file << "+ " << 0 << " ";
		}
		else if (list[x]->getExponent() == 1)
		{
			file << "+ " << list[x]->getOuter() << " ";
		}
		else
		{
			file << list[x]->getOuter() * list[x]->getExponent() << "x^" << list[x]->getExponent() - 1 << " ";
		}

		x++;
	}
	file << std::endl;
	file.close();
}

void derive_tan(char* page, Linkedlist& list, int& x, std::ofstream& file)
{
	if (x == 0)
	{
		if (list[x]->getOuter() * list[x]->getInner() < 0)
		{
			file << list[x]->getOuter() * list[x]->getInner() << "sec^2 " << list[x]->getInner() << "x ";
		}
		else
		{
			file << list[x]->getOuter() * list[x]->getInner() << "sec^2 " << list[x]->getInner() << "x ";
		}
	}
	else
	{
		if (list[x]->getOuter() * list[x]->getInner() < 0)
		{
			file << "+ " << list[x]->getOuter() * list[x]->getInner() << "sec^2 " << list[x]->getInner() << "x ";
		}
		else
		{
			file << "- " << list[x]->getOuter() * list[x]->getInner() << "sec^2 " << list[x]->getInner() << "x ";
		}
	}
}

void derive_sin(char* page, Linkedlist& list, int& x, std::ofstream& file)
{
	if (x == 0)
	{
		if (list[x]->getOuter() == 1)
			file << list[x]->getInner() << "cos " << list[x]->getInner() << "x ";
		else
			file << list[x]->getOuter() * list[x]->getInner() << "cos " << list[x]->getInner() << "x ";
	}
	else
	{
		if (list[x]->getOuter() * list[x]->getInner() > 0)
		{
			file << "+ " << list[x]->getOuter() * list[x]->getInner() << "cos " << list[x]->getInner() << "x ";
		}
		else
		{
			file << "- " << list[x]->getOuter() * list[x]->getInner() * -1 << "cos " << list[x]->getInner() << "x ";
		}
	}
}

void derive_cos(char* page, Linkedlist& list, int& x, std::ofstream& file)
{
	if (x == 0)
	{
		if (list[x]->getOuter() == 1)
			file << list[x]->getInner() << "sin " << list[x]->getInner() << "x ";
		else
			file << list[x]->getOuter() * list[x]->getInner() << "sin " << list[x]->getInner() << "x ";
	}
	else
	{
		if (list[x]->getOuter() * list[x]->getInner() < 0)
		{
			file << "+ " << list[x]->getOuter() * list[x]->getInner() << "sin " << list[x]->getInner() << "x ";
		}
		else
		{
			file << "- " << list[x]->getOuter() * list[x]->getInner() << "sin " << list[x]->getInner() << "x ";
		}
	}
}