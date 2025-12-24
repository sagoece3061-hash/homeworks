#ifndef _MYLIST_H
#define _MYLIST_H
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include <string>
using namespace std;

template<class type>
class Node{
public:
    type value;
    Node<type>* next;

    Node(const type& val, Node<type>* nxt = nullptr) : value(val), next(nxt) {} 

    Node() : next(nullptr) {}
};

template<class type>
class MyList{
public:
    int size;
    Node<type>* first;

    MyList(): size(0), first(nullptr){
    }
    MyList(type a){
        Node<type>* new_node = new Node<type>();
        new_node->value = a;
        new_node->next = nullptr;
        size = 1;

        first = new_node;
    }

    MyList(Node<type> node){
        Node<type> search = node;
        first = node;

        while(search->next){
            size++;
            search = search->next;
        }
    }

    MyList(std::initializer_list<type> l){
        auto list_element = l.begin();
        size = l.size();

        while(list_element != l.end()){
            insert_sorted(*list_element);
            list_element++;
        }
    }

    // 1. Deep Copy Constructor
    MyList(const MyList& other) : size(0), first(nullptr) {
        Node<type>* current_other = other.first;
        while (current_other) {
            insert_sorted(current_other->value); 
            current_other = current_other->next;
        }
    }

    // 2. Copy Assignment Operator
    MyList& operator=(const MyList& other) {
        if (this == &other) {
            return *this;
        }

        Node<type>* current = first;
        Node<type>* next_node;
        while (current) {
            next_node = current->next;
            delete current;
            current = next_node;
        }
        first = nullptr;
        size = 0;

        Node<type>* current_other = other.first;
            while (current_other) {
                insert_sorted(current_other->value);
                current_other = current_other->next;
            }

            return *this;
    }

    ~MyList(){
        Node<type>* current = first;
        Node<type>* next_node = nullptr;

        while (current != nullptr) {
            next_node = current->next;
            delete current;
            current = next_node;
        }
        first = nullptr;
    }

    void insert_sorted(type a){
        Node<type>* node = new Node<type>();
        Node<type>* search = first;
        
        node->value = a;
        
        if(!first){
            size++;
            first = node;
            return;
        } 

        if(node->value <= first->value){
            node->next = first;
            first = node;
            size++;
            return;
        }

        for(int i = 0; i < size; i++){
            if(!search->next || (search->next->value >= node->value)){
                node->next = search->next;
                search->next = node;
                size++;
                return;
            }
            search = search->next;
        }
    }

    void remove(type a){
        int index = find(a);
        remove(index);
    }

    void remove(int index){
        Node<type>* search = first;
        Node<type>* temp;

        if(index >= size || index < 0) return;

        if(index == 0){
            first = search->next;
            delete search;
            size--;
            return;
        }

        for(int i = 0; i < index - 1; i++){
            search = search->next;
        } 

        temp = search->next;
        search->next = search->next->next;
        size--;
        delete temp;
    }

    void print_list() const{
        Node<type>* node = first;

        if(size == 0) return;

        std::cout << node->value;
        for(int i = 1; i < size; i++){
            std::cout << "\n";
            node = node->next;
            std::cout << node->value;
        }
        std::cout << "\n";
    }

    int find(type a) const{
        Node<type>* search = this->first;

        for(int i = 0; i < size; i++){
            if(search->value == a){
                return i;
            }
            search = search->next;
        }

        return -1;
    }

    const type& operator[](int index) const{
        Node<type>* search = first;
        if(index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        for(int i = 0; i < index; i++) search = search->next;
        return (search->value);
    }

    type& operator[](int index){
        Node<type>* search = first;
        if(index < 0 || index >= size) throw std::out_of_range("Index out of bounds");
        for(int i = 0; i < index; i++) search = search->next;
        return search->value;
    }
    
    // void MyList<BusLine>::check_stops(int stopId){
    //     Node<BusLine> search = first;

    //     while(search->next){
    //         MyList<Stop> stop_list = search->value->stops.first;
    //         while(stop_list)

    //         search = search->next;
    //     }
    // }
};

template<class type>
MyList<type> operator+(MyList<type> a, int i);

template<class type>
MyList<type> operator-(MyList<type> a, int i);

template<class type>
Node<type> operator+(Node<type> a, int i);

template<class type>
Node<type> operator++(Node<type>& a);

#endif