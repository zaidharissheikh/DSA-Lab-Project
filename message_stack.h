#pragma once
#ifndef MESSAGE_STACK_H
#define MESSAGE_STACK_H
#include <iostream>
#include <string>
using namespace std;

class Message {
public:
    string sender;       
    string content;      
    string timestamp;    

    Message(const string& sender, const string& content, const string& timestamp) : sender(sender), content(content), timestamp(timestamp) {}

    void display() 
    {
        cout << "[" << timestamp << "] " << sender << ": " << content << endl;
    }
};

struct MessageNode {
    Message data;
    MessageNode* next;
    MessageNode(const Message& message, MessageNode* nextNode = NULL) : data(message), next(nextNode) {}
};

class MessageStack {
    MessageNode* top_ptr; 
    int count;      //number of messages in the stack

public:
    MessageStack() : top_ptr(NULL), count(0) {}

    ~MessageStack() 
    {
        clear();
    }

    void push(const Message& message)
    {
        MessageNode* newNode = new MessageNode(message, top_ptr);
        top_ptr = newNode;
        ++count;
    }

    void pop()
    {
        if (empty()) {
            cout << "No messages to delete." << endl;
            return;
        }
        MessageNode* temp = top_ptr;
        top_ptr = top_ptr->next;
        delete temp;
        --count;
    }

    Message top() const 
    {
        if (empty()) {
            cout << "No messages to show." << endl;
            return Message("", "", "");
        }
        return top_ptr->data;
    }

    bool empty() const {
        return top_ptr == NULL;
    }

    int size() const 
    {
        return count;
    }

    void display()  
    {
        if (empty()) {
            cout << "Conversation empty. Start one now." << endl;
            return;
        }
        MessageNode* current = top_ptr;
        cout << "Conversation history (most recent first):" << endl;
        while (current != NULL)
        {
            current->data.display();
            current = current->next;
        }
    }

    void clear() 
    {
        while (!empty()) {
            pop();
        }
    }
};
#endif 
