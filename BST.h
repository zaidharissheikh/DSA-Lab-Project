#ifndef BST_H
#define BST_H

#include <string>
using namespace std;

// Forward declaration of the BSTNode class
class BSTNode {
public:
    string key;
    BSTNode* left;
    BSTNode* right;

    // Constructor for BSTNode
    BSTNode(const string& k, void* d = nullptr) : key(k), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Helper functions
    void freeMemory(BSTNode* node);
    BSTNode* insert(BSTNode* node, const string& key);  // Updated: only key argument
    void preorderTraversal(BSTNode* node);

public:
    // Constructor & Destructor
    BST();
    ~BST();

    // Public methods
    bool insert(const string& key);
    void preorder();
};

#endif // BST_H
