#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include "Contact.h"

using namespace std;

// Linked list node for collision handling (Separate Chaining)
struct HashNode {
    Contact data;
    HashNode* next;
    HashNode(Contact c) : data(c), next(nullptr) {}
};

class HashTable {
private:
    static const int TABLE_SIZE = 1009; // A prime number helps spread out the data
    HashNode* table[TABLE_SIZE];

    // Simple math trick to turn a phone string into an array index
    int hashFunction(string phone) {
        long long hashVal = 0;
        for (char c : phone) {
            if (c >= '0' && c <= '9') {
                hashVal = (hashVal * 10 + (c - '0')) % TABLE_SIZE;
            }
        }
        return hashVal;
    }
public:
    // Initialize empty table
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) table[i] = nullptr;
    }
    
    // Clean up all linked lists in the buckets to prevent leaks
    ~HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            HashNode* entry = table[i];
            while (entry != nullptr) {
                HashNode* prev = entry;
                entry = entry->next;
                delete prev;
            }
        }
    }
    
    // Put a contact into the hash table
    void insert(Contact c) {
        int hashVal = hashFunction(c.phone);
        HashNode* prev = nullptr;
        HashNode* entry = table[hashVal];
        
        // Traverse to the end of the chain if a collision happens
        while (entry != nullptr) {
            prev = entry;
            entry = entry->next;
        }
        if (entry == nullptr) {
            entry = new HashNode(c);
            if (prev == nullptr) table[hashVal] = entry; // First one in this bucket
            else prev->next = entry; // Attach to the chain
        }
    }
    
    // Find a contact instantly using their phone number
    Contact* search(string phone) {
        int hashVal = hashFunction(phone);
        HashNode* entry = table[hashVal];
        
        while (entry != nullptr) {
            if (entry->data.phone == phone) return &(entry->data);
            entry = entry->next;
        }
        return nullptr; // Not found
    }
};
#endif
