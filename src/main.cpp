
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

    // while (graph.generateLevelGraph()) {
    //     graph.printLevelGraph();

    // }

    cout << "******** MAXIMUM FLOW RETURNED: ********" << endl;
    graph.printFlow();
}

/* 
Difficulties: 
    Graph representation
    Level graph rep/gen
*/

