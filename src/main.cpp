
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

    cout << "******** INITIAL NETWORK STATE: ********" << endl;
    graph.printFlow();

    int iterations = 0;
    while (graph.generateLevelGraph()) {
        cout << "******** ITERATION " << ++iterations << " ********" << endl;
        graph.printLevelGraph();

        // Find a blocking flow in the level graph using dynamic link-cut trees
        // and add it to the total flow.
        graph.addBlockingFlow();

        cout << "\nNetwork state after finding a blocking flow" << endl;
        graph.printFlow();
        graph.resetLevelGraph();
    }

    cout << "******** MAXIMUM FLOW RETURNED: ********" << endl;
    graph.printFlow();
}

