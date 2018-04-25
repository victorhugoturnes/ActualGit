#include <iostream>
#include "list.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    List *test = new List;
    test->printList();
    test->addNode(2);
    test->addNode(3);
    test->addNode(4);
    test->printList();
    test->clearList();
    test->printList();
    _node *test2 = insertTail(NULL, 0);
    test2 = insertTail(test2, 1);
    test2 = insertTail(test2, 2);
    show(test2);
    clear(test2);
    return 0;
}

