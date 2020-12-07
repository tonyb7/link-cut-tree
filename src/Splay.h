
#pragma once

#include "LinkCutTree.h"

namespace Splay {

    /* 
        Splay node v within its auxiliary tree (which is a splay tree).
        Ensures that the pathparent pointer is moved to the root/splayed node.
    */
    void splay(LinkCutTree::TreeNode* v);

    /*
        Rotate right operation used by splay.
    */
    void rotateLeft(LinkCutTree::TreeNode* p);

    /* 
        Rotate left operation used by splay.
    */
    void rotateRight(LinkCutTree::TreeNode* p);
}

