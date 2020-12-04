
#include <iostream>
#include <unordered_map>

using std::cin;
using std::unordered_map;

struct Tree {

};

int main()
{
    int numVertices;
    cin >> numVertices;

    unordered_map<int, Tree*> trees; // maintain a forest of trees
    for (int i = 0; i < numVertices; ++i) {
        auto tree = new Tree;
        trees[i] = tree;
    }


    
}

