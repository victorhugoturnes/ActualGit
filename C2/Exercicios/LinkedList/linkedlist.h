#ifndef LINKEDLIST_H
#define LINKEDLIST_H


class LinkedList
{
private:
    int info;
    LinkedList *next;
public:
    LinkedList(int info);
    void printList();
    void insertTail(int info);
    void insertHead(int info);
    void destroy();
};

#endif // LINKEDLIST_H
