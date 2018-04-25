#ifndef LIST_H
#define LIST_H
typedef struct node{
    struct node *next;
    int info;
}_node;

_node *newNode(int info);
_node *insertTail(_node *node, int info);
void show(_node *node);
void clear(_node *node);

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
