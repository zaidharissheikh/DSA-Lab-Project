#include "Graph.h"
#include <iostream> // Now include UserProfile.h to use its full definition

Graph::Graph(int vertices) : vertices(vertices) {
    adjMatrix = new UserProfile * [vertices];
    usernames = new std::string[vertices];
    for (int i = 0; i < vertices; ++i) {
        adjMatrix[i] = nullptr;  // Initially no user profile at any vertex
    }
}

Graph::~Graph() {
    for (int i = 0; i < vertices; ++i) {
        delete adjMatrix[i];  // Free memory for UserProfiles
    }
    delete[] adjMatrix;
    delete[] usernames;  // Free usernames array
}

int Graph::count = 0;

void Graph::addEdge(int u, int v) {
    adjMatrix[u] = adjMatrix[v];  // Assuming these are pointers to UserProfile
    adjMatrix[v] = adjMatrix[u];
}

void Graph::addUserProfile(const std::string& username, UserProfile* user) {
    usernames[count] = username;
    adjMatrix[count] = user;
    count++;
}

UserProfile* Graph::getUserProfile(const std::string& username) {
    for (int i = 0; i < vertices; ++i) {
        if (usernames[i] == username) {
            return adjMatrix[i];  // Return the UserProfile associated with the username
        }
    }
    return nullptr;  // User not found
}

void Graph::display() const {
    for (int i = 0; i < vertices; ++i) {
        if (adjMatrix[i]) {
            std::cout << "Vertex " << i << ": " << usernames[i] << std::endl;
        }
    }
}

void Graph::BFS(int start) const {
    // Implement BFS if needed
}

void Graph::DFS(int start) const {
    bool* visited = new bool[vertices]();
    DFSUtil(start, visited);
    delete[] visited;
}

void Graph::DFSUtil(int start, bool* visited) const {
    visited[start] = true;
    std::cout << start << " ";
    for (int i = 0; i < vertices; ++i) {
        if (!visited[i] && adjMatrix[i] != nullptr) {
            DFSUtil(i, visited);
        }
    }
}
