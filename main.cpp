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
void viewFollowerNewsfeed();
void showMessages();
void viewSearchHistory();
void blockFriend();
void unblockFriend();

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

// driver code
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
        "12. Block follower",
        "13. Unblock follower",
        "14. View Newsfeed",
        "15. View Search history",
        "16. View Followers Newsfeed",
        "17. Exit",
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
        system("cls");
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
        case 12: blockFriend(); break;
        case 13: unblockFriend(); break;
        case 14: viewNewsfeed(); break;
        case 15: viewSearchHistory(); break;
        case 16: viewFollowerNewsfeed(); break;
        case 17: return 0;
        default: printColoredText("Invalid choice. Please try again.\n", "31");
        }
        cout << "\n";
    }
}

// main functions for each functionality
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
    if (newUser->addUser(name, password, newUser)) {
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

    // Search for user in user manager 
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
    if (!friendUser)
    {
        printColoredText("User not found.\n", "33");
        return;
    }

    if (friendName == currentUser->name) {
        printColoredText("You cannot send request to yourself.\n", "31");
        return;
    }

    FriendNode* currentFriend = friendUser->friends;

    while (currentFriend )  {
        if (currentFriend->friendName == currentUser->name) {
            printColoredText("Already your friend.\n", "31");
            return;
        }

        currentFriend = currentFriend->next;
    }


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
    if (currentUser->friendRequestQueue.isEmpty()) {
        cout << "No pending requests." << endl;
    }
    else {
        currentUser->friendRequestQueue.display();
        char ch;
        cout << "1. Accept oldest follow request\n2. Reject oldest follow request\n3. Accept All\n4. Reject All\n";
        cin >> ch;
        string fr, noti;
        switch (ch) {
        case '1': {
            fr = currentUser->friendRequestQueue.dequeue();
            currentUser->acceptFriendRequest(fr);
            noti = "Follow request accepted by " + currentUser->name;
            currentUser->searchUser(fr)->addNotification(noti);

            // adding friendship as edges
            int currentIndex = UserProfile::relationshipsGraph->getUserIndex(currentUser->name);
            int friendIndex = UserProfile::relationshipsGraph->getUserIndex(fr);
            if (currentIndex != -1 && friendIndex != -1) {
                UserProfile::relationshipsGraph->addEdge(currentIndex, friendIndex);
            }
            UserProfile::relationshipsGraph->display();
            printColoredText("Request Accepted.\n", "32");
            break;
        }
        case '2': {
            fr = currentUser->friendRequestQueue.dequeue();
            noti = "Follow request rejected by " + currentUser->name;
            currentUser->searchUser(fr)->addNotification(noti);
            printColoredText("Request Rejected.\n", "33");
            break;
        }
        case '3': {
            while (!currentUser->friendRequestQueue.isEmpty()) {
                fr = currentUser->friendRequestQueue.dequeue();
                currentUser->acceptFriendRequest(fr);
                noti = "Follow request accepted by " + currentUser->name;
                currentUser->searchUser(fr)->addNotification(noti);
            }
            printColoredText("Requests Accepted.\n", "32");
            break;
        }
        case '4': {
            while (!currentUser->friendRequestQueue.isEmpty()) {
                fr = currentUser->friendRequestQueue.dequeue();
                noti = "Follow request rejected by " + currentUser->name;
                currentUser->searchUser(fr)->addNotification(noti);
            }
            printColoredText("Requests Rejected.\n", "32");
            break;
        }
        default:
            cout << "Invalid choice." << endl;
        }
    }
}

void addPost() {
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "32");
        return;
    }

    string content;
    cout << "Enter post content: ";
    getline(cin, content);

    // Simulate adding a post
    currentUser->addPost(content);
    printColoredText("Post added successfully.\n", "32");
}

