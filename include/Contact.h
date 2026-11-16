#ifndef CONTACT_H
#define CONTACT_H
#include <string>

using namespace std;

// This holds the basic details for a single person in our phonebook
struct Contact {
    string name;
    string phone;
    string email;
    int callCount; // Tracks how many times we called this person

    // Constructor to easily create a new contact in one line
    Contact(string n = "", string p = "", string e = "", int c = 0) {
        name = n;
        phone = p;
        email = e;
        callCount = c;
    }
};
#endif
