#include <iostream>
#include "user_profile.h"

using namespace std;

// Managers and global variables
UserProfile* currentUser = nullptr;
UserProfile* friendUser = nullptr;

void signup();
void login();
void logout();
void sendFollowRequest();
void processFollowRequests();
void addPost();
void viewNotifications();
void sendMessage();
void searchUsers();
void showFollowers();
void viewNewsfeed();
void showMessages();

// Utility Functions
void printColoredText(const string& text, const string& colorCode) {
    cout << "\033[" << colorCode << "m" << text << "\033[0m";
}

void printBox(const string& title, const string menu[]) {
    printColoredText("+--------------------------------+\n", "35");
    printColoredText("| " + title + string(30 - title.length(), ' ') + " |\n", "35");
    printColoredText("+--------------------------------+\n", "35");
    for (int i = 0; menu[i] != ""; ++i) {
        printColoredText("| " + menu[i] + string(30 - menu[i].length(), ' ') + " |\n", "35");
    }
    printColoredText("+--------------------------------+\n", "35");
}


int main() {
    string welcomeMessage = "Welcome to Mini Instagram!";
    string menu[] = {
        "1. Signup",
        "2. Login",
        "3. Logout",
        "4. Send Follow Request",
        "5. Process Follow Requests",
        "6. Add Post",
        "7. View Notifications",
        "8. Send Message",
        "9. Show Messages",
        "10. Search Users",
        "11. Show Followers",
        "12. View Newsfeed",
        "13. Exit",
        ""
    };

    int choice;
    while (true) {
        printColoredText("\n", "0");
        printBox(welcomeMessage, menu);
        printColoredText("\nEnter your choice: ", "37");
        cin >> choice;

        if (cin.fail()) {
            cin.clear(); // Clear the error flag
            char discard;
            while (cin.get(discard) && discard != '\n'); // Discard invalid input
            printColoredText("Invalid input. Please enter an integer.\n", "31");
            continue;
        }
        cin.ignore();
        switch (choice) {
        case 1: signup(); break;
        case 2: login(); break;
        case 3: logout(); break;
        case 4: sendFollowRequest(); break;
        case 5: processFollowRequests(); break;
        case 6: addPost(); break;
        case 7: viewNotifications(); break;
        case 8: sendMessage(); break;
        case 9: showMessages(); break;
        case 10: searchUsers(); break;
        case 11: showFollowers(); break;
        case 12: viewNewsfeed(); break;
        case 13: return 0;
        default: printColoredText("Invalid choice. Please try again.\n", "31");
        }
        cout << "\n";
    }
}

