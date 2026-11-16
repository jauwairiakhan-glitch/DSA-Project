#include <iostream>
#include <fstream>
#include <string>
#include "../include/Contact.h"
#include "../include/AVLTree.h"
#include "../include/HashTable.h"
#include "../include/DoublyLinkedList.h"

using namespace std;

// Read the text file and fill up our data structures
void loadData(AVLTree& avl, HashTable& hashT) {
    ifstream file("../data/contacts.txt");
    if (!file) {
        // Fallback if run from root directory
        file.open("data/contacts.txt");
    }
    if (!file) {
        file.open("contacts.txt");
    }
    if (!file) {
        cout << "Oops! Cannot open contacts.txt. Make sure to run generator.cpp first.\n";
        return;
    }
    
    string name, phone, email, callsStr;
    int count = 0;
    
    // Read the comma-separated data line by line
    while (getline(file, name, ',') && getline(file, phone, ',') && 
           getline(file, email, ',') && getline(file, callsStr)) {
               
        // Convert the string call count to an integer
        int calls = stoi(callsStr);
        Contact c(name, phone, email, calls);
        
        // Put the data into our structures
        avl.insert(c);
        hashT.insert(c);
        count++;
    }
    file.close();
    cout << count << " contacts loaded successfully into the system.\n";
}

int main() {
    AVLTree phonebook;
    HashTable phoneLookup;
    DoublyLinkedList recentCalls;

    // Load the 1000 dummy records right when the program starts
    loadData(phonebook, phoneLookup);

    int choice;
    do {
        // Clean console menu
        cout << "\n=== Smart Phonebook Menu ===\n";
        cout << "1. Display All Contacts (A-Z)\n";
        cout << "2. Search by Phone Number\n";
        cout << "3. Call a Contact\n";
        cout << "4. View Recent Calls\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        
        // Input validation so letters don't crash the program
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a valid number.\n";
            continue;
        }

        if (choice == 1) {
            cout << "\n--- Contact List ---\n";
            phonebook.display();
        } 
        else if (choice == 2) {
            string num;
            cout << "Enter the phone number to search: ";
            cin >> num;
            Contact* c = phoneLookup.search(num);
            if (c) cout << "Match Found: " << c->name << " | Email: " << c->email << "\n";
            else cout << "Sorry, this contact is not in the phonebook.\n";
        } 
        else if (choice == 3) {
            string num;
            cout << "Enter the phone number you want to call: ";
            cin >> num;
            Contact* c = phoneLookup.search(num);
            if (c) {
                cout << "Dialing " << c->name << "...\n";
                // Add this call to our doubly linked list history
                recentCalls.addCall(*c);
            } else {
                cout << "Number not recognized.\n";
            }
        } 
        else if (choice == 4) {
            cout << "\n--- Recent Calls Log ---\n";
            recentCalls.displayRecent();
        }
    } while (choice != 5);

    cout << "Closing the phonebook. Goodbye!\n";
    return 0;
}
