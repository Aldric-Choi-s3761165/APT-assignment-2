#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
    length = 0;
}

LinkedList::~LinkedList() {
    Node* current = head;
    Node* next;

    while(current != nullptr) {
        next = current->getNext();
        delete current;
        current = next;
    }
}

void LinkedList::addNode(Tile* t) {
    Node* n = new Node(t, head);
    this->head = n;
    length++;
}

// fix removeNode since first node needs to update head to next etc
void LinkedList::removeNode(Tile* t) {
    Node* current = head;
    Node* prev = nullptr;

    while(current->getNext() != nullptr) {
        prev = current;
        current = current->getNext();

        //fix check for checking value and colour instead of == since they value different addresses
        if(current->getTile() == t)  {
            prev->setNext(current->getNext());
            delete current;
            length--;
        }
    }

}

void LinkedList::removeAllNodes() {
    Node* current = head;
    Node* next = nullptr;

    while(current != nullptr) {
        next = current->getNext();
        delete current;
        current = next;
    }

    head = nullptr;
    length = 0;
}

void LinkedList::printNodes() {
    Node* upto = head;

    std::cout << "head->";
    while(upto != nullptr) {
        std::cout << "|" << upto->getTile()->getColour() << upto->getTile()->getShape() << "|-->";
        upto = upto->getNext();
    }
    std::cout << "null" << std::endl;
}

int LinkedList::getLength() {
    return this->length;
}

Tile* LinkedList::pop() {
    Tile* t = nullptr;

    if(head != nullptr) {
        Node* n = head;
        t = new Tile(n->getTile()->getColour(), n->getTile()->getShape());
        head = head->getNext();
        length--;
        delete n;
    }
    
    return t;
}