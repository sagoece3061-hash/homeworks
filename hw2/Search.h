#ifndef _SEARCH_H
#define _SEARCH_H
#include <cstddef>

template<class C>
size_t linear_search(C value, C* arr, size_t size);

template<class C>
size_t binary_search(C value, C* arr, size_t size);

template<class C>
size_t jump_search(C value, C* arr, size_t size);

#endif