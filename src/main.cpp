
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <queue>

#include <cassert>

using std::cin;
using std::cout; using std::endl;
using std::unordered_map;
using std::vector;
using std::shared_ptr; using std::make_shared;
using std::queue;


struct Edge {
    // edge directed from u to v
    int u; 
    int v;

    int flow;
    int capacity;
    int residual; // = capacity - flow

    // index of reverse edge in the Edges array
    int reverse;
};

class Graph {
public:
    Graph(int vertices_) : vertices(vertices_), source(0), target(vertices_ - 1) 
    {}

    /* 
        Adds an edge from u to v with the given capacity. 
        Adds a reverse edge from v to u with capacity 0. 
    */
    void addEdge(int u, int v, int capacity)
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

    void generateLevelGraph() 
    {
        assert(vertex_to_level.empty());

        shared_ptr<LevelGraphNode> s = make_shared<LevelGraphNode>();
        s->level = 0;
        vertex_to_level[source] = s;

        queue<int> bfs_q;
        bfs_q.push(source);

        while (!bfs_q.empty()) {
            int current_vertex = bfs_q.front();
            bfs_q.pop();

            auto level_it = vertex_to_level.find(current_vertex);
            assert(level_it != vertex_to_level.end());

            shared_ptr<LevelGraphNode> current_node = level_it->second;

            vector<int> outgoing_edges = adj[current_vertex];
            for (int e : outgoing_edges) {

                Edge outgoing_edge = edges[e];
                if (outgoing_edge.residual == 0) {
                    // edge isn't in residual graph, so edge won't be in level graph
                    continue;
                }

                int next_vertex = outgoing_edge.v;
                shared_ptr<LevelGraphNode>& v = vertex_to_level[next_vertex];
                
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

    void printLevelGraph() {
        
        int level = 0;

        queue<int> bfs_q;
        bfs_q.push(source);

        cout << "Printing the Level Graph: " << endl;
        while (!bfs_q.empty()) {
            int curr = bfs_q.front();
            bfs_q.pop();

            shared_ptr<LevelGraphNode> v = vertex_to_level[curr];
            if (v->level > level) {
                level = v->level;
                cout << endl;
            }

            cout << curr << " ";

            for (int e : v->outgoing_edges) {
                bfs_q.push(e);
            }
        }

    }

private:
    int vertices;
    int source;
    int target;
    vector<Edge> edges;

    // vertex number -> edge index of outgoing edges
    unordered_map<int, vector<int>> adj; 

    // Link-cut tree node
    struct TreeNode {
        TreeNode() : parent(nullptr), left(nullptr), right(nullptr), pathparent(nullptr) 
        {}

        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        TreeNode* pathparent;
    };

    // Level graph stuff
    struct LevelGraphNode {
        int level;
        vector<int> outgoing_edges;
        TreeNode node;
    };
    unordered_map<int, shared_ptr<LevelGraphNode>> vertex_to_level;

};

int main()
{
    int num_vertices;
    cin >> num_vertices;

    Graph graph(num_vertices);

    int u, v, cap;
    while (cin >> u >> v >> cap) {
        graph.addEdge(u, v, cap);
    }

    graph.generateLevelGraph();
    graph.printLevelGraph();
}

/* 
Difficulties: 
    Graph representation
    Level graph rep/gen
*/
