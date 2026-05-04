/**
 * Title: Hashing
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1
 * Homework: 3
 * Description: Question 5
 */
#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"

using namespace std;

string getCanonical(string s) {//does not work
    string minS = s;
    int n = s.length();
    string crrnt = s;

    for (int i = 0; i < n; i++) {
        char c = crrnt[0];
        crrnt.erase(0, 1);
        crrnt += c;
        
        if (crrnt < minS) minS = crrnt;
    }

    string rev = "";

    for (int i = n - 1; i >= 0; i--) 
        rev += s[i];
    
    crrnt = rev;
    if (crrnt < minS) minS = crrnt;
    
    for (int i = 0; i < n; i++) {
        char c = crrnt[0];
        crrnt.erase(0, 1);
        crrnt += c;
        
        if (crrnt < minS) minS = crrnt;
    }
    return minS;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    ifstream isrtm(argv[1]);
    ofstream ostrm(argv[2]);
    
    if(!isrtm.is_open()) return 1;
    
    if(!ostrm.is_open()) return 1;

    int n;
    isrtm >> n;

    HashTable<string, int> table;
    int noOfRev = 0;

    for (int i = 0; i < n; i++) {//fix
        string b;
        isrtm >> b;
        
        string canon = getCanonical(b);

        if (!table.contains(canon)) {
            table.insert(canon, 1);
        }
    }

    ostrm << table.size() << endl;

    int inn = 0;
    if(n > table.size()) inn = 1;

    ostrm << (n > table.size() ? 1 : 0);

    isrtm.close();
    ostrm.close();
    return 0;
}
