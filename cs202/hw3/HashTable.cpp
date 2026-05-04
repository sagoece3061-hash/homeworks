/** 
 * Title: Hashing 
 * Author : Sevval Ece Candogan
 * ID:  22402843
 * Section : 1 
 * Homework : 3 
 * Description : HashTable class 
 */
#include "HashTable.h"

bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    
    return true;
}

int findNextPrime(int n) {
    int next = n + 1;

    while (!isPrime(next)) {
        next++;
    }

    return next;
}

template <typename K, typename V>
HashTable<K,V>::HashTable(int capacity){
    this->capacity = capacity;
    this->itemCount = 0;

    this->table = new HashNode<K,V>*[capacity];

    for(int i = 0; i < capacity; i++){
        this->table[i] = nullptr;
    }
}

template <typename K, typename V>
HashTable<K,V>::~HashTable(){
    for(int i = 0; i < capacity; i++){
        HashNode<K,V>* c = table[i];

        while(c){
            HashNode<K,V>* t = c;
            c = c->next;
            delete t;
        }
    }

    delete [] table;
}

template <typename K, typename V>
void HashTable<K,V>::insert(const K& key, const V& value){
    if (capacity > 0 && getLoadFactor() > 1.0) { 
        rehash();
    }

    int idx = hashFunction(key);

    HashNode<K,V>* c = table[idx];

    while(c){
        if(c->key == key){
            c->value = value;
            return;
        }
        c = c->next;
    }

    HashNode<K,V>* newValue = new HashNode<K,V>(key, value);
    newValue->next = table[idx];
    table[idx] = newValue;
    itemCount++;
}

template <typename K, typename V>
bool HashTable<K,V>::get(const K& key, V& value){
    int idx = hashFunction(key);

    HashNode<K,V>* c = table[idx];

    while(c){
        if(c->key == key){
            value = c->value;
            return true;
        }
        c = c->next;
    }

    return false;
}

template <typename K, typename V>
bool HashTable<K,V>::contains(const K& key){
    int idx = hashFunction(key);

    HashNode<K, V>* c = table[idx];

    while(c){
        if(c->key == key)
            return true;
        c = c->next;
    }

    return false;
}

template <typename K, typename V>
bool HashTable<K,V>::remove(const K& key){return false;}

template <typename K, typename V>
V* HashTable<K,V>::find(const K& key){
    int idx = hashFunction(key);

    HashNode<K,V>* c = table[idx];

    while(c){
        if(c->key == key){
            return &c->value;
        }
        c = c->next;
    }

    return nullptr;
}

template <typename K, typename V>
int HashTable<K,V>::size() const{
    return itemCount;
}

template <typename K, typename V>
void HashTable<K,V>::rehash(){
    int newCapacity = findNextPrime(2*capacity);

    HashNode<K,V>** oldTable = table;
    table = new HashNode<K,V>*[newCapacity];

    int oldCapacity = capacity;
    capacity = newCapacity;
    itemCount = 0;

    for(int i = 0; i < newCapacity; i++) table[i] = nullptr;

    for(int i = 0; i < oldCapacity; i++){
        HashNode<K,V>* listNode = oldTable[i];

        while(listNode){
            HashNode<K,V>* t = listNode->next;

            insert(listNode->key, listNode->value);

            delete listNode;
            listNode = t;
        }
    }

    delete[] oldTable;
}

template <typename K, typename V>
double HashTable<K,V>::getLoadFactor() const{
    return ((double)itemCount / capacity);
}

template <typename K, typename V>
int HashTable<K, V>::hashFunction(const K& key) const {
    unsigned long hash = 5381;
    
    for (size_t i = 0; i < key.length(); i++) {
        hash = ((hash << 5) + hash) + (unsigned char)key[i];
    }

    return (int)(hash % capacity);
}

template class HashTable<string, int>;
template class HashTable<std::string, DocNode*>;