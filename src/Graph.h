
#pragma once

#include "LinkCutTree.h"

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
        
        Returns a boolean specifying whether a path to the target was found.
    */
    bool generateLevelGraph();

    /* 
        Reset the level graph to prepare for the next iteration.
    */
    void resetLevelGraph()
    {vertex_to_level_node.clear();}

    /* 
        Find a blocking flow in the level graph using the link-cut tree implementation.
        Add the blocking flow to the graph's total flow.
    */
    void addBlockingFlow();

    /*
        Functions to print the state of Graph. 
    */
    void printLevelGraph() const;
    void printFlow() const;

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
    
    // Level graph representation
    struct LevelGraphNode {
        int level;
        std::vector<int> outgoing_edges;
        LinkCutTree::TreeNode node;
    };
    std::unordered_map<int, std::shared_ptr<LevelGraphNode>> vertex_to_level_node;

};

