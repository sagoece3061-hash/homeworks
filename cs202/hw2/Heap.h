/** 
 * Title: AVL Trees and Heaps 
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1 
 * Homework: 2 
 * Description: Short description of your code 
 */
#ifndef HEAP
#define HEAP
#include <iostream>

template<typename NodeType>
class Heap{

    int parent(int i){
        return (i - 1) / 2;
    }

    int left_child(int i){
        return 2 * i + 1;
    }

    int right_child(int i){
        return 2 * i + 2;
    }

public:
    NodeType* items;
    int items_size;
    int items_capacity;

    Heap(): items(nullptr), items_size(0), items_capacity(1){
        items = new NodeType[1];
    }

    Heap(int capacity): items_size(0), items_capacity(capacity){
        if(capacity == 0) items = nullptr;
        items = new NodeType[capacity];
    }

    ~Heap(){
        delete [] items;
        items_size = 0;
        items_capacity = 0;
    }

	void heapInsert(const NodeType& newItem){
        if(items_size == items_capacity){
            items_capacity = items_capacity ? items_capacity * 2 : 1;
            NodeType* newItems = new NodeType[items_capacity * 2];
            for(int i = 0; i < items_size; i++) newItems[i] = items[i];

            delete [] items;
            items = newItems;
        }

        items[items_size] = newItem;
        int i = items_size;
        items_size++;

        while(i >= 0 && items[parent(i)] < items[i]){
            swap(items[parent(i)], items[i]);
            i = parent(i);
        }
    }

	void heapDeleteFirst(){
        items[0] = items[items_size - 1];
        items_size--;

        heapifyForDeletion();
    }

    void heapify(){
        int curr_parent = 0;
        int i = curr_parent;
        bool continue_heapify = true;

        while(curr_parent >= 0){
            i = curr_parent;

            while(continue_heapify){
                
                int l_child = left_child(i);
                int r_child = right_child(i);

                //std::cout << l_child << " : " << r_child << "\n";

                if(l_child < items_size && items[i] < items[l_child]){

                    if(r_child < items_size && items[i] < items[r_child] && items[l_child] < items[r_child]){
                    
                        int new_i = items[l_child] < items[r_child] ? r_child: l_child;

                        //std::cout << items[i] << " swapped with " << items[new_i] << "\n";

                        swap(items[i], items[new_i]);
                        i = new_i;
                    }

                    else{

                        //std::cout << items[i] << " swapped with " << items[l_child] << "\n";
                        swap(items[i], items[l_child]);
                        i = l_child;
                    }

                }
                else if(r_child < items_size && items[i] < items[r_child]){
                    
                    //std::cout << items[i] << "swapped with " << items[r_child] << "\n";
                    swap(items[i], items[r_child]);
                    i = r_child;
                }

                else continue_heapify = false;
            }

            //std::cout << i << "\n";

            continue_heapify = true;
            curr_parent = curr_parent - 1;
        }
    }

    void heapifyForDeletion(){
        int curr_parent = 0;
        int i = curr_parent;
        bool continue_heapify = true;

        while(continue_heapify){
            
            int l_child = left_child(i);
            int r_child = right_child(i);

            //std::cout << l_child << " : " << r_child << "\n";

            if(l_child < items_size && items[i] < items[l_child]){

                if(r_child < items_size && items[i] < items[r_child] && items[l_child] < items[r_child]){
                
                    int new_i = items[l_child] < items[r_child] ? r_child: l_child;

                    //std::cout << items[i] << " swapped with " << items[new_i] << "\n";

                    swap(items[i], items[new_i]);
                    i = new_i;
                }

                else{

                    //std::cout << items[i] << " swapped with " << items[l_child] << "\n";
                    swap(items[i], items[l_child]);
                    i = l_child;
                }

            }
            else if(r_child < items_size && items[i] < items[r_child]){
                
                //std::cout << items[i] << "swapped with " << items[r_child] << "\n";
                swap(items[i], items[r_child]);
                i = r_child;
            }

            else continue_heapify = false;
        }

    }

    void print_heap(){
        for(int i = 0; i < items_size; i++){
            //std::cout << items[i] << "(" << items[parent(i)] << ")" << " - ";
        }
    }

    void swap(NodeType& l, NodeType& r){
        NodeType temp = l;
        l = r;
        r = temp;
    }
};
#endif