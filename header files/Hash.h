#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>

using namespace std;

// Node structure for the linked list used for chaining
struct Node_Hash {
    string username;  // Username
    string password;  // Password
    Node_Hash* next;

    Node_Hash(const string& user, const string& pass)
        : username(user), password(pass), next(nullptr) {}
};

class HashTable {
private:
    Node_Hash** table;  // Array of pointers to linked lists (DMA)
    int capacity;  // Size of the hash table

    // Hash function to map keys to table indices
    int hashFunction(const string& key) const;

public:
    HashTable(int size);      // Constructor to initialize hash table with a given size
    ~HashTable();             // Destructor to free dynamically allocated memory

    bool insert(const string& username, const string& password);  // Insert username-password pair
    string search(const string& username) const;                 // Search for a password by username
    void display() const;                                        // Display the hash table (for debugging)
};

#endif
