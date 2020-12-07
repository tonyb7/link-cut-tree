
#pragma once

#include <memory>

class Graph;

namespace LinkCutTree {

    struct TreeNode {
        TreeNode() : vertex(-1) {} // default should be overwritten
        TreeNode(int vertex_) 
        : vertex(vertex_), parent(nullptr), left(nullptr), right(nullptr), pathparent(nullptr) 
        {}

        int vertex;
        std::shared_ptr<TreeNode> parent;
        std::shared_ptr<TreeNode> left;
        std::shared_ptr<TreeNode> right;
        std::shared_ptr<TreeNode> pathparent;
    };

    /*
        Return the root of the tree containing v
    */
    std::shared_ptr<TreeNode> root(std::shared_ptr<TreeNode> v);

    /*
        Combine trees containing v and w by adding an edge (v, w) with capacity c. 
        Make w the parent of v. Assumes v is a tree root (but not necessarily w), 
        and that v and w are in different trees.
    */
    void link(std::shared_ptr<TreeNode> v, std::shared_ptr<TreeNode> w, int c);

    /*
        Delete the edge (v, parent(v)), dividing the tree containing v into two trees. 
        Assumes v is not a tree root. (Do not return the cost of the deleted edge...)
    */
    void cut(std::shared_ptr<TreeNode> v);

    /*
        Return the vertex w closest to root(v) such that cost(w, parent(w)) is 
        minimal among edges on the path from v to root(v). Assumes v is not a tree root.
        
        We return the vertex closes to root(v) since we might have to consecutively 
        call this (when we delete zero-capacity edges along a path).
    */
    std::shared_ptr<TreeNode> mincost(std::shared_ptr<TreeNode> v, Graph* graph);

    /*
        Add x to the cost of all edges along the tree path from v to root(v).
    */
    void update(std::shared_ptr<TreeNode> v, int x, Graph* graph);

}

