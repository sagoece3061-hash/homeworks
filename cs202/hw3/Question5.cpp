/**
 * Title: Hashing
 * Author: Sevval Ece Candogan
 * ID: 22402843
 * Section: 1
 * Homework: 3
 * Description: Question 5 - Bracelets solution
 */
#include <iostream>
#include <string>
#include <fstream>
#include "HashTable.h"

using namespace std;

// Bilekligi normalize eden fonksiyon
string getCanonical(string s) {
    string min_s = s;
    int n = s.length();
    string curr = s;

    // Tum donusleri dene
    for (int i = 0; i < n; i++) {
        char c = curr[0];
        curr.erase(0, 1);
        curr += c;
        if (curr < min_s) min_s = curr;
    }

    // Tersini al
    string rev = "";
    for (int i = n - 1; i >= 0; i--) rev += s[i];
    
    curr = rev;
    if (curr < min_s) min_s = curr;

    // Tersinin donuslerini dene
    for (int i = 0; i < n; i++) {
        char c = curr[0];
        curr.erase(0, 1);
        curr += c;
        if (curr < min_s) min_s = curr;
    }
    return min_s;
}

int main(int argc, char* argv[]) {
    if (argc < 3) return 1;

    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    
    if (!infile.is_open() || !outfile.is_open()) return 1;

    int n;
    infile >> n;

    HashTable<string, int> table;
    int reversal_count = 0;

    for (int i = 0; i < n; i++) {
        string b;
        infile >> b;
        
        string canon = getCanonical(b);
        
        if (!table.contains(canon)) {
            table.insert(canon, 1);
        }
    }

    outfile << table.size() << endl;
    
    outfile << (n > table.size() ? 1 : 0);

    infile.close();
    outfile.close();
    return 0;
}