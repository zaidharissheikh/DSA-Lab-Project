#ifndef STACK_H
#define STACK_H

class StackNode {
public:
    int data;
    StackNode* next;
    StackNode(int data) : data(data), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;

public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    void push(int data);
    int pop();
    int peek() const;
};

#endif
