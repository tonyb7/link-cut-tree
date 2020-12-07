
#include "Splay.h"
#include <cassert>

// Adapted from source: https://en.wikipedia.org/wiki/Splay_tree
namespace Splay {

void splay(LinkCutTree::TreeNode* v)
{
    while (v->parent) {
        if (!v->parent->parent) {
            // zig
            if (v->parent->left == v) {
                rotateRight(v->parent);
            }
            else {
                rotateLeft(v->parent);
            }
        }
        else if (v->parent->left == v && v->parent->parent->left == v->parent) {
            // zig zig
            rotateRight(v->parent->parent);
            rotateRight(v->parent);
        }
        else if (v->parent->right == v && v->parent->parent->right == v->parent) {
            //  zig zig
            rotateLeft(v->parent->parent);
            rotateLeft(v->parent);
        }
        else if (v->parent->left == v && v->parent->parent->right == v->parent) {
            // zig zag
            rotateRight(v->parent);
            rotateLeft(v->parent);
        }
        else {
            // zig zag
            assert(v->parent->right == v && v->parent->parent->left == v->parent);
            rotateLeft(v->parent);
            rotateRight(v->parent);
        }
    }
}

void rotateLeft(LinkCutTree::TreeNode* p)
{
    LinkCutTree::TreeNode* v = p->right;
    if (v) {
        p->right = v->left;
        if (v->left) {
            v->left->parent = p;
        }
        v->parent = p->parent;
        v->left = p;
    }

    if (!p->parent) {
        v->pathparent = p->pathparent;
        p->pathparent = nullptr;
    }
    else if (p == p->parent->left) {
        p->parent->left = v;
    }
    else {
        p->parent->right = v;
    }

    p->parent = v;
}

void rotateRight(LinkCutTree::TreeNode* p)
{
    LinkCutTree::TreeNode* v = p->left;
    if (v) {
        p->left = v->right;
        if (v->right) {
            v->right->parent = p;
        }
        v->parent = p->parent;
        v->right = p;
    }

    if (!p->parent) {
        v->pathparent = p->pathparent;
        p->pathparent = nullptr;
    }
    else if (p == p->parent->left) {
        p->parent->left = v;
    }
    else {
        p->parent->right = v;
    }
    
    p->parent = v;
}

}

