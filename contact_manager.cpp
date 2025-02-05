#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
using namespace std;

struct Contact {
    string name;
    string phone;
    string email;
};

void addContact() {
    Contact contact;
    cout << "Enter Name: ";
    getline(cin, contact.name);
    cout << "Enter Phone: ";
    getline(cin, contact.phone);
    cout << "Enter Email: ";
    getline(cin, contact.email);
    
    ofstream file("contacts.txt", ios::app);
    if (file.is_open()) {
        file << contact.name << "," << contact.phone << "," << contact.email << "\n";
        file.close();
        cout << "Contact added successfully!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

void viewContacts() {
    ifstream file("contacts.txt");
    string line;
    
    cout << "\n--- Contact List ---\n";
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, email;
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        
        cout << "Name: " << name << " | Phone: " << phone << " | Email: " << email << "\n";
    }
    file.close();
}

void searchContact() {
    string searchName;
    cout << "Enter name to search: ";
    getline(cin, searchName);
    ifstream file("contacts.txt");
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, email;
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        
        if (name == searchName) {
            cout << "\nContact Found:\n";
            cout << "Name: " << name << " | Phone: " << phone << " | Email: " << email << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Contact not found!\n";
    }
    file.close();
}

void deleteContact() {
    string deleteName;
    cout << "Enter name to delete: ";
    getline(cin, deleteName);
    ifstream file("contacts.txt");
    vector<string> contacts;
    string line;
    bool found = false;
    
    while (getline(file, line)) {
        stringstream ss(line);
        string name, phone, email;
        getline(ss, name, ',');
        getline(ss, phone, ',');
        getline(ss, email, ',');
        
        if (name != deleteName) {
            contacts.push_back(line);
        } else {
            found = true;
        }
    }
    file.close();
    
    ofstream outFile("contacts.txt");
    for (const auto &contact : contacts) {
        outFile << contact << "\n";
    }
    outFile.close();
    
    if (found) {
        cout << "Contact deleted successfully!\n";
    } else {
        cout << "Contact not found!\n";
    }
}

int main() {
    int choice;
    do {
        cout << "\nContact Management System\n";
        cout << "1. Add Contact\n";
        cout << "2. View Contacts\n";
        cout << "3. Search Contact\n";
        cout << "4. Delete Contact\n";
        cout << "5. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore();
        
        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option!\n";
        }
    } while (choice != 5);
    
    return 0;
}
