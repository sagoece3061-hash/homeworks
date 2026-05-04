/** 
 * Title: Binary Search Trees 
 * Author : Sevval Ece Candogan
 * ID: 22402843
 * Section : 1 
 * Homework : 1 
 * Description : BST implementation header file 
 */

#ifndef BINARY_SEARCH_TREE
#define BINARY_SEARCH_TREE
#include "TreeNode.h"

class BinarySearchTree{
    TreeNode* root;
    TreeNode* deleteNode(int key);
    TreeNode** findClosestInorder(TreeNode*& s);
    TreeNode** search(TreeNode*& node, int key);
public:
    void insert(int x);
    bool retrieve(int x);
    void deleteKey(int x); 
    int height();
    int heightHelper(TreeNode* node);
};
#endif
