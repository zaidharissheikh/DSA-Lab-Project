#ifndef GRAPH_H
#define GRAPH_H

#include <string>

// Forward declaration of the UserProfile class to avoid circular dependency
class UserProfile;

class Graph {
private:
    int vertices;  // Number of vertices
    UserProfile** adjMatrix;  // Adjacency matrix holding UserProfile pointers
    std::string* usernames;  // Array of usernames corresponding to vertices
    static int count;

public:
    Graph(int vertices);  // Constructor
    ~Graph();  // Destructor to free dynamically allocated memory
    void addEdge(int u, int v);  // Adds an undirected edge between u and v
    void addUserProfile(const std::string& username, UserProfile* user);  // Add user profile at a username
    UserProfile* getUserProfile(const std::string& username);  // Retrieve user profile by username
    void display() const;  // Displays the graph (for debugging)
    void BFS(int start) const;  // Breadth-First Search starting from vertex `start`
    void DFS(int start) const;  // Depth-First Search starting from vertex `start`

    // Helper function for DFS to handle recursion
    void DFSUtil(int start, bool* visited) const;
};

#endif
