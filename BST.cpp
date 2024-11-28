#include "BST.h"

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

// Search for a node in the BST
void* BST::search(const string& key) {
    BSTNode* result = search(root, key);
    return result ? result->data : nullptr;
}

// Recursive helper for searching
BSTNode* BST::search(BSTNode* node, const string& key) {
    if (!node || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    return search(node->right, key);
}

// Remove a node from the BST
void BST::remove(const string& key) {
    root = remove(root, key);
}

// Recursive helper for deletion
BSTNode* BST::remove(BSTNode* node, const string& key) {
    if (!node) {
        return nullptr;
    }
    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        // Node with only one child or no child
        if (!node->left) {
            BSTNode* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            BSTNode* temp = node->left;
            delete node;
            return temp;
        }

        // Node with two children: Get the inorder successor
        BSTNode* temp = findMin(node->right);
        node->key = temp->key;
        node->data = temp->data;
        node->right = remove(node->right, temp->key);
    }
    return node;
}

// Helper function to find the minimum node in a subtree
BSTNode* BST::findMin(BSTNode* node) {
    while (node && node->left) {
        node = node->left;
    }
    return node;
}

// Perform an inorder traversal
void BST::inorder(void (*visit)(BSTNode*)) {
    inorderTraversal(root, visit);
}

// Recursive helper for inorder traversal
void BST::inorderTraversal(BSTNode* node, void (*visit)(BSTNode*)) {
    if (node) {
        inorderTraversal(node->left, visit);
        visit(node);
        inorderTraversal(node->right, visit);
    }
}
