#ifndef BINARY_TREE_H
#define BINARY_TREE_H
#include "TreeNode.h"

template<typename C, typename F>
class BinaryTree
{
    TreeNode<C>* root;

public:
    BinaryTree(): root(nullptr);

    void preorderTraverse(F visit_fn);
    void inorderTraverse(F visit_fn);
    void postorderTraverse(F visit_fn);

    ~BinaryTree();
};
#endif