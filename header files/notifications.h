#pragma once
#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H

#include <string>

struct NotificationNode {
    std::string message;   // Notification message
    NotificationNode* next; 

    explicit NotificationNode(const std::string& msg) : message(msg), next(nullptr) {}
};


class Notifications {
private:
    NotificationNode* front; 
    NotificationNode* rear;  

public:
    Notifications();
    ~Notifications();
    void addNotification(const std::string& message);
    std::string getNotification();
    void displayNotifications() const;
    bool isEmpty() const;
    void clearNotifications();
};

#endif 

