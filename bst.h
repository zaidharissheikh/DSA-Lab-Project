#pragma once
#include <iostream>
using namespace std;

struct TreeNode {
    string username;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const string& username) : username(username), left(NULL), right(NULL) {}
};
class BST {
    TreeNode* root;  

    TreeNode* insert(TreeNode* node, const string& username) 
    {
        if (node == NULL) {
            return new TreeNode(username); 
        }
        if (username < node->username) {
            node->left = insert(node->left, username); 
        }
        else if (username > node->username) {
            node->right = insert(node->right, username); 
        }
        else {
            cout << "Username \"" << username << "\" already exists in the BST." << endl;
        }
        return node;
    }

    bool search(TreeNode* node, const string& username) const 
    {
        if (node == NULL) {
            return false; 
        }
        if (username == node->username) {
            return true; 
        }
        if (username < node->username) {
            return search(node->left, username); 
        }
        return search(node->right, username); 
    }

    void inOrder(TreeNode* node) const 
    {
        if (node == NULL) {
            return;
        }
        inOrder(node->left);               
        cout << node->username << " ";     
        inOrder(node->right);              
    }

    void clear(TreeNode* node) 
    {
        if (node == NULL) {
            return;
        }
        clear(node->left);  
        clear(node->right); 
        delete node;
    }

public:
    BST() : root(NULL) {}

    ~BST() {
        clear(root); 
    }

    void insert(const string& username) 
    {
        root = insert(root, username);
    }

    bool search(const string& username) const 
    {
        return search(root, username);
    }

    void display() const
    {
        cout << "Usernames in sorted order: ";
        inOrder(root);
        cout << endl;
    }

    void clear()
    {
        clear(root);
        root = NULL;
    }
};
#endif 
