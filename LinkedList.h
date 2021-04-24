#include "Node.h"
#include "Tile.h"

class LinkedList {

public:
    LinkedList();
    void addNode(Tile t);

private:
    Node* head;
    Node* tail;
    int length;

};