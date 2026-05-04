/** 
 * Title: AVL Trees and Heaps 
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1 
 * Homework: 2 
 * Description: Short description of your code 
 */
#include "Nodes.h"

class AvlTree{
    int balance(TreeNode* node) {
        if (!node){
            return 0;
        } 
            
        return height(node->lchild) - height(node->rchild);
    }

    TreeNode* sag_donus(TreeNode* dugm1) {
        TreeNode* dugm2 = dugm1->lchild;
        TreeNode* temp = dugm2->rchild;

        //yer degistirme
        dugm2->rchild = dugm1;
        dugm1->lchild = temp;

        //once usttekini update et
        updateNode(dugm1);
        updateNode(dugm2);
        return dugm2;
    }

    TreeNode* sol_donus(TreeNode* dugm1) {
        TreeNode* dugm2 = dugm1->rchild;
        TreeNode* temp = dugm2->lchild;

        //yer degistirme
        dugm2->lchild = dugm1;
        dugm1->rchild = temp;

        updateNode(dugm2);
        updateNode(dugm1);
        return dugm2;
    }

    TreeNode* findClosestInorder(TreeNode* node) {
        TreeNode* tempNode = node;

        while (tempNode->lchild){
            tempNode = tempNode->lchild;

        }
            
        return tempNode;
    }

    TreeNode* insertHelper(TreeNode* node, int key) {
        if (!node) return new TreeNode(key);

        if (key < node->key){
            node->lchild = insertHelper(node->lchild, key);
        }

        else if (key > node->key){
            node->rchild = insertHelper(node->rchild, key);
        }

        else if(key == node->key){
            node->value_count++;
            updateNode(node);
            return node;
        }

        int bal = balance(node);

        if (bal>1){
            if(key < node->lchild->key){
                return sag_donus(node);

            }

            else if(key > node->lchild->key) {
                node->lchild = sol_donus(node->lchild);
                return sag_donus(node);
            }
        }

        if (bal < -1){ 
            if(key > node->rchild->key)
                return sol_donus(node);
            else if(key < node->rchild->key) {
                node->rchild = sag_donus(node->rchild);
                return sol_donus(node);
            }
        }

        updateNode(node);
        return node;
    }

    TreeNode* deleteHelper(TreeNode* node, int key) {
        if (!node) return nullptr;

        if (key < node->key){
            node->lchild = deleteHelper(node->lchild, key);//search left

        }

        else if (key > node->key){
            
            node->rchild = deleteHelper(node->rchild, key);//search right
        }

        else {

            if(node->value_count>1){
                node->value_count--;
                updateNode(node);

                return node;
            }

            if (!node->lchild || !node->rchild) {
                TreeNode* t = nullptr;
                TreeNode* to_be_deleted = node;

                if(node->lchild) t = node->lchild;

                else if(node->rchild) t = node->rchild;

                if (!t){
                    to_be_deleted = node;
                    node = nullptr; 
                } 
                
                else {
                    *node = *t;
                    to_be_deleted = t;
                }

                delete to_be_deleted;
            } 
            
            else {
                TreeNode* temp = findClosestInorder(node->rchild);
                node->key = temp->key;
                node->value_count = temp->value_count;
                node->rchild = deleteHelper(node->rchild, temp->key);
            }
        }

        if (!node){
            return node;
        } 

        int bal = balance(node);    //get balance

        //control for rotations
        if (bal > 1){
            if(balance(node->lchild) >= 0){

                return sag_donus(node);
            }

            else{
                node->lchild = sol_donus(node->lchild);
                return sag_donus(node);
            }
        }

        if (bal <-1){
            if(balance(node->rchild) <= 0){

                return sol_donus(node);
            }
            else{
                node->rchild = sag_donus(node->rchild);
                return sol_donus(node);
            }
        }

        updateNode(node);
        return node;
    }

    void updateNode(TreeNode* node){
        if(!node) return;
        node->height = 0;   //height resetliyor
        node->subtree_size = node->value_count; //kendi countindan baslayacak
        node->subtree_sum = (node->key) * (node->value_count);

        if(node->lchild){
            node->height = node->lchild->height;
            node->subtree_size += node->lchild->subtree_size;
            node->subtree_sum += node->lchild->subtree_sum;
        }
        if(node->rchild){

            if(node->rchild->height > node->height)
                node->height = node->rchild->height;

            node->subtree_size += node->rchild->subtree_size;
            node->subtree_sum += node->rchild->subtree_sum;
        }

        node->height++;
    }

public:
    TreeNode* root;
    AvlTree() : root(nullptr) {}
    
    void insert(int x){
        root = insertHelper(root, x);
    }

    void deleteKey(int x){
        root = deleteHelper(root, x);
    }
    
    int height(TreeNode* node) {
        if (!node) return 0;
        return node->height;
    }

    int sumOfPSmallest(TreeNode* node, int p){
        if (!node || p<1) return 0;//no need for right child control this handlesit

        int leftSize = 0;
        int leftSum = 0;

        if(node->lchild){
            leftSize = node->lchild->subtree_size;
            leftSum = node->lchild->subtree_sum;
        }
        if (leftSize >= p){//left is enough
            return sumOfPSmallest(node->lchild, p);

        }

        if (leftSize + node->value_count >= p) {
            return leftSum + ((p - leftSize) * node->key);

        }
        else{//left side was not enough for p sums
            return leftSum + (node->value_count * node->key) + sumOfPSmallest(node->rchild, p - (leftSize + node->value_count));
        }
    }
};