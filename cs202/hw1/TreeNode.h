/** 
 * Title: Binary Search Trees 
 * Author : Sevval Ece Candogan
 * ID: 22402843
 * Section : 1 
 * Homework : 1 
 * Description : TreeNode implementation header file 
 */

#ifndef TREE_NODE
#define TREE_NODE

class TreeNode{
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(): key(), left(nullptr), right(nullptr){}
    TreeNode(int k): key(k), left(nullptr), right(nullptr){}
};
#endif