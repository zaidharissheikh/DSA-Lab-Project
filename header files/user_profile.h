#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <string>
#include <ctime>
#include "Stack.h"
#include "LinkedList.h"
#include "Graph.h"
#include "Queue.h"
#include "Hash.h"
#include "BST.h"
#include "friendRequestQueue.h"
#include "notifications.h"
#include "messageStack.h"

using namespace std;

// Struct for Friend Node to store friend details and status
struct FriendNode {
    string friendName;
    string status; // "active", "blocked", "pending"
    FriendNode* next;

    FriendNode(const string& name, const string& status)
        : friendName(name), status(status), next(nullptr) {}
};

// Struct for Message Node to store message details
struct MessageNode {
    string sender;
    string content;
    MessageNode* next;

    MessageNode(const string& sender, const string& content)
        : sender(sender), content(content), next(nullptr) {}
};

// Struct for Post to represent user posts
struct Post {
    string content;
    time_t timestamp;
    Post* next;

    Post() {}
    Post(const string& content)
        : content(content), timestamp(time(nullptr)), next(nullptr) {}
};


class UserProfile {
public:
    string name;
    string password;
    string city;
    time_t lastLogin;
    FriendNode* friends;
    MessageNode* messages;
    Post* posts;
    UserProfile* next;

    Stack postStack;
    Stack followerPostStack;
    messageStack mStack;
    FriendRequestQueue friendRequestQueue;
    Notifications notificationQueue;

    // Static references to global Graph and HashTable (shared across all users)
    static Graph* relationshipsGraph;
    static HashTable* loginHashTable;
    static BST* userBST;

    UserProfile();
    ~UserProfile();

    void addPost(const string& content);
    void addFriendRequest(const string& sender);
    void sendMessage(const string& sender, const string& receiver, const string& message);
    void addNotification(const string& message);
    void acceptFriendRequest(const string& sender);
    bool login(const string& username, const string& password);
    void displayNotifications();
    void displayPosts();
    UserProfile* searchUser(const string& username);
    bool addUser(const string& username, const string& password);
    bool isPasswordStrong(const string& password);
};

#endif // USER_PROFILE_H