void signup() {
    string name, password, city;
    cout << "Enter username: ";
    cin >> name;

    // Check if username already exists
    if (currentUser->searchUser(name) != nullptr) {
        printColoredText("Username already exists. Please try again.\n", "31");
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Check password strength
    if (!currentUser->isPasswordStrong(password)) {
        printColoredText("Password is not strong enough. It should have at least 8 characters, 1 letter, 1 number, and 1 special character.\n", "31");
        return;
    }

    cout << "Enter city: ";
    cin >> city;

    // Create new user profile
    UserProfile* newUser = new UserProfile();
    newUser->name = name;
    newUser->password = password;
    newUser->city = city;

    // Add user to user manager (hash table or similar structure)
    if (newUser->addUser(name, password)) {
        currentUser = newUser;
        printColoredText("User signed up successfully: " + name + "\n", "32");
    }
    else {
        delete newUser;
    }
}

void login() {
    if (currentUser) {
        printColoredText("You are already logged in.\n", "33");
        return;
    }

    string username, password;
    cout << "Enter username: ";
    getline(cin, username);
    cout << "Enter password: ";
    cin >> password;

    // Search for user in user manager (HashTable)
    UserProfile* user = currentUser->searchUser(username);

    if (user && user->login(username, password)) {
        currentUser = user;
        printColoredText("Login successful! Welcome, " + username + ".\n", "32");
    }
    else {
        printColoredText("Invalid username or password!\n", "31");
    }
}

void logout() {
    if (currentUser) {
        currentUser = nullptr;
        printColoredText("Logged out successfully.\n", "32");
    }
    else {
        printColoredText("No user is currently logged in.\n", "31");
    }
}

void sendFollowRequest() {
    if (!currentUser) {
        printColoredText("You need to be logged in to send follow requests.\n", "33");
        return;
    }

    string friendName;
    cout << "Enter username to follow: ";
    getline(cin, friendName);

    friendUser = currentUser->searchUser(friendName);
    if (friendUser) {
        friendUser->addFriendRequest(currentUser->name);
        string noti = currentUser->name + " sent you a friend request.";
        friendUser->addNotification(noti);
        printColoredText("Follow request sent to " + friendName + ".\n", "32");
    }
    else {
        printColoredText("User not found.\n", "31");
    }
}

void processFollowRequests() {
    if (!currentUser) {
        printColoredText("You need to be logged in to process follow requests.\n", "33");
        return;
    }
    if (currentUser->friendRequestQueue.isEmpty())
    {
        cout << "No pending requests." << endl;
    }
    else
    {
        currentUser->friendRequestQueue.display();
        char ch;
        cout << "1. Accept oldest follow request\n2. Reject oldest follow request\n3. Accept All\n4. Reject All\n";
        cin >> ch;
        string fr, noti;
        switch (ch)
        {
        case '1':
            fr = currentUser->friendRequestQueue.dequeue();
            currentUser->acceptFriendRequest(fr);
            noti = "Follow requested accepted by " + currentUser->name;
            currentUser->searchUser(fr)->addNotification(noti);
            printColoredText("Request Accepted.\n", "32");
            break;
        case '2':
            fr = currentUser->friendRequestQueue.dequeue();
            noti = "Follow requested rejected by " + currentUser->name;
            currentUser->searchUser(fr)->addNotification(noti);
            printColoredText("Request Rejected.\n", "33");
            break;
        case '3':
            while (!currentUser->friendRequestQueue.isEmpty())
            {
                fr = currentUser->friendRequestQueue.dequeue();
                currentUser->acceptFriendRequest(fr);
                noti = "Follow requested accepted by " + currentUser->name;
                currentUser->searchUser(fr)->addNotification(noti);
            }
            printColoredText("Requests Accepted.\n", "32");
            break;
        case '4':
            while (!currentUser->friendRequestQueue.isEmpty())
            {
                fr = currentUser->friendRequestQueue.dequeue();
                noti = "Follow requested rejected by " + currentUser->name;
                currentUser->searchUser(fr)->addNotification(noti);
            }
            printColoredText("Requests Rejected.\n", "32");
            break;
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

void addPost() {
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "33");
        return;
    }

    string content;
    cout << "Enter post content: ";
    cin.ignore();
    getline(cin, content);

    // Simulate adding a post
    currentUser->addPost(content);
    printColoredText("Post added successfully.\n", "32");
}

void viewNotifications() {
    if (!currentUser) {
        printColoredText("You need to be logged in to view notifications.\n", "31");
        return;
    }
    currentUser->displayNotifications();
}

void sendMessage() {
    if (!currentUser) {
        printColoredText("You need to be logged in to send messages.\n", "33");
        return;
    }

    string recipientName, message;
    cout << "Enter recipient username: ";
    cin >> recipientName;
    cout << "Enter message: ";
    cin.ignore();
    getline(cin, message);

    UserProfile* recipient = currentUser->searchUser(recipientName);
    if (recipient) {
        currentUser->sendMessage(currentUser->name, recipientName, message);
        recipient->mStack.push(message, currentUser->name, recipientName);
        string noti = "New message from " + currentUser->name;
        recipient->addNotification(noti);
        printColoredText("Message sent to " + recipientName + " from " + currentUser->name + ".\n", "32");
    }
    else {
        printColoredText("User not found.\n", "31");
    }
}

void showMessages()
{
    if (!currentUser) {
        printColoredText("You need to be logged in to view messages.\n", "33");
        return;
    }
    cout << "Enter username of which you want to open the chat: ";
    string name;
    getline(cin, name);
    UserProfile* frand = currentUser->searchUser(name);
    if (frand && frand->name != currentUser->name)
    {
        currentUser->mStack.printMsgs(currentUser->name, name);
        return;
    }
    cout << "No friend with such user name found." << endl;
}

void searchUsers() {
    string username;
    cout << "Enter username to search: ";
    cin >> username;

    UserProfile* user = currentUser->searchUser(username);
    if (user) {
        printColoredText("User found: " + user->name + " from " + user->city + ".\n", "32");
    }
    else {
        printColoredText("User not found.\n", "31");
    }
}

void showFollowers() {
    if (!currentUser) {
        printColoredText("You need to be logged in to view followers.\n", "33");
        return;
    }

    // Simulate showing followers
    FriendNode* current = currentUser->friends;
    cout << "Followers of " << currentUser->name << ":\n";
    while (current) {
        cout << current->friendName << " (" << current->status << ")\n";
        current = current->next;
    }
}

void viewNewsfeed() {
    if (!currentUser) {
        printColoredText("You need to be logged in to view your newsfeed.\n", "33");
        return;
    }

    // Simulate viewing newsfeed
    Post* current = currentUser->posts;
    cout << "Posts by " << currentUser->name << ":\n";
    while (current) {
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &current->timestamp);
        cout << current->content << " at " << buffer;
        current = current->next;
    }
}
