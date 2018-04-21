#include "linkedlist.h"
#include <iostream>

using namespace std;

LinkedList::LinkedList(int info)
{
    this->info = info;
    this->next = NULL;
}

void LinkedList::printList()
{
    if(this != NULL)
    {
        cout << "("
             << info
             << ") ->";
        this->next->printList();
    }else cout << "(!)" << endl;
}

void LinkedList::insertTail(int info)
{
    this->next == NULL ? (void)(this->next = new LinkedList(info)) : this->next->insertTail(info);
}

void LinkedList::insertHead(int info)
{
    LinkedList *aux = new LinkedList(this->info);
    aux->next = this->next;
    this->info = info;
    this->next = aux;
}

void LinkedList::destroy()
{
    if(this->next) this->next->destroy();
    delete this;
}
