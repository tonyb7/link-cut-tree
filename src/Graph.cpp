
#include "Graph.h"

#include <iostream>
#include <queue>

#include <cassert>

using std::cin;
using std::cout; using std::endl;
using std::queue;
using std::unordered_map;
using std::unordered_set;
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

    adj[u][v] = forward_edge_index;
    adj[v][u] = reverse_edge_index;
}

bool Graph::generateLevelGraph() 
{
    assert(vertex_to_level_node.empty());

    shared_ptr<LevelGraphNode> s = make_shared<LevelGraphNode>(0, source);
    vertex_to_level_node[source] = s;

    queue<int> bfs_q;
    bfs_q.push(source);

    while (!bfs_q.empty()) {
        int current_vertex = bfs_q.front();
        bfs_q.pop();

        auto level_it = vertex_to_level_node.find(current_vertex);
        assert(level_it != vertex_to_level_node.end());

        shared_ptr<LevelGraphNode> current_node = level_it->second;

        unordered_map<int, int> outgoing_edges = adj[current_vertex];
        for (auto e_it = outgoing_edges.begin(); e_it != outgoing_edges.end(); ++e_it) {
            
            Edge outgoing_edge = edges[e_it->second];
            if (outgoing_edge.residual == 0) {
                // edge isn't in residual graph, so edge won't be in level graph
                continue;
            }

            int next_vertex = outgoing_edge.v;
            shared_ptr<LevelGraphNode>& v = vertex_to_level_node[next_vertex];
            
            if (v) {
                // already visited
                if (v->level == current_node->level + 1) {
                    current_node->outgoing_vertices.insert(v->node.vertex);
                    v->incoming_vertices.insert(current_vertex);
                }
                continue;
            }
            else {
                v = make_shared<LevelGraphNode>(current_node->level + 1, next_vertex);
                v->incoming_vertices.insert(current_vertex);

                current_node->outgoing_vertices.insert(next_vertex);
                bfs_q.push(next_vertex);
            }

        }
    }

    return vertex_to_level_node.count(target);
}

void Graph::addBlockingFlow() 
{
    using LinkCutTree::TreeNode;

    TreeNode s = vertex_to_level_node[source]->node;

    while (true) {
        TreeNode* r = LinkCutTree::root(&s);

        if (r->vertex == target) {
            // found a path from source to target
            bool firstTime = true;
            while (true) {
                TreeNode * w = LinkCutTree::mincost(&s); // find the mincost along this path

                assert(w->parent);
                int edge_idx = adj.at(w->vertex).at(w->parent->vertex);
                const Edge& e = edges.at(edge_idx);
                int cost = e.residual;

                if (firstTime) {
                    firstTime = false;
                    LinkCutTree::update(&s, 0 - cost); // add mincost to blocking flow
                    cost = 0;
                }

                if (cost != 0) {
                    assert(cost > 0);
                    break;
                }
                else {
                    // delete all edges that acquired cost==0
                    LinkCutTree::cut(w);
                    vertex_to_level_node[e.u]->outgoing_vertices.erase(e.v);
                    vertex_to_level_node[e.v]->incoming_vertices.erase(e.u);
                }
            }
        }
        else {
            shared_ptr<LevelGraphNode> rnode = vertex_to_level_node.at(r->vertex);
            if (rnode->outgoing_vertices.empty()) {
                if (r->vertex == source) {
                    // a blocking flow has been found
                    break;
                }
                else {
                    // dead end; cut all incoming edges
                    for (int u : rnode->incoming_vertices) {
                        shared_ptr<LevelGraphNode> prev_node = vertex_to_level_node.at(u);

                        LinkCutTree::cut(&prev_node->node);
                        prev_node->outgoing_vertices.erase(r->vertex);
                    }
                    rnode->incoming_vertices.clear();
                }
            }
            else {
                // There exists an outgoing edge, so select one and link it
                int outgoing_vertex = *rnode->outgoing_vertices.begin();
                const Edge& e = edges.at(adj.at(r->vertex).at(outgoing_vertex));
                TreeNode outgoing_node = vertex_to_level_node.at(outgoing_vertex)->node;
                
                LinkCutTree::link(r, &outgoing_node, e.residual);
            }
        }

    }

}

void Graph::printLevelGraph() const
{
    int level = 0;

    queue<int> bfs_q;
    bfs_q.push(source);

    cout << "Printing the Level Graph: " << endl;
    unordered_set<int> seen;

    while (!bfs_q.empty()) {
        int curr = bfs_q.front();
        bfs_q.pop();

        shared_ptr<LevelGraphNode> v = vertex_to_level_node.at(curr);
        if (v->level > level) {
            level = v->level;
            cout << endl;
        }

        // Returns pair (iter, whether insertion happened)
        auto s_pair = seen.emplace(curr);
        if (s_pair.second) {
            cout << curr << " ";
        }

        for (int e : v->outgoing_vertices) {
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
    cout << endl;

}

void Graph::printFlow() const
{
    int flow = 0;
    unordered_map<int, int> source_edges = adj.at(source);
    for (auto e_it = source_edges.begin(); e_it != source_edges.end(); ++e_it) {
        flow += edges.at(e_it->second).flow;
    }

    cout << "Total Flow: " << flow << endl;

    for (const Edge& edge : edges) {
        cout << "The edge from " << edge.u 
             << " to "           << edge.v 
             << " has "          << edge.flow  << "/" << edge.capacity 
             << " units of flow" << endl;
    }
    cout << endl;
}

