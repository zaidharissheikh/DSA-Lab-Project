#ifndef QUEUE_H
#define QUEUE_H

struct QueueNode {
    int data;
    QueueNode* next;

    QueueNode(int val) {
        data = val;
        next = nullptr;
    }
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;

public:
    Queue();
    ~Queue();

    bool isEmpty() const;
    bool isFull() const;
    void enqueue(int data);
    int dequeue();
    int peek() const;
};

#endif
