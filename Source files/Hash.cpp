#include "hash.h"
#include <iostream>

using namespace std;

// Hash function: Computes the index based on the username
int HashTable::hashFunction(const string& key) const {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;  // Using a prime multiplier for better distribution
    }
    return hash;
}

// Constructor: Initializes the hash table
HashTable::HashTable(int size) {
    capacity = size;
    table = new Node_Hash * [capacity];  // Dynamically allocate memory for the hash table
    for (int i = 0; i < capacity; i++) {
        table[i] = nullptr;  // Initialize all buckets to nullptr
    }
}

// Destructor: Frees the allocated memory
HashTable::~HashTable() {
    for (int i = 0; i < capacity; i++) {
        Node_Hash* current = table[i];
        while (current) {
            Node_Hash* temp = current;
            current = current->next;
            delete temp;
        }
    }
    delete[] table;
}

// Insert: Adds a new username-password pair
bool HashTable::insert(const string& username, const string& password) {
    int index = hashFunction(username);
    Node_Hash* newNode = new Node_Hash(username, password);

    // Insert at the head of the linked list for simplicity
    newNode->next = table[index];
    table[index] = newNode;
    return true;
}

// Search: Retrieves the password for a given username
string HashTable::search(const string& username) const {
    int index = hashFunction(username);
    Node_Hash* current = table[index];

    while (current) {
        if (current->username == username) {
            return current->password;  // Return the password if username is found
        }
        current = current->next;
    }
    return "";  // Return an empty string if username is not found
}

// Display: Prints the hash table (for debugging)
void HashTable::display() const {
    for (int i = 0; i < capacity; i++) {
        cout << "Bucket " << i << ": ";
        Node_Hash* current = table[i];
        while (current) {
            cout << "(" << current->username << ", " << current->password << ") -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }
}
