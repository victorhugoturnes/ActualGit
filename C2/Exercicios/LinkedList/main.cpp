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
    return 0;
}

