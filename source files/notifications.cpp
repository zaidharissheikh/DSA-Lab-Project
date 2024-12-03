#include "Notifications.h"
#include <iostream>
using namespace std;

Notifications::Notifications() : front(nullptr), rear(nullptr) {}

Notifications::~Notifications() {
    while (front) {
        NotificationNode* temp = front;
        front = front->next;
        delete temp;
    }
}

void Notifications::addNotification(const std::string& message) {
    NotificationNode* newNode = new NotificationNode(message);
    if (isEmpty()) {
        front = rear = newNode;
    }
    else {
        rear->next = newNode;
        rear = newNode;
    }
   /* cout << "Notification added: " << message << endl;*/
}

string Notifications::getNotification() {
    if (!front) {
        cout << "No notifications available." << endl;
        return "";
    }

    NotificationNode* temp = front;
    std::string message = front->message;
    front = front->next;
    if (!front) {
        rear = nullptr; 
    }
    delete temp;
    return message;
}

void Notifications::clearNotifications()
{
    while (!isEmpty())
    {
        getNotification();
    }
}

void Notifications::displayNotifications() const {
    if (isEmpty()) {
        cout << "No notifications available." << endl;
        return;
    }

    cout << "Notifications:" << endl;
    NotificationNode* temp = front;
    while (temp) {
        cout << "- " << temp->message << endl;
        temp = temp->next;
    }
}

bool Notifications::isEmpty() const {
    return front == nullptr;
}