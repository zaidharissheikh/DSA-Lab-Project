#pragma once
#ifndef QUEUE_H
#define QUEUE_H
#include <iostream>
#include <string>
using namespace std;

struct queue_node {
        string requests; //friend requests
        queue_node* next;
        queue_node(const string& value, queue_node* nextNode = NULL) : requests(value), next(nextNode) {}
};
//queue for friend requests and notifications
class Queue {
    queue_node* front_ptr; 
    queue_node* rear_ptr;  
    int count;    //number of elements in the queue

public:
    Queue() : front_ptr(NULL), rear_ptr(NULL), count(0) {}

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(const string& value) 
    {
        queue_node* newNode = new queue_node(value);
        if (empty()) {
            front_ptr = rear_ptr = newNode;
        }
        else {
            rear_ptr->next = newNode;
            rear_ptr = newNode;
        }
        ++count;
    }

    void dequeue() 
    {
        if (empty()) {
            cout << "Queue is empty. Cannot dequeue." << endl;
            return;
        }
        queue_node* temp = front_ptr;
        front_ptr = front_ptr->next;
        delete temp;
        --count;
        if (front_ptr == NULL) 
        { 
            rear_ptr = NULL;
        }
    }

    string front() const 
    {
        if (empty()) {
            cout << "Queue is empty. Cannot access front." << endl;
            return "";
        }
        return front_ptr->requests;
    }

    string rear() const 
    {
        if (empty()) {
            cout << "Queue is empty. Cannot access rear." << endl;
            //return an empty string in case of an empty queue
            return "";
        }
        return rear_ptr->requests;
    }

    bool empty() const 
    {
        return front_ptr == NULL;
    }

    int size() const {
        return count;
    }

    void print()
    {
        queue_node* temp = front_ptr;
        while (temp != NULL)
        {
            cout << temp->requests << endl;
            temp = temp->next;
        }
    }

    void clear() 
    {
        while (!empty()) 
        {
            dequeue();
        }
    }
};
#endif 
