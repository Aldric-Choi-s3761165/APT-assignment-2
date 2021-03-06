#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() {
    this->head = nullptr;
    this->length = 0;
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
    head = n;
    length++;
}

void LinkedList::addBack(Tile* t){
    Node* n = new Node(t, nullptr);
    Node* prev = head;
    
    if(prev != nullptr) {
        while(prev->getNext() != nullptr) {
            prev = prev->getNext();
        }
        prev->setNext(n);
    }
    else {
        head = n;
    }
    length++;
}

Tile* LinkedList::getNode(Colour c, Shape s) {
    Node* current = head;
    Node* prev = nullptr;
    Tile* returnTile = nullptr;

    for(int i = 0; i < length; i++) 
    {
        if(current->getTile()->getColour() == c && current->getTile()->getShape() == s)  
        {
            if(prev == nullptr) {
                head = current->getNext();
            }
            else {
                prev->setNext(current->getNext());
            }
            
            returnTile = current->getTile();
            length--;
            i = length;
        }
        else {
            prev = current;
            current = current->getNext();
        } 
    }

    return returnTile;
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
    std::cout << printingNodes(", ") << std::endl;
}

std::string LinkedList::savingNodes() {
    return printingNodes(",");
}

std::string LinkedList::printingNodes(std::string space) {
    Node* upto = head;
    std::string printing;
    
    if(head != nullptr) {
        for(int i = 0; i < length - 1; i++) {
            printing = printing + upto->getTile()->getColour() + std::to_string(upto->getTile()->getShape()) + space;
            upto = upto->getNext();
        }
        
        printing = printing + upto->getTile()->getColour() + std::to_string(upto->getTile()->getShape()); 
    }

    return printing;
}

std::string LinkedList::printingNodesWithCoordinates(std::string space) {
    Node* upto = head;
    std::string printing;
    
    if(head != nullptr) {
        for(int i = 0; i < length - 1; i++) {
            
            printing = printing + upto->getTile()->getColour() + std::to_string(upto->getTile()->getShape()) + "@" 
            + upto->getTile()->getCharColour(upto->getTile()->getRow()) + std::to_string(upto->getTile()->getCol()) + space;
            
            upto = upto->getNext();
        }
        
        printing = printing + upto->getTile()->getColour() + std::to_string(upto->getTile()->getShape()) + "@" 
        + upto->getTile()->getCharColour(upto->getTile()->getRow()) + std::to_string(upto->getTile()->getCol()); 
    }

    return printing;
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