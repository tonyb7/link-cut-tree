
#include "LinkCutTree.h"

namespace LinkCutTree {

/* 
    Splay node v within its auxiliary tree (which is a splay tree).
    Ensures that the pathparent pointer is moved to the root/splayed node.
*/
void splay(TreeNode* v) 
{

}

/* 
    Helper function for link-cut tree operations. Make the root-to-v path
    preferred, and make v the root of its auxiliary tree.
*/
void access(TreeNode* v) 
{
    // Make v the root of its auxiliary tree
    splay(v);
    
    // Remove v's preferred child since v itself is most recently accessed now.
    v->right->pathparent = v;
    v->right->parent = nullptr;
    v->right = nullptr;

    while (v->pathparent) {
        TreeNode * w = v->pathparent;

        // Move v's pathparent up to the top of its auxiliary tree
        splay(w);

        // Switch w's preferred child
        w->right->pathparent = w;
        w->right->parent = nullptr;
        w->right = v;
        v->parent = w;
        v->pathparent = nullptr;
        
        // Rotate left on v so v is root of its auxiliary tree (above w)
        splay(v);
    }
}

TreeNode* root(TreeNode* v)
{
    return v;
}

TreeNode* link(TreeNode* v, TreeNode* w, int c)
{
    return v;
}

int cut(TreeNode* v)
{
    return 0;
}

TreeNode* mincost(TreeNode* v)
{
    return v;
}

void update(TreeNode* v, int x)
{
    return;
}

}

