#include "BST.h"
#include<iostream>

// Constructor
BST::BST() : root(nullptr) {}

// Destructor
BST::~BST() {
    freeMemory(root);
}

// Helper function to free memory of nodes
void BST::freeMemory(BSTNode* node) {
    if (node) {
        freeMemory(node->left);
        freeMemory(node->right);
        delete node;
    }
}

bool BST::insert(const string& key) {
    root = insert(root, key);  // Insert with only the key
    return true;
}

// Recursive helper for insertion (updated to use only the key)
BSTNode* BST::insert(BSTNode* node, const string& key) {
    if (!node) {
        return new BSTNode(key, nullptr);  // no data assigned
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    return node;
}

// Perform an inorder traversal
void BST::preorder() {
    preorderTraversal(root);
}

// Recursive helper for inorder traversal
void BST::preorderTraversal(BSTNode* node) {
    if (node) {
        preorderTraversal(node->left);
        preorderTraversal(node->right);
        cout << node->key << endl;
    }
}
