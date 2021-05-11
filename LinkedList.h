#ifndef LINKEDLIST_H
#define LINKEDLIST_H 

#include "Node.h"
#include "Tile.h"
#include <string>

class LinkedList {

public:
    LinkedList();
    ~LinkedList();
    void addNode(Tile* t);
    void addBack(Tile* t);

    // get node takes the node out of linkedlist
    Tile* getNode(Colour c, Shape s);
    Tile* pop();
    void removeAllNodes();

    void printNodes();
    std::string savingNodes();
    int getLength();
    std::string printingNodesWithCoordinates(std::string space);
    
private:
    std::string printingNodes(std::string space);
    
    Node* head;
    int length;

};

#endif // LINKEDLIST_H 