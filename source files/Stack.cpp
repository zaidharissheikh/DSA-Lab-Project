#include "Stack.h"
#include <stdexcept>
#include <iostream>

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::push(std::string data, time_t time) {
    StackNode* newNode = new StackNode(data);
    newNode->timestamp = time;
    newNode->next = top;
    top = newNode;
}

StackNode* Stack::pop() {
    if (isEmpty()) throw std::underflow_error("Stack Underflow");
    StackNode* temp = top;
    top = top->next;
    return temp;
}

StackNode* Stack::peek() {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return top;  // Return the top node to access both data and timestamp
}

void Stack::display() {
    if (isEmpty()) {
        std::cout << "Stack is empty!" << std::endl;
        return;
    }

    StackNode* current = top;
    while (current != nullptr) {
        // Convert timestamp to readable format
        char timeBuffer[26];  // Buffer to hold the formatted time string
        ctime_s(timeBuffer, sizeof(timeBuffer), &current->timestamp);  // Safe time conversion
        timeBuffer[24] = '\0'; // Remove the newline character from ctime

        std::cout << "Post: " << current->data << ", Time: " << timeBuffer << std::endl;
        current = current->next;
    }
}


