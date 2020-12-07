
#pragma once

#include "LinkCutTree.h"
#include <memory>

namespace Splay {

    /* 
        Splay node v within its auxiliary tree (which is a splay tree).
        Ensures that the pathparent pointer is moved to the root/splayed node.
    */
    void splay(std::shared_ptr<LinkCutTree::TreeNode> v);

    /*
        Rotate right operation used by splay.
    */
    void rotateLeft(std::shared_ptr<LinkCutTree::TreeNode>  p);

    /* 
        Rotate left operation used by splay.
    */
    void rotateRight(std::shared_ptr<LinkCutTree::TreeNode> p);
}

