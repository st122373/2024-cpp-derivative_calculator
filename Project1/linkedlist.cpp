#include "Linkedlist.h"

Linkedlist::Linkedlist()
{
    head = nullptr;
}

Linkedlist::Linkedlist(Linkedlist& list)
{
    Node* iter = list.head;
    if (iter == nullptr)
    {
        head = nullptr;
        return;
    }
    head = iter;

    Node* current = head;

    while (iter != nullptr)
    {
        current->setNext(iter);
        iter = iter->getNext();
        current = current->getNext();
    }
}

Linkedlist::~Linkedlist() {

    deleteList();

}
void Linkedlist::deleteList()
{
    Node* iter = head;
    while (iter != nullptr)
    {
        Node* placeholder = iter;
        iter = iter->getNext();
        delete placeholder;
    }
    head = nullptr;

}

void Linkedlist::addNode(Node* n)
{
    if (head == nullptr)
    {
        head = n;
        return;
    }
    Node* iter = head;
    while (iter->getNext() != nullptr)
    {
        iter = iter->getNext();
    }
    iter->setNext(n);
}

Node* Linkedlist::getHead()
{
    return  head;
}

void Linkedlist::sort()
{
    Node* iter = head;
    if (iter == nullptr)
        return;
    bool swap = false;
    do {
        swap = false;
        Node* reti = iter->getNext();
        while (reti != nullptr)
        {
            if (iter->getExponent() < reti->getExponent())
            {
                int outer1 = iter->getOuter();
                int inner1 = iter->getInner();
                int exponent1 = iter->getExponent();
                int t1 = iter->getTrig();

                iter->swapNodes(reti->getOuter(), reti->getInner(), reti->getTrig(), reti->getExponent());
                reti->swapNodes(outer1, inner1, t1, exponent1);

                swap = true;
            }
            iter = iter->getNext();
            reti = reti->getNext();
        }

    } while (swap);
}

int Linkedlist::getSize()
{
    Node* iter = head;
    int size = 0;
    while (iter != nullptr)
    {
        size++;
        iter = iter->getNext();
    }
    return size;
}

void Linkedlist::operator ++ ()
{
    Node* placeholder = head;
    Node* n = new Node();
    head = n;
    n->setNext(placeholder);
}

Node* Linkedlist::operator [] (int i)
{
    Node* iter = head;
    while (iter != nullptr && i > 0) {
        iter = iter->getNext();
        i--;
    }
    return iter;
}