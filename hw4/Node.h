#ifndef _NODE
#define _NODE
template<class type>
class Node{
public:
    type value;
    Node<type>* next;

    Node(){
        next = nullptr;
    }

    Node(type value){
        this->value = value;
        next = nullptr;
    }

    Node(type value, Node<type> next){
        this->value = value;
        this->next = next;
        next = nullptr;
    }
};
#endif