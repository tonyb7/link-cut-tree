
#pragma once

#include <unordered_map>
#include <vector>
#include <memory>

class Graph {
public:
    /* 
        Initialize the number of vertices, and source and target vertex indices 
    */
    Graph(int vertices_) : vertices(vertices_), source(0), target(vertices_ - 1) 
    {}

    /* 
        Adds an edge from u to v with the given capacity. 
        Adds a reverse edge from v to u with capacity 0. 
    */
    void addEdge(int u, int v, int capacity);

    /* 
        Creates level graph representation of the current graph from scratch.
        Edge tracks its residual capacity so all the information needed for 
        generating the level graph exists already. 
    */
    void generateLevelGraph();
    void printLevelGraph();

private:
    int vertices;
    int source;
    int target;

    struct Edge {
        // edge directed from u to v
        int u; 
        int v;
        // flow values
        int flow;
        int capacity;
        int residual; // = capacity - flow
        // index of reverse edge in the Edges array
        int reverse;
    };
    std::vector<Edge> edges;

    // vertex number -> edge index of outgoing edges
    std::unordered_map<int, std::vector<int>> adj; 

    // Link-cut tree node
    struct TreeNode {
        TreeNode() : parent(nullptr), left(nullptr), right(nullptr), pathparent(nullptr) 
        {}
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        TreeNode* pathparent;
    };
    
    // Level graph representation
    struct LevelGraphNode {
        int level;
        std::vector<int> outgoing_edges;
        TreeNode node;
    };
    std::unordered_map<int, std::shared_ptr<LevelGraphNode>> vertex_to_level_node;

};

