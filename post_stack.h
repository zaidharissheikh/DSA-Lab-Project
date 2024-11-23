#pragma once
#ifndef POSTS_STACK_H
#define POSTS_STACK_H
#include <iostream>
#include <string>
using namespace std;

class Post {
public:
    string dateTime; 
    string content;   
    Post(const string& dateTime = "", const string& content = "") : dateTime(dateTime), content(content) {}

    void display() 
    {
        cout << "[" << dateTime << "] " << content << endl;
    }
};

struct PostNode {
    Post data;
    PostNode* next;
    PostNode(const Post& post, PostNode* nextNode = NULL) : data(post), next(nextNode) {}
};

class PostsStack {
    PostNode* top_ptr; 
    int count;         //number of posts in the stack

public:
    PostsStack() : top_ptr(NULL), count(0) {}

    ~PostsStack() {
        clear();
    }

    void push(const Post& post) 
    {
        PostNode* newNode = new PostNode(post, top_ptr);
        top_ptr = newNode;
        ++count;
    }

    void pop() 
    {
        if (empty()) {
            cout << "No posts to delete." << endl;
            return;
        }
        PostNode* temp = top_ptr;
        top_ptr = top_ptr->next;
        delete temp;
        --count;
    }

    Post top() const {
        if (empty()) {
            cout << "No posts to show." << endl;
            return Post("", "");
        }
        return top_ptr->data;
    }

    bool empty() const {
        return top_ptr == NULL;
    }

    int size() const {
        return count;
    }

    void display()
    {
        if (empty()) {
            cout << "No posts to display." << endl;
            return;
        }
        PostNode* current = top_ptr;
        cout << "Posts history (most recent first):" << endl;
        while (current != NULL)
        {
            current->data.display();
            current = current->next;
        }
    }
    void clear() 
    {
        while (!empty()) {
            pop();
        }
    }
};
#endif 
