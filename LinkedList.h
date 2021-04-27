#ifndef LINKEDLIST_H
#define LINKEDLIST_H 

#include "Node.h"
#include "Tile.h"

class LinkedList {

public:
    LinkedList();
    ~LinkedList();
    void addNode(Tile* t);
    void removeNode(Tile* t);
    void removeAllNodes();
    void printNodes();

private:
    Node* head;
    // int length;

};

#endif // LINKEDLIST_H 