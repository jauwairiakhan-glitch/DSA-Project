#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include "Contact.h"

using namespace std;

// Node for the doubly linked list
struct NodeDLL {
    Contact data;
    NodeDLL* next;
    NodeDLL* prev;
    
    NodeDLL(Contact c) : data(c), next(nullptr), prev(nullptr) {}
};

class DoublyLinkedList {
private:
    NodeDLL* head;
    NodeDLL* tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    
    // Destructor clears memory so we don't get memory leak penalties
    ~DoublyLinkedList() {
        while (head != nullptr) {
            NodeDLL* temp = head;
            head = head->next;
            delete temp;
        }
    }
    
    // Insert new calls at the start (head) so recent ones show first
    void addCall(Contact c) {
        NodeDLL* newNode = new NodeDLL(c);
        if (!head) {
            // First call ever
            head = tail = newNode;
        } else {
            // Push the current head back and make this the new head
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    
    // Just show the last 10 calls to keep the screen clean
    void displayRecent() {
        NodeDLL* temp = head;
        int count = 0;
        while (temp != nullptr && count < 10) { 
            cout << temp->data.name << " (" << temp->data.phone << ")\n";
            temp = temp->next;
            count++;
        }
    }
};
#endif
