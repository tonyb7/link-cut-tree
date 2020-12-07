
#include "LinkCutTree.h"
#include "Splay.h"
#include "Graph.h"

#include <vector>
#include <climits>
#include <cassert>

using std::vector;
using std::shared_ptr;

// Adapted from source: https://www.youtube.com/watch?v=XZLN6NxEQWo
namespace LinkCutTree {

/* 
    Traverse a tree rooted a v in order, and storing the path in vertices.
*/
void traverseInOrder(std::shared_ptr<TreeNode> v, vector<std::shared_ptr<TreeNode>>& vertices);

/* 
    Helper function for link-cut tree operations. Make the root-to-v path
    preferred, and make v the root of its auxiliary tree.
*/
void access(std::shared_ptr<TreeNode> v) 
{
    // Make v the root of its auxiliary tree
    Splay::splay(v);
    
    // Remove v's preferred child since v itself is most recently accessed now.
    if (v->right) {
        v->right->pathparent = v;
        v->right->parent = nullptr;
        v->right = nullptr;
    }

    while (v->pathparent) {
        shared_ptr<TreeNode> w = v->pathparent;

        // Move v's pathparent up to the top of its auxiliary tree
        Splay::splay(w);

        // Switch w's preferred child
        if (w->right) {
            w->right->pathparent = w;
            w->right->parent = nullptr;
        }
        w->right = v;
        v->parent = w;
        v->pathparent = nullptr;
        
        // Rotate left on v so v is root of its auxiliary tree (above w)
        Splay::splay(v);
    }
}

std::shared_ptr<TreeNode> root(std::shared_ptr<TreeNode> v)
{
    access(v);

    // Root is the leftmost node of the auxiliary tree
    std::shared_ptr<TreeNode> root = v;
    while (root->left) {
        assert(root != root->left);
        root = root->left;
    }
    
    Splay::splay(root);

    return root;
}

void link(std::shared_ptr<TreeNode> v, std::shared_ptr<TreeNode> w, int c)
{
    access(v);
    access(w);

    assert(v != w);
    // v is right below w in the represented tree
    v->left = w;
    w->parent = v;
}

void cut(std::shared_ptr<TreeNode> v)
{
    access(v);

    // Separate v and its parent into two trees
    if (v->left) {
        v->left->parent = nullptr;
    }
    v->left = nullptr;
}

std::pair<std::shared_ptr<TreeNode>, std::shared_ptr<TreeNode>>
mincost(std::shared_ptr<TreeNode> v, Graph* graph)
{
    access(v);

    vector<shared_ptr<TreeNode>> root_to_v;
    traverseInOrder(v->left, root_to_v);
    root_to_v.push_back(v);

    shared_ptr<TreeNode> minNode = nullptr;
    shared_ptr<TreeNode> minNodeParent = nullptr;
    int minCost = INT_MAX;
    for (int i = 1; i < (int)root_to_v.size(); ++i) {
        shared_ptr<TreeNode> curr = root_to_v[i];
        shared_ptr<TreeNode> parent = root_to_v[i-1];

        int cost = graph->getResidual(curr->vertex, parent->vertex);
        if (cost < minCost) {
            minNode = curr;
            minNodeParent = parent;
            minCost = cost;
        }
    }

    return {minNode, minNodeParent};
}

void update(std::shared_ptr<TreeNode> v, int x, Graph* graph)
{
    access(v);
    
    vector<shared_ptr<TreeNode>> root_to_v;
    traverseInOrder(v->left, root_to_v);
    root_to_v.push_back(v);

    for (int i = 1; i < (int)root_to_v.size(); ++i) {
        shared_ptr<TreeNode> curr = root_to_v[i];
        shared_ptr<TreeNode> parent = root_to_v[i-1];

        graph->addFlow(curr->vertex, parent->vertex, 0 - x);
    }

    return;
}

void traverseInOrder(std::shared_ptr<TreeNode> v, vector<std::shared_ptr<TreeNode>>& vertices)
{
    if (!v) {
        return;
    }

    traverseInOrder(v->left, vertices);
    vertices.push_back(v);
    traverseInOrder(v->right, vertices);
}

}

