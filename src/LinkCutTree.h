
#pragma once

namespace LinkCutTree {

    struct TreeNode {
        TreeNode() : vertex(-1) {} // default should be overwritten
        TreeNode(int vertex_) 
        : vertex(vertex_), parent(nullptr), left(nullptr), right(nullptr), pathparent(nullptr) 
        {}

        int vertex;
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;
        TreeNode* pathparent;
    };

    /*
        Return the root of the tree containing v
    */
    TreeNode* root(TreeNode* v);

    /*
        Combine trees containing v and w by adding an edge (v, w) with capacity c. 
        Make w the parent of v. Assumes v is a tree root (but not necessarily w), 
        and that v and w are in different trees.
    */
    TreeNode* link(TreeNode* v, TreeNode* w, int c);

    /*
        Delete the edge (v, parent(v)), dividing the tree containing v into two trees. 
        Assumes v is not a tree root. (Do not return the cost of the deleted edge...)
    */
    void cut(TreeNode* v);

    /*
        Return the vertex w closest to root(v) such that cost(w, parent(w)) is 
        minimal among edges on the path from v to root(v). Assumes v is not a tree root.
        
        We return the vertex closes to root(v) since we might have to consecutively 
        call this (when we delete zero-capacity edges along a path).
    */
    TreeNode* mincost(TreeNode* v);

    /*
        Add x to the cost of all edges along the tree path from v to root(v).
    */
    void update(TreeNode* v, int x);

}

