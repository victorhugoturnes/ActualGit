#include <iostream>
#include "linkedlist.h"

using namespace std;

int main()
{
    LinkedList *test = new LinkedList(1);
    test->insertTail(2);
    test->insertTail(2);
    test->insertTail(2);
    test->insertHead(2);
    test->insertHead(7);
    test->insertTail(5);
    test->insertTail(4);
    test->insertTail(3);
    test->printList();
    test->destroy();
    test;
    return 0;
}