void viewNotifications() {
    if (!currentUser) {
        printColoredText("You need to be logged in to view notifications.\n", "32");
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
    if (recipient == nullptr) {
        printColoredText("User does not exsist.\n", "33");
        return;
    }
    FriendNode* current = currentUser->friends;
    while (current) {
        if (current->friendName == recipientName)
        {
            if (current->status == "blocked")
            {
                printColoredText("User is blocked. Can't send message.\n", "33");
                return;
            }
        }
        current = current->next;
    }
    current = recipient->friends;
    while (current) {
        if (current->friendName == currentUser->name)
        {
            if (current->status == "blocked")
            {

                printColoredText("You are blocked. Can't send message.\n", "33");
                return;
            }
        }
        current = current->next;
    }
    if (recipient) {
        if (recipient->name != currentUser->name)
        {
            currentUser->sendMessage(currentUser->name, recipientName, message);
            recipient->mStack.push(message, currentUser->name, recipientName);
            string noti = "New message from " + currentUser->name;
            recipient->addNotification(noti);
            printColoredText("Message sent to " + recipientName + " from " + currentUser->name + ".\n", "32");
        }
        else
        {
            printColoredText("Can't send message to yourself.\n", "33");
            return;
        }
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
    printColoredText("No friend/follower with such user name found.\n", "33");
}

void searchUsers() {
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "33");
        return;
    }

    string username;
    cout << "Enter username to search: ";
    cin >> username;

    currentUser->searchHistory.insert(username);

    UserProfile* user = currentUser->searchUser(username);
    if (user) {
        printColoredText("User found: " + user->name + " from " + user->city + ".\n", "32");
    }
    else {
        printColoredText("User not found.\n", "31");
    }
}

void viewSearchHistory() {
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "33");
        return;
    }

    currentUser->searchHistory.preorder();
}

void showFollowers() {
    if (!currentUser) {
        printColoredText("You need to be logged in to view followers.\n", "33");
        return;
    }

    // Simulate showing followers
    FriendNode* current = currentUser->friends;
    if (!current)
    {
        printColoredText("No followers.\n", "33");
        return;
    }
    cout << "Followers of " << currentUser->name << ":\n";
    while (current) {
        cout << current->friendName << " (" << current->status << ")\n";
        current = current->next;
    }
}

void blockFriend()

{
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "33");
        return;
    }

    string name;
    cout << "Enter name of follower you want to block: ";
    getline(cin, name);
    FriendNode* current = currentUser->friends;
    if (!current)
    {
        printColoredText("No followers.\n", "33");
        return;
    }
    while (current) {
        if (current->friendName == name)
        {
            if (current->status == "blocked")
            {
                printColoredText("User is already blocked. Itna ghussa?\n", "33");

                return;
            }
            current->status = "blocked";
            printColoredText("User successfully blocked.\n", "33");
            return;
        }
        current = current->next;
    }
    printColoredText("No follower with such username found.\n", "33");
}

void unblockFriend()
{
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "33");
        return;
    }

    string name;
    cout << "Enter name of follower you want to unblock: ";
    getline(cin, name);
    FriendNode* current = currentUser->friends;
    if (!current)
    {

        printColoredText("No followers.\n", "33");
        return;
    }
    while (current) {
        if (current->friendName == name)
        {
            if (current->status == "active")
            {
                printColoredText("User is already unblocked. Aap theek to hain na?\n", "33");
                return;
            }
            current->status = "active";
            printColoredText("User successfully unblocked.\n", "33");
            return;
        }
        current = current->next;
    }
    printColoredText("No follower with such username found.\n", "33");
}

void viewNewsfeed() {
    if (!currentUser) {
        printColoredText("You need to be logged in to view your newsfeed.\n", "33");
        return;
    }
    currentUser->postStack.display();
}

void viewFollowerNewsfeed()
{
    if (!currentUser) {
        printColoredText("You need to be logged in to add posts.\n", "33");
        return;
    }

    string name;
    cout << "Enter name of user you want to view posts of: ";
    getline(cin, name);
    UserProfile* following = currentUser->searchUser(name);
    if (!following)
    {
        printColoredText("No followers.\n", "33");
        return;
    }
    FriendNode* current = following->friends;
    while (current) {
        if (current->friendName == currentUser->name)
        {
            if (current->status != "blocked")
            {
                following->postStack.display();
                return;
            }
            else
            {
                printColoredText("You are blocked by this user.\n", "32");
                return;
            }
        }
        current = current->next;
    }
    printColoredText("You are not following that user. Follow them to view their posts.\n", "32");
}