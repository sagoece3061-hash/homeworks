#ifndef _STACK
#define _STACK
#include <initializer_list>
#include  <stdexcept>
#include "Node.h"
using namespace std;

template<class type>
class Stack{
    Node<type>* head;
    
public: 
    int size;
    int capacity;

    Stack(): capacity(0), size(0), head(nullptr){}

    Stack(int capacity): capacity(capacity), size(0), head(nullptr){}

    Stack(const Stack& other) : capacity(other.capacity), size(0), head(nullptr) {
        if (!other.head) return;

        Node<type>* curr = other.head;
        Node<type>* prev = nullptr;

        while (curr) {
            Node<type>* newNode = new Node<type>(curr->value);
            if (!head) {
                head = newNode;
            } else {
                prev->next = newNode;
            }
            prev = newNode;
            curr = curr->next;
            size++;
        }
    }

    Stack& operator=(const Stack& other) {
        if (this != &other) {
            while (!empty()) {
                pop();
            }

            capacity = other.capacity;
            Node<type>* curr = other.head;
            Node<type>* prev = nullptr;
            while (curr != nullptr) {
                Node<type>* newNode = new Node<type>(curr->value);
                if (head == nullptr) head = newNode;
                else prev->next = newNode;
                prev = newNode;
                curr = curr->next;
                size++;
            }
        }
        return *this;
    }

    Stack(Stack&& other) noexcept : head(other.head), size(other.size), capacity(other.capacity) {
        other.head = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    Stack& operator=(Stack&& other) noexcept {
        if (this != &other) {
            while (!empty()) pop();

            head = other.head;
            size = other.size;
            capacity = other.capacity;

            other.head = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    ~Stack(){
        if(size == 0) return;
        Node<type>* temp = head;
        Node<type>* next = temp->next;

        while(temp){
            next = temp->next;
            delete temp;
            temp = next;
        }

        size = 0;
        capacity = 0;
    }

    type top(){
        if(size == 0) throw runtime_error("size is zero");
        return head->value;
    }
	
    bool empty(){
        return !size;
    }

    void push(const type& value){
        Node<type>* new_elem = new Node<type>(value);
        new_elem->next = head;
        head = new_elem;
        size++;
    }
    
    type pop(){
        if(size == 0) throw runtime_error("size is zero");
        Node<type>* hn = head->next;
        type ret = head->value;
        delete head;
        head = hn;
        size--;
        return ret;
    }

    template<typename U>
    friend std::ostream& operator<<(ostream& ost, const Stack<U>& stack);
};

template<class type>
std::ostream& operator<<(ostream& ost, const Stack<type>& stack) {
    Node<type>* temp = stack.head;
    ost << "[ ";
    if(stack.size != 0){
        ost << temp->value;
        temp = temp->next;
        for(int i = 1; i < stack.size; i++){
            ost << ", " << temp->value;
            temp = temp->next;
        }
    }
    ost << " ]\n";
    
    return ost;
}

template<class type>
int stackSearch(Stack<type> stack, type a){
    int size = stack.size;

    for(int i = 0; i < size; i++){
        if(a == stack.top())
            return i; 
        stack.pop();
    }

    return -1;
}
#endif