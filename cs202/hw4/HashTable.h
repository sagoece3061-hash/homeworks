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
    // Constructor & Destructor
    HashTable(int capacity = 101); // Başlangıç kapasitesi (Genelde asal sayı tercih edilir)
    ~HashTable();

    // Temel Metotlar
    void insert(const K& key, const V& value);
    bool get(const K& key, V& value);        // Değeri referansla döndürür, varsa true döner
    bool contains(const K& key);            // Anahtar var mı kontrolü
    bool remove(const K& key);              // (Opsiyonel) Eleman silme
    
    // Soru 4 ve Genel Kullanım İçin: Değeri doğrudan pointer olarak al (içeriği değiştirmek için)
    V* find(const K& key);

    // Soru 3 İçin: Dictionary kod yönetimini kolaylaştıran yardımcı
    int size() const;                       // Tablodaki eleman sayısı

    // Tablo Yönetimi
    void rehash();                          // Load factor aşılınca tabloyu büyütür
    double getLoadFactor() const;

private:
    HashNode<K, V>** table;
    int capacity;
    int itemCount;
    int hashFunction(const K& key) const;
};
#endif