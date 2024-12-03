#include "messageStack.h"
#include <stdexcept>
#include <iostream>
using namespace std;
messageStack::messageStack() : top(nullptr) {}

messageStack::~messageStack() {
    while (!isEmpty()) {
        pop();
    }
}

bool messageStack::isEmpty() const {
    return top == nullptr;
}

void messageStack::push(string data, string sender, string receiver) {
    mNode* newNode = new mNode(data, sender, receiver);
    newNode->next = top;
    top = newNode;
}

string messageStack::pop() {
    if (isEmpty()) 
        cout << "Stack is empty";
    mNode* temp = top;
    string poppedData = top->data;
    top = top->next;
    delete temp;
    return poppedData;
}

string messageStack::peek() const {
    if (isEmpty()) 
        cout << "Stack is empty";
    return top->data;
}

void messageStack::printMsgs(const string& sender, const string& receiver)
{
    if (isEmpty())
        cout << "NO messages to show\n";
    mNode* temp = top;
    while (temp != NULL)
    {
        if (temp->receiver == receiver || temp->sender == receiver)
        {
            cout << temp->sender << ": " << temp->data << endl;
        }
        temp = temp->next;
    }
}

