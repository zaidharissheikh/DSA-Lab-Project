//#include <iostream>
//#include "user_profile.h"
//
//using namespace std;
//void PostManager::addPost(Post*& head, const string& content) {
//    Post* newPost = new Post(content);
//    newPost->next = head;
//    head = newPost;
//}
//
//void PostManager::displayPosts(Post* head) {
//    Post* current = head;
//    char buffer[26];
//    while (current != nullptr) {
//        cout << "Post: " << current->content
//            << " (Timestamp: " << ctime_s(buffer, sizeof(buffer), &current->timestamp) << ")" << endl;
//        current = current->next;
//    }
//}
