#pragma once
#ifndef FRIENDREQUESTQUEUE_H
#define FRIENDREQUESTQUEUE_H
#include "Queue.h"
#include <iostream>
#include <string>
using namespace std;

struct RequestNode {
    string sender;      // The username of the sender
    RequestNode* next;  // Pointer to the next node in the queue

    RequestNode(const string& senderName) : sender(senderName), next(nullptr) {}
};

class FriendRequestQueue {
private:
    RequestNode* front;  
    RequestNode* rear;   

public:
    FriendRequestQueue() : front(nullptr), rear(nullptr) {}

    void enqueue(const string& sender) {
        RequestNode* newNode = new RequestNode(sender);
        if (!rear) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;
            rear = newNode;
        }
        /*cout << "Friend request from " << sender << " added to the queue." << endl;*/
    }

    string dequeue() {
        if (isEmpty()) {
            cout << "No pending friend requests." << endl;
            return "";
        }
        RequestNode* temp = front;
        string sender = front->sender;
        front = front->next;
        if (!front)
            rear = nullptr;  
        delete temp;
        return sender;
    }

    void display() {
        if (isEmpty()) {
            return;
        }
        cout << "Pending Follow Requests:" << endl;
        RequestNode* temp = front;
        while (temp) {
            cout << "- " << temp->sender << endl;
            temp = temp->next;
        }
    }

    bool isEmpty() {
        return front == nullptr;
    }

    /*~FriendRequestQueue() {
        while (front) {
            RequestNode* temp = front;
            front = front->next;
            delete temp;
        }
    }*/
};
#endif
