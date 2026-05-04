#include "MyList.h"

template<class type>
Node<type> operator+(Node<type> a, int i){
    while(i--){
        if(a.next)
            a = *a.next;
        else 
            throw std::runtime_error("index error");
    }

    return a;
}

template<class type>
Node<type> operator++(Node<type>& a){
    return a = a + 1;
}