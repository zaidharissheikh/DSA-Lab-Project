//#include "notifications.h"
//#include <iostream>
//
//void NotificationManager::addNotification(UserProfile* userProfile, const std::string& message) {
//    Notification* newNotification = new Notification{ message };
//    if (!userProfile->notificationsRear) {
//        userProfile->notificationsFront = userProfile->notificationsRear = newNotification;
//    }
//    else {
//        userProfile->notificationsRear->next = newNotification;
//        userProfile->notificationsRear = newNotification;
//    }
//}
//
//void NotificationManager::displayNotifications(UserProfile* userProfile) {
//    Notification* temp = userProfile->notificationsFront;
//    while (temp) {
//        std::cout << "Notification: " << temp->message << std::endl;
//        temp = temp->next;
//    }
//}
