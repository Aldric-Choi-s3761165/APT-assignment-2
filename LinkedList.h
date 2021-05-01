#ifndef LINKEDLIST_H
#define LINKEDLIST_H 

#include "Node.h"
#include "Tile.h"

class LinkedList {

public:
    LinkedList();
    ~LinkedList();
    void addNode(Tile* t);
    void addBack(Tile* t);
    Tile* removeNode(Colour c, Shape s);
    void removeAllNodes();
    void printNodes();
    int getLength();
    Tile* pop();

private:
    Node* head;
    Node* tail;
    int length;

};

#endif // LINKEDLIST_H 