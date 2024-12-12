#include "user_profile.h"
#include <iostream>

// Initialize the static members (one shared instance for all users)
Graph* UserProfile::relationshipsGraph = new Graph(100);  // Example size for graph
HashTable* UserProfile::loginHashTable = new HashTable(100);  // Example size for hash table
BST* UserProfile::userBST = new BST();  // Create an empty BST for username search

// Constructor to initialize the UserProfile
UserProfile::UserProfile() {
    name = "";
    password = "";
    city = "";
    lastLogin = time(nullptr);  // Initialize with current time
    friends = nullptr;
    messages = nullptr;
    //posts = nullptr;
    next = nullptr;

}

// Destructor to clean up dynamically allocated memory
UserProfile::~UserProfile() {
    // Clean up the linked list of friends, messages, posts, etc.
    delete relationshipsGraph;
    delete loginHashTable;
    delete userBST;

    // Free up memory for linked lists
    while (friends != nullptr) {
        FriendNode* temp = friends;
        friends = friends->next;
        delete temp;
    }

    while (messages != nullptr) {
        MessageNode* temp = messages;
        messages = messages->next;
        delete temp;
    }

 /*   while (posts != nullptr) {
        Post* temp = posts;
        posts = posts->next;
        delete temp;
    }*/
}

// Function to add a post to the user's post stack
void UserProfile::addPost(const string& content) {
    // Add to the stack for newsfeed or posts stack (if needed)
    postStack.push(content, time(nullptr)); 
}

// Function to add a friend request
void UserProfile::addFriendRequest(const string& sender) {

    friendRequestQueue.enqueue(sender);  
}

// Function to send a message to a friend
void UserProfile::sendMessage(const string& sender ,const string& receiver, const string& message) {
    mStack.push(message, sender ,receiver);
}

// Function to add a notification
void UserProfile::addNotification(const string& message) {

    notificationQueue.addNotification(message);
}

// Function to accept a friend request
void UserProfile::acceptFriendRequest(const string& sender) {
    FriendNode* newF = new FriendNode(sender, "active");
    if (!friends)
    {
        friends = newF;
    }
    else
    {
        newF->next = friends;
        friends = newF;
    }
}

// Function to process login (check username and password)
bool UserProfile::login(const string& username, const string& password) {
    string storedPassword = loginHashTable->search(username);
    return (storedPassword == password);  // Return true if passwords match
}

// Function to display notifications
void UserProfile::displayNotifications() {

    notificationQueue.displayNotifications();
    notificationQueue.clearNotifications();
}



UserProfile* UserProfile::searchUser(const string& username) {
    // First, search for the user in the Graph
    UserProfile* userProfile = relationshipsGraph->getUserProfile(username);
    if (userProfile) {

        return userProfile;  // User found in the Graph
    }

    // If not found in the BST, check in the HashTable using the username as the key
    string password = loginHashTable->search(username);  // Retrieve the password (if found) from HashTable
    if (!password.empty()) {
        return new UserProfile();  // Create a new profile for the user from HashTable (useful if no profile exists)
    }

    return nullptr;  // User not found in Graph, BST, or HashTable
}

// Function to add a user to the hash 
bool UserProfile::addUser(const string& username, const string& password, UserProfile* user) {
    // Check if the username already exists in the hash table
    if (loginHashTable->search(username) != "") {
        std::cout << "Username " << username << " is already taken." << std::endl;
        return false;  // Username is already taken
    }

    UserProfile* newUser = user;

    // Insert the new user into the global hash table and BST
    if (loginHashTable->insert(username, password) && userBST->insert(username)) {
        std::cout << "User " << username << " added successfully." << std::endl;

        // Add the user to the global graph by directly using their username
        relationshipsGraph->addUserProfile(username, newUser);  // Associate username with UserProfile in the graph

        return true;  // User added successfully
    }
    else {
        std::cout << "Failed to add user " << username << "." << std::endl;
        delete newUser;  // Clean up the dynamically allocated memory
        return false;  // Insertion failed
    }
}

bool UserProfile::isPasswordStrong(const string& password) {
    if (password.length() < 8) {
        return false;  // Password must be at least 8 characters long
    }

    bool hasLetter = false;
    bool hasDigit = false;
    bool hasSpecialChar = false;
    const string specialChars = "@$!%*?&";

    // Using a for loop with 3 arguments (index, condition, increment)
    for (int i = 0; i < password.length(); ++i) {
        char ch = password[i];
        if (isalpha(ch)) {
            hasLetter = true;  // Checks if character is a letter (A-Z or a-z)
        }
        else if (isdigit(ch)) {
            hasDigit = true;   // Checks if character is a digit (0-9)
        }
        else if (specialChars.find(ch) != string::npos) {
            hasSpecialChar = true;  // Checks if character is a special character from the allowed set
        }
    }

    // Ensure the password contains at least one letter, one digit, and one special character
    return hasLetter && hasDigit && hasSpecialChar;
}