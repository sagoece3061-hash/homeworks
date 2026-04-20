/** 
* Title: Hashing 
* Author : Sevval Ece Candogan
* ID:  22402843
* Section : 1 
* Homework : 3 
* Description : HashTable class 
*/
#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <iostream>
#include <string>

using namespace std;

template <typename K, typename V>
struct HashNode {
    K key;
    V value;
    HashNode* next;

    HashNode(const K& k, const V& v) : key(k), value(v), next(NULL) {}
};

struct DocNode {
    string docName;
    int frequency;
    DocNode* next;
    DocNode(string name) : docName(name), frequency(1), next(NULL) {}
};


template <typename K, typename V>
class HashTable{
public:
    HashTable(int capacity = 101); 
    ~HashTable();

    void insert(const K& key, const V& value);
    bool get(const K& key, V& value); 
    bool contains(const K& key); 
    bool remove(const K& key);
    
    V* find(const K& key);
    int size() const; 

    void rehash();
    double getLoadFactor() const;

private:
    HashNode<K, V>** table;
    int capacity;
    int itemCount;
    int hashFunction(const K& key) const;
};
#endif
