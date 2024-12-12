#ifndef LINKEDLIST_H
#define LINKEDLIST_H

class Node {
public:
    int data;
    Node* next;

    Node(int data);
};

class LinkedList {
public:
    Node* head;

    LinkedList();
    ~LinkedList();

    void insertAtBeginning(int data);
    void insertAtEnd(int data);
    void deleteNode(int data);
    void display() const;
};

#endif
