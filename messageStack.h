#pragma once
#ifndef MESSAGESTACK_H
#define MESSAGESTACK_H
#include <string>
class mNode {
public:
    std::string data;
    std::string receiver;
    std::string sender;
    mNode* next;
    mNode(std::string data, std::string sender, std::string receiver) : data(data), sender(sender), receiver(receiver), next(nullptr) {}
};

class messageStack {
private:
    mNode* top;

public:
    messageStack();
    ~messageStack();

    bool isEmpty() const;
    void push(std::string data, std::string sender, std::string receiver);
    std::string pop();
    std::string peek() const;
    void printMsgs(const std::string& sender, const std::string& receiver);
};
#endif
