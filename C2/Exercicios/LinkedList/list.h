#ifndef LIST_H
#define LIST_H


class Node
{
private:
    Node *next;
    int info;
public:
    Node();
    Node(int info);
    ~Node();
    void addNode(int info);
    void printList();
    void clearList();
};


class List : private Node
{
private:
    Node *top;
public:
    List();
    void addNode(int info);
    void printList();
    void clearList();
    ~List();
};

#endif // LIST_H
