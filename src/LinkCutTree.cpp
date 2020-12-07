
#include "LinkCutTree.h"
#include "Splay.h"
#include "Graph.h"

#include <vector>
#include <climits>

using std::vector;

namespace LinkCutTree {

/* 
    Traverse a tree rooted a v in order, and storing the path in vertices.
*/
void traverseInOrder(TreeNode* v, vector<TreeNode*>& vertices);

/* 
    Helper function for link-cut tree operations. Make the root-to-v path
    preferred, and make v the root of its auxiliary tree.
*/
void access(TreeNode* v) 
{
    // Make v the root of its auxiliary tree
    Splay::splay(v);
    
    // Remove v's preferred child since v itself is most recently accessed now.
    v->right->pathparent = v;
    v->right->parent = nullptr;
    v->right = nullptr;

    while (v->pathparent) {
        TreeNode * w = v->pathparent;

        // Move v's pathparent up to the top of its auxiliary tree
        Splay::splay(w);

        // Switch w's preferred child
        w->right->pathparent = w;
        w->right->parent = nullptr;
        w->right = v;
        v->parent = w;
        v->pathparent = nullptr;
        
        // Rotate left on v so v is root of its auxiliary tree (above w)
        Splay::splay(v);
    }
}

TreeNode* root(TreeNode* v)
{
    access(v);

    // Root is the leftmost node of the auxiliary tree
    TreeNode* root = v;
    while (root->left) {
        root = root->left;
    }
    
    Splay::splay(root);

    return root;
}

void link(TreeNode* v, TreeNode* w, int c)
{
    access(v);
    access(w);

    // v is right below w in the represented tree
    v->left = w;
    w->parent = v;
}

void cut(TreeNode* v)
{
    access(v);

    // Separate v and its parent into two trees
    v->left->parent = nullptr;
    v->left = nullptr;
}

TreeNode* mincost(TreeNode* v, Graph* graph)
{
    access(v);

    vector<TreeNode*> root_to_v;
    traverseInOrder(v->left, root_to_v);
    root_to_v.push_back(v);

    TreeNode* minNode = nullptr;
    int minCost = INT_MAX;
    for (int i = 1; i < (int)root_to_v.size(); ++i) {
        TreeNode* curr = root_to_v[i];
        TreeNode* parent = root_to_v[i-1];

        int cost = graph->getResidual(curr->vertex, parent->vertex);
        if (cost < minCost) {
            minNode = curr;
            minCost = cost;
        }
    }

    return minNode;
}

void update(TreeNode* v, int x, Graph* graph)
{
    access(v);
    
    vector<TreeNode*> root_to_v;
    traverseInOrder(v->left, root_to_v);
    root_to_v.push_back(v);

    for (int i = 1; i < (int)root_to_v.size(); ++i) {
        TreeNode* curr = root_to_v[i];
        TreeNode* parent = root_to_v[i-1];

        graph->addFlow(curr->vertex, parent->vertex, 0 - x);
    }

    return;
}

void traverseInOrder(TreeNode* v, vector<TreeNode*>& vertices)
{
    if (!v) {
        return;
    }

    traverseInOrder(v->left, vertices);
    vertices.push_back(v);
    traverseInOrder(v->right, vertices);
}

}

