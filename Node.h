#ifndef NODE_H
#define NODE_H 

#include "Tile.h"

class Node {

public:
    Node(Tile* t, Node* n);
    ~Node();
    Node* getNext();
    Tile* getTile();
    void setNext(Node* n);

private:
    Node* next;
    Tile* tile;

};

#endif // NODE_H 