#pragma once
#ifndef MESSAGING_QUEUE_H
#define MESSAGING_QUEUE_H
#include "queue.h"

class messaging_queue {
	Queue m_queue;
public:
    void sendMessage(const string& sender, const string& receiver, const string& message)
    {
        string fullMsg = "[" + sender + " to " + receiver + "]: " + message;
        m_queue.enqueue(fullMsg);
        cout << "Message sent successfully!" << endl;
    }

    void viewMessages() 
    {
        cout << "Messages:" << endl;
        m_queue.print();
    }
    //this function will be invoked when user opens their inbox
    void clearMessages()
    {
        while (!m_queue.empty()) {
            m_queue.dequeue();
        }
    }
};

#endif
