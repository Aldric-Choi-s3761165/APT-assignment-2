#include "Node.h"

Node::Node(Tile* t, Node* n) {
    this->tile = t;
    this->next = n;
}

Node* Node::getNext() {
    return next;
}

Tile* Node::getTile() {
    return tile;
}

void Node::setNext(Node* n) {
    this->next = n;
}
