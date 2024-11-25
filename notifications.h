#pragma once
#ifndef NOTIFICATIONS_H
#define NOTIFICATIONS_H
#include "queue.h"

class notifications {
	Queue notis;
public:
    void addNoti(const string& notification)
    {
        notis.enqueue(notification);
    }

    void viewNotis()
    {
        cout << "Notifications:" << endl;
        notis.print();
    }
    //this function will be invoked after the user has seen their notifications
    void clearNotifis() 
    {
        while (!notis.empty()) {
            notis.dequeue();
        }
    }
};
#endif
