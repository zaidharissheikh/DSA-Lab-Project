#include "Graph.h"
#include <iostream> // Only iostream library is allowed

Graph::Graph(int vertices) : vertices(vertices) {
    adjMatrix = new bool* [vertices];  // Adjacency matrix for storing edges (0 or 1)
    userProfiles = new UserProfile * [vertices];  // Array to store UserProfile pointers
    usernames = new std::string[vertices];  // Array to store usernames
    for (int i = 0; i < vertices; ++i) {
        adjMatrix[i] = new bool[vertices] {false};  // Initialize matrix with false (no edges)
        userProfiles[i] = nullptr;  // Initialize user profile pointers as nullptr
    }
}

Graph::~Graph() {
    for (int i = 0; i < vertices; ++i) {
        delete[] adjMatrix[i];  // Free memory for the rows of the adjacency matrix
    }
    delete[] adjMatrix;
    delete[] usernames;  // Free usernames array
    delete[] userProfiles;  // Free user profiles array
}

int Graph::count = 0;

void Graph::addEdge(int u, int v) {
    if (u >= vertices || v >= vertices) {
        std::cerr << "Invalid vertex index." << std::endl;
        return;
    }
    adjMatrix[u][v] = true;  // Directed edge from u to v
}

void Graph::addUserProfile(const std::string& username, UserProfile* user) {
    if (count >= vertices) {
        std::cerr << "Maximum number of users reached." << std::endl;
        return;
    }
    usernames[count] = username;
    userProfiles[count] = user;  // Store the UserProfile pointer at the corresponding index
    count++;
}

UserProfile* Graph::getUserProfile(const std::string& username) {
    for (int i = 0; i < vertices; ++i) {
        if (usernames[i] == username) {
            return userProfiles[i];  // Return the UserProfile pointer associated with the username
        }
    }
    return nullptr;  // User not found
}

void Graph::display() const {
    for (int i = 0; i < vertices; ++i) {
        if (usernames[i].empty()) continue;  // Skip empty vertices

        std::cout << "User: " << usernames[i] << " (" << i << "):";
        bool hasConnections = false;

        for (int j = 0; j < vertices; ++j) {
            if (adjMatrix[i][j]) {  // Check if there is an edge from vertex i to vertex j
                hasConnections = true;
                std::cout << " -> " << usernames[j];
            }
        }

        if (!hasConnections) {
            std::cout << " No connections";
        }
        std::cout << std::endl;
    }
}

int Graph::getUserIndex(const std::string& username) {
    for (int i = 0; i < vertices; ++i) {
        if (usernames[i] == username) {
            return i;  // Return the index of the user
        }
    }
    return -1;  // Username not found
}
