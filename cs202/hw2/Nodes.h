/** 
 * Title: AVL Trees and Heaps 
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1 
 * Homework: 2 
 * Description: Short description of your code 
 */
#ifndef TASKNODE
#define TASKNODE
#include <iostream>

class TaskNode{
public:
    int number;
    int arrival_time;
    int duration;
    int priority;
    
    TaskNode(){}
    TaskNode(int priority): priority(priority){}
    TaskNode(int number, int arrival_time, int duration, int priority): number(number), arrival_time(arrival_time), duration(duration), priority(priority){}
    ~TaskNode(){}
};

bool operator<(const TaskNode& l, const TaskNode& r){
    if(l.priority - l.arrival_time == r.priority - r.arrival_time)
        return l.arrival_time > r.arrival_time;
    return l.priority - l.arrival_time < r.priority - r.arrival_time;
}

std::ostream& operator<<(std::ostream& os, const TaskNode& obj){
    return os << obj.priority;
}

class ProcessorNode{
public:
    int number;
    int start_time;
    int end_time;
    
    ProcessorNode(){}
    ProcessorNode(int number, int start_time, int end_time): number(number), start_time(start_time), end_time(end_time){}
    ~ProcessorNode(){}
};

bool operator<(const ProcessorNode& l, const ProcessorNode& r){
    return l.end_time > r.end_time;
}

std::ostream& operator<<(std::ostream& os, const ProcessorNode& obj){
    return os << obj.end_time;
}

class TreeNode {
public:
    int key;

    int height; 
    TreeNode* lchild;
    TreeNode* rchild;

    int subtree_size;
    long long subtree_sum;
    int value_count;

    TreeNode() : key(), height(1), lchild(nullptr), rchild(nullptr) {}
    TreeNode(int k) : key(k), height(1), lchild(nullptr), rchild(nullptr), subtree_sum(k), subtree_size(1), value_count(1) {}
};

#endif