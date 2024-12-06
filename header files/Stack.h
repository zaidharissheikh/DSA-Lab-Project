#ifndef STACK_H
#define STACK_H

#include<string>

class StackNode {
public:
    std::string data;
    time_t timestamp;
    StackNode* next;
    StackNode(std::string data) : data(data), next(nullptr) {}
};

class Stack {
private:
    StackNode* top;

public:
    Stack();
    ~Stack();

    bool isEmpty() const;
    void push(std::string data, time_t time);
    StackNode* pop();
    StackNode* peek();
    void display();
};

#endif
