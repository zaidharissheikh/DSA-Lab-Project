#ifndef GRAPH_H
#define GRAPH_H

#include <string>

// Forward declaration of the UserProfile class to avoid circular dependency
class UserProfile;

class Graph {
private:
    int vertices;  // Number of vertices (users)
    bool** adjMatrix;  // Adjacency matrix (edges between users)
    UserProfile** userProfiles;  // Array to store pointers to user profiles
    std::string* usernames;  // Array of usernames corresponding to vertices
    static int count;  // Counter for the number of users

public:
    Graph(int vertices);  // Constructor to initialize the graph with a given number of vertices
    ~Graph();  // Destructor to free dynamically allocated memory
    void addEdge(int u, int v);  // Adds a directed edge from user u to user v
    void addUserProfile(const std::string& username, UserProfile* user);  // Adds a user profile at a specific vertex
    UserProfile* getUserProfile(const std::string& username);  // Retrieves the UserProfile associated with a username
    void display() const;  // Displays the graph (user profiles and their connections)
    int getUserIndex(const std::string& username);  // Returns the index of a user based on their username
};

#endif  // GRAPH_H
