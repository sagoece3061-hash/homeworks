/** 
 * Title: Binary Search Trees 
 * Author : Sevval Ece Candogan
 * ID: 22402843
 * Section : 1 
 * Homework : 1 
 * Description : main file 
 */

#include "BinarySearchTree.h"
#include <iostream>

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

    tree->deleteKey(30);
    int h = tree->height();
    std::cout << h << "\n";
    return 0;
}
