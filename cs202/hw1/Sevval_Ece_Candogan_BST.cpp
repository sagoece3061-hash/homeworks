/** 
 * Title: Binary Search Trees 
 * Author : Sevval Ece Candogan
 * ID: 22402843
 * Section : 1 
 * Homework : 1 
 * Description : BST implementation cpp file 
 */
#include <iostream>

class TreeNode{
public:
    int key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(): key(), left(nullptr), right(nullptr){}
    TreeNode(int k): key(k), left(nullptr), right(nullptr){}
};

class BinarySearchTree{
    TreeNode* root;
 
    TreeNode* deleteNode(int key) {
        TreeNode** s = search(root, key);

        if(!s) return root;

        if(!(*s)->left || !(*s)->right){
            TreeNode* c = nullptr;

            if((*s)->left) c = (*s)->left;
            else if((*s)->right) c = (*s)->right;

            delete *s;
            *s = c;

            return root;
        } 

        TreeNode** b = findClosestInorder((*s)->right);
        TreeNode* b_right = (*b)->right;

        (*s)->key = (*b)->key;
        delete *b;
        *b = b_right;

        return root;
    }

    TreeNode** findClosestInorder(TreeNode*& s){
        if(!s) return nullptr;

        TreeNode** b = findClosestInorder(s->left);


        if(!b) return &s;

        return b;
    }
 
    TreeNode** search(TreeNode*& node, int key){
        if(!node) return nullptr;

        if(node->key < key) return search(node->right, key);

        else if(node->key > key) return search(node->left, key);

        else return &node;
    }

    int heightHelper(TreeNode* node){
        if(!node) return 0;

        int leftHeight = heightHelper(node->left);
        int rightHeight = heightHelper(node->right);

        int ret = (leftHeight > rightHeight) ? leftHeight : rightHeight;

        return ret + 1;
    }

public:

    BinarySearchTree() : root(nullptr) {}
    
    void insert(int x){
        TreeNode** node = &root;

        while(*node){
            if((*node)->key > x){
                node = &(*node)->left;
            }
            else{
                node = &(*node)->right;
            }
        }

        *node = new TreeNode(x);
    }

    bool retrieve(int x){
        TreeNode* node = root;

        while(node){
            if(node->key > x){
                node = node->left;
            }
            else if(node->key < x){
                node = node->right;
            }
            else return true;
        }

        return false;
    }

    void deleteKey(int x){
        root = deleteNode(x);
    }

    int height(){
        return heightHelper(root);
    }
};

int main(int argc, char const *argv[])
{
    BinarySearchTree* tree = new BinarySearchTree();

    tree->insert(40);
    tree->insert(20);
    tree->insert(60);
    tree->insert(10);
    tree->insert(30);
    tree->insert(50);
    tree->insert(70);
    tree->insert(5);
    tree->insert(35);
    tree->insert(32);

    int h = tree->height();
    std::cout << h << "\n";
    return 0;
}