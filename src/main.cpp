
#include "Graph.h"

#include <iostream>

using std::cin;
using std::cout; using std::endl;

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

