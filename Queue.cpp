#include "Queue.h"
#include <stdexcept>



Queue::Queue() : front(nullptr), rear(nullptr) {}

Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

bool Queue::isFull() const {
    // Since we are using a linked list, the queue is theoretically never full (unless memory runs out).
    return false;
}

void Queue::enqueue(int data) {
    QueueNode* newNode = new QueueNode(data);
    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
}

int Queue::dequeue() {
    if (isEmpty()) throw std::underflow_error("Queue Underflow");

    QueueNode* temp = front;
    int data = front->data;
    front = front->next;

    // If the queue becomes empty, also set rear to nullptr
    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    return data;
}

int Queue::peek() const {
    if (isEmpty()) throw std::underflow_error("Queue is empty");
    return front->data;
}

