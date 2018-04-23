#include "list.h"
#include <iostream>

using namespace std;

List::List()
{
    this->top = NULL;
}

void List::printList()
{
    if(top)this->top->printList();
    else cout << "(!)" << endl;
}

void List::clearList()
{
    if(this->top) this->top->clearList();
    this->top = NULL;
}

List::~List()
{

}

void List::addNode(int info)
{
    if(!top) top = new Node(info);
    else this->top->addNode(info);
}

void Node::addNode(int info)
{
    if(this->next) this->next->addNode(info);
    else this->next = new Node(info);
}


void Node::printList()
{
    cout << "("
         << this->info
         << ")->";
    if(this->next) this->next->printList();
    else cout << "(!)\n";
}

void Node::clearList()
{
    if(this->next) this->next->clearList();
    delete this;
}

Node::Node(int info)
{
    this->info = info;
    this->next = NULL;
}
Node::Node()
{
    this->next = NULL;
}
Node::~Node()
{

}
