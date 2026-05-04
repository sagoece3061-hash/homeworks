/** 
 * Title: AVL Trees and Heaps 
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1 
 * Homework: 2 
 * Description: Short description of your code 
 */
#include <iostream>
#include <fstream>
#include "AvlTree.h"
#include <chrono>

int main(int argc, char const *argv[])
{
    auto start = std::chrono::high_resolution_clock::now();
    if(argc < 2){
        std::cerr << "Error: NO INPUT\n";
        return 1;
    }
    std::string filename = argv[1];
    std::ifstream istrm(filename);

    int* scores;
    int scores_size = 0;
    int window_size;
    int p;

    AvlTree* tree = new AvlTree();


    if (!istrm.is_open())
        std::cout << "failed to open " << filename << '\n';
    else{
        istrm >> scores_size;
        istrm >> window_size;
        istrm >> p;

        scores = new int[scores_size];

        for(int i = 0; i < scores_size; i++){
            istrm >> scores[i];
            //std::cout << scores[i] << "\n";
        }
    }

    long long global_sum = 0;
    for(int i = 0; i < scores_size; i++){
        tree->insert(scores[i]);

        if(i > window_size - 1)        
            tree->deleteKey(scores[i - window_size]);

        if(i > window_size - 2){
            int sum = tree->sumOfPSmallest(tree->root, p);
            global_sum += sum;
            std::cout << sum << " ";

        }

    }

    std::cout << "\nGlobal Sum: " << global_sum << "\n";

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double, std::milli> elapsed = end - start;
    //std::cout << "Total program execution time: " << elapsed.count() << " ms\n";
    return 0;
}