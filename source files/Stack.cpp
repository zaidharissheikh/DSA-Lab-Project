#include "Stack.h"
#include <stdexcept>

Stack::Stack() : top(nullptr) {}

Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

bool Stack::isEmpty() const {
    return top == nullptr;
}

void Stack::push(int data) {
    StackNode* newNode = new StackNode(data);
    newNode->next = top;
    top = newNode;
}

int Stack::pop() {
    if (isEmpty()) throw std::underflow_error("Stack Underflow");
    StackNode* temp = top;
    int poppedData = top->data;
    top = top->next;
    delete temp;
    return poppedData;
}

int Stack::peek() const {
    if (isEmpty()) throw std::underflow_error("Stack is empty");
    return top->data;
}
