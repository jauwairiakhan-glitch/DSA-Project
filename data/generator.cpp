#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

int main() {
    // Seed the random number generator so we get different data every time
    srand(time(0));
    
    // Create and open the text file
    ofstream file("contacts.txt");
    if (!file) {
        cout << "Oops! Could not create the file.\n";
        return 1;
    }
    
    // Arrays of dummy names to mix and match
    string firstNames[] = {"Ali", "Umer", "Sufian", "Jauwairia", "Hamza", "Ayesha", "Sara", "Bilal", "Zain", "Fatima"};
    string lastNames[] = {"Khan", "Farooqi", "Ahmed", "Ali", "Hussain", "Tariq", "Malik", "Shah", "Iqbal", "Raza"};

    // Generate exactly 1000 contacts to meet the project requirement
    for (int i = 0; i < 1000; i++) {
        // Pick a random first and last name
        string name = firstNames[rand() % 10] + " " + lastNames[rand() % 10] + " " + to_string(i + 1);
        // Create a random Pakistani format mobile number (e.g., 03XX-XXXXXXX)
        string phone = "03" + to_string(10 + rand() % 40) + to_string(1000000 + rand() % 9000000);
        string email = "user" + to_string(i + 1) + "@test.com";
        int calls = rand() % 100;
        
        // Write the comma-separated row to the file
        file << name << "," << phone << "," << email << "," << calls << "\n";
    }
    
    file.close();
    cout << "Success! 1000 dummy contacts generated in contacts.txt\n";
    return 0;
}
