#include <cstdlib>
#include "Linkedlist.h"
#include <fstream>
 // function prototypes
void ifIsX(int&, char*, Node*);
void ifTrig(int&, char*, Node*);

std::ostream& operator << (std::ostream& os, Linkedlist& list);
std::ostream& operator << (std::ostream& os, Node*);
void derive(char*, Linkedlist&);


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

        int count = 0;
        Node* n = new Node();
        while (line[count] != '\0')
        {
            // if between terms in function
            if (line[count] == '+' || line[count] == '-') {
                //create array
                list.addNode(n);
                n = new Node();

                if (line[count] == '-')
                    n->setOuter(-1);
                count++;
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
                    continue;
                }

                else {
                    n->setOuter(std::atoi(&line[count]));
                    count++;
                    continue;
                } 

            } 

            // if char is X
            if (line[count] == 'x')
            {
                ifIsX(count, line, n);
                continue;
            } 

            count++;
        } 

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

void ifIsX(int& count, char* line, Node* n)
{

    if (line[count + 1] == '^')
    {
        count++;

        if (line[count + 1] == '-')
        {
            n->setExponent(-1);
            count++;
        } 

        if (line[count + 1] == '1' && line[count + 2] == '0')
        {
            n->setExponent(10);
            count += 2;
        } 

        else
        {
            n->setExponent(std::atoi(&line[count + 1]));
            count += 2;
        } 

    }
    else
    {
        n->setExponent(1);
        count++;
    } 

} // end of function

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

void derive(char* page, Linkedlist& list)
{
    std::ofstream file;
    file.open(page, std::ios::app);

    int x = 0;
    while (list[x] != nullptr)
    {
        if (x == 0)
        {
            if (list[x]->getTrig())
            {
                if (list[x]->getTrig() == TAN)
                {
                    if (list[x]->getOuter() * list[x]->getInner() < 0)
                    {
                        if (list[x]->getOuter() == 1)
                        {
                            if (list[x]->getInner() == -1)
                            {
                                file << "sec^2 -x ";
                            }
                            else
                                file << list[x]->getInner() << "sec^2 " << list[x]->getInner() << "x ";
                        }
                        else
                            if (list[x]->getInner() == 1)
                            {
                                if (list[x]->getOuter() == -1)
                                    file << "sec^2 x ";
                            }
                            else
                                file << list[x]->getOuter() * list[x]->getInner() << "sec^2 " << list[x]->getInner() << "x ";
                    }
                    else
                    {
                        if (list[x]->getOuter() == 1)
                        {
                            if (list[x]->getInner() == 1)
                            {
                                file << "-sec^2 x ";
                            }
                            else
                                file << list[x]->getInner() * -1 << "sec^2 " << list[x]->getInner() << "x ";
                        }
                        else
                            file << list[x]->getOuter() * list[x]->getInner() * -1 << "sec^2 " << list[x]->getInner() << "x ";
                    }
                }
                else if (list[x]->getTrig() == SIN)
                {
                    if (list[x]->getInner() == 1)
                    {
                        if (list[x]->getOuter() == 1)
                            file << "cos x ";
                        else
                            file << list[x]->getOuter() << "cos x ";
                    }
                    else
                    {
                        if (list[x]->getOuter() == 1)
                            file << list[x]->getInner() << "cos " << list[x]->getInner() << "x ";
                        else
                            file << list[x]->getOuter() * list[x]->getInner() << "cos " << list[x]->getInner() << "x ";
                    }
                }
                else if (list[x]->getTrig() == COS)
                {
                    if (list[x]->getOuter() * list[x]->getInner() < 0)
                    {
                        if (list[x]->getOuter() == 1)
                        {
                            if (list[x]->getInner() == -1)
                                file << "sin -x ";
                        }
                        else
                            if (list[x]->getInner() == 1)
                                if (list[x]->getOuter() == -1)
                                    file << "sin x ";
                                else
                                    file << list[x]->getOuter() * -1 << "sin x ";
                            else
                                file << list[x]->getOuter() * list[x]->getInner() * -1 << "sin " << list[x]->getInner() << "x ";
                    }
                    else
                    {
                        file << list[x]->getOuter() * list[x]->getInner() * -1 << "sin " << list[x]->getInner() << "x ";
                    }
                }
            }
            else if (list[x]->getExponent() == 0)
            {
                file << 0 << " ";
            }
            else if (list[x]->getExponent() == 1)
            {
                file << list[x]->getOuter() << " ";
            }
            else if (list[x]->getExponent() == 2)
            {
                file << list[x]->getOuter() * 2 << "x ";
            }
            else
            {
                file << list[x]->getOuter() * list[x]->getExponent() << "x^" << list[x]->getExponent() - 1 << " ";
            }
        }
        else
        {
            if (list[x]->getTrig())
            {
                if (list[x]->getTrig() == TAN)
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
                else if (list[x]->getTrig() == SIN)
                {
                    if (list[x]->getOuter() * list[x]->getInner() > 0)
                    {
                        file << "+ " << list[x]->getOuter() * list[x]->getInner() << "cos " << list[x]->getInner() << "x ";
                    }
                    else
                        file << "- " << list[x]->getOuter() * list[x]->getInner() * -1 << "cos " << list[x]->getInner() << "x ";

                }
                else if (list[x]->getTrig() == COS)
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
            else if (list[x]->getExponent() == 0)
            {
                file << "+ " << 0 << " ";
            }
            else if (list[x]->getExponent() == 1)
            {
                if (list[x]->getOuter() > 0)
                    file << "+ " << list[x]->getOuter() << " ";
                else
                    file << "- " << -1 * list[x]->getOuter() << " ";
            }
            else if (list[x]->getExponent() == 2)
            {
                if (list[x]->getOuter() > 0)
                    file << "+ " << list[x]->getOuter() * 2 << "x ";
                else
                    file << "- " << -1 * list[x]->getOuter() * 2 << "x ";
            }
            else
            {
                if (list[x]->getOuter() * list[x]->getExponent() > 0)
                    file << "+ " << list[x]->getOuter() * list[x]->getExponent() << "x^" << list[x]->getExponent() - 1 << " ";
                else
                    file << "- " << -1 * list[x]->getOuter() * list[x]->getExponent() << "x^" << list[x]->getExponent() - 1 << " ";
            }
        }
        x++;
    }
    file << std::endl;
    file.close();
}
