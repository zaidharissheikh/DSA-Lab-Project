#ifndef BST_H
#define BST_H

#include <string>
using namespace std;

// Forward declaration of the BSTNode class
class BSTNode {
public:
    string key;
    void* data;
    BSTNode* left;
    BSTNode* right;

    // Constructor for BSTNode
    BSTNode(const string& k, void* d = nullptr) : key(k), data(d), left(nullptr), right(nullptr) {}
};

class BST {
private:
    BSTNode* root;

    // Helper functions
    void freeMemory(BSTNode* node);
    BSTNode* insert(BSTNode* node, const string& key);  // Updated: only key argument
    BSTNode* search(BSTNode* node, const string& key);
    BSTNode* remove(BSTNode* node, const string& key);
    BSTNode* findMin(BSTNode* node);
    void inorderTraversal(BSTNode* node, void (*visit)(BSTNode*));

public:
    // Constructor & Destructor
    BST();
    ~BST();

    // Public methods
    bool insert(const string& key);
    void* search(const string& key);
    void remove(const string& key);
    void inorder(void (*visit)(BSTNode*));
};

#endif // BST_H
