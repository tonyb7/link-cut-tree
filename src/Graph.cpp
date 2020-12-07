
#include "Graph.h"

#include <iostream>
#include <queue>

#include <cassert>

using std::cin;
using std::cout; using std::endl;
using std::queue;
using std::unordered_map;
using std::vector;
using std::shared_ptr; using std::make_shared;

void Graph::addEdge(int u, int v, int capacity)
{
    int forward_edge_index = edges.size();
    int reverse_edge_index = edges.size() + 1;

    Edge forward { u, v, 0, capacity, capacity, reverse_edge_index };
    Edge reverse { v, u, 0,        0,        0, forward_edge_index };

    edges.push_back(forward);
    edges.push_back(reverse);

    adj[u].push_back(forward_edge_index);
    adj[v].push_back(reverse_edge_index);
}

void Graph::generateLevelGraph() 
{
    assert(vertex_to_level_node.empty());

    shared_ptr<LevelGraphNode> s = make_shared<LevelGraphNode>();
    s->level = 0;
    vertex_to_level_node[source] = s;

    queue<int> bfs_q;
    bfs_q.push(source);

    while (!bfs_q.empty()) {
        int current_vertex = bfs_q.front();
        bfs_q.pop();

        auto level_it = vertex_to_level_node.find(current_vertex);
        assert(level_it != vertex_to_level_node.end());

        shared_ptr<LevelGraphNode> current_node = level_it->second;

        vector<int> outgoing_edges = adj[current_vertex];
        for (int e : outgoing_edges) {

            Edge outgoing_edge = edges[e];
            if (outgoing_edge.residual == 0) {
                // edge isn't in residual graph, so edge won't be in level graph
                continue;
            }

            int next_vertex = outgoing_edge.v;
            shared_ptr<LevelGraphNode>& v = vertex_to_level_node[next_vertex];
            
            if (v) {
                // already visited
                continue;
            }
            else {
                v = make_shared<LevelGraphNode>();
                v->level = current_node->level + 1;

                current_node->outgoing_edges.push_back(next_vertex);
                bfs_q.push(next_vertex);
            }

        }
    }

}

void Graph::printLevelGraph() {
    
    int level = 0;

    queue<int> bfs_q;
    bfs_q.push(source);

    cout << "Printing the Level Graph: " << endl;
    while (!bfs_q.empty()) {
        int curr = bfs_q.front();
        bfs_q.pop();

        shared_ptr<LevelGraphNode> v = vertex_to_level_node[curr];
        if (v->level > level) {
            level = v->level;
            cout << endl;
        }

        cout << curr << " ";

        for (int e : v->outgoing_edges) {
            bfs_q.push(e);
        }
    }
    cout << endl;

    if (vertex_to_level_node.count(target)) {
        cout << "The target node (" << target << ") is in the level graph" << endl;
    }
    else {
        cout << "The target node (" << target << ") is not in the level graph" << endl;
    }

}

