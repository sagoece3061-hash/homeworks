#ifndef TREE_NODE_H
#define TREE_NODE_H

template<class C>
class TreeNode{
public:
    C value;
    TreeNode* left;
    TreeNode* right;

    TreeNode(): left(nullptr), right(nullptr);
    TreeNode(C value): value(value), left(nullptr), right(nullptr);
    TreeNode(C value, TreeNode* left): value(value), left(left), right(nullptr);
    TreeNode(C value, TreeNode* left, TreeNode* right): value(value), left(left), right(right);

    ~TreeNode();
};
#endif