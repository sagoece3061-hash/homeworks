#include "Search.h"

template<class C>
size_t linear_search(C value, C* arr, size_t size){
    for(int i = 0; i < size; i++){
        if(arr[i] == value) return i;
    }
    return -1;
}

template<class C>
size_t binary_search(C value, C* arr, size_t size){
    size_t upper = size;
    size_t lower = 0;
    size_t mid;
    
    while(upper >= lower){
        mid = (upper + lower) / 2;
        if(arr[mid] > value){

        }
        else if(arr[mid] < value){

        }
        else return mid;
    }

    return -1;
}

template<class C>
size_t jump_search(C value, C* arr, size_t size){
    
}