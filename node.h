#pragma once
#ifndef NODE_H
#define NODE_H
#include "post_stack.h"
#include <iostream>
using namespace std;

class Node {
private:
    PostsStack posts; //stack to hold posts
    int postCount;       //number of posts
   
public:
    string name;         
    string password;     
    string city;         
    string lastLogin;    

    Node(const string& name, const string& password, const string& city, const string& lastLogin) : name(name), password(password), city(city), lastLogin(lastLogin), postCount(0) 
    {}

    ~Node() { }

    void addPost(const string& dateTime, const string& content) 
    {
        posts.push(Post(dateTime, content));
    }

    void displayUserInfo()  
    {
        cout << "Name: " << name << endl;
        cout << "City: " << city << endl;
        cout << "Last Login: " << lastLogin << endl;
        cout << "Posts: " << endl;
        posts.display();
    }
};
#endif