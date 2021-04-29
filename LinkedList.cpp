#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
    head = nullptr;
    length = 0;
}

LinkedList::LinkedList(LinkedList& other) {
    head = nullptr;
    length = 0;

    for(int i = other.length - 1; i >= 0; i--) {
        Tile* temp = other.getTile(i);
        Tile* n = new Tile(temp->getColour(), temp->getShape());
        addNode(n);
    }
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

// precondition: int is within range else nullptr
// LinkedList constructor relies on int being within range and that length
// is up to date
Tile* LinkedList::getTile(int i) {
    Node* upto = head;
    int counter = 0;
    Tile* tile = nullptr;

    if(i < 0) {
        upto = nullptr;
    }

    while(upto != nullptr) {
        if(counter == i) {
            tile = upto->getTile();
            upto = nullptr;
        }
        else {
            upto = upto->getNext();
            counter++;
        }
    }

    return tile;
}

void LinkedList::addNode(Tile* t) {
    Node* n = new Node(t, head);
    this->head = n;
    length++;
}

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