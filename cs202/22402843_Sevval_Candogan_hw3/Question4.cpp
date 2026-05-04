/** * Title: Hashing 
 * Author : Sevval Ece Candogan
 * ID: 22402843
 * Section : 1 
 * Homework : 3 
 * Description : Question4
 */
#include "HashTable.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
    if(argc < 3) return 1;

    ifstream istrm(argv[1]);
    if (!istrm.is_open()) return 1;

    int num_docs;
    istrm >> num_docs;

    string* docNames = new string[num_docs];
    for(int i = 0; i < num_docs; i++) {
        istrm >> docNames[i];
    }
    
    string queryLine = "";
    string qWord;
    istrm >> ws;
    getline(istrm, queryLine);
    istrm.close();

    HashTable<string, DocNode*> table;

    for(int i = 0; i < num_docs; i++) {

        ifstream docFile(docNames[i].c_str());
        
        if(!docFile.is_open()) continue;

        string currentWord = "";
        char ch;
        while (docFile.get(ch)) {

            if (isalpha(static_cast<unsigned char>(ch))) 
                currentWord += tolower(static_cast<unsigned char>(ch));

            
            else if (!currentWord.empty()) {

                DocNode** head = table.find(currentWord);

                if (!head) table.insert(currentWord, new DocNode(docNames[i]));
                else {

                    DocNode* curr = *head;
                    bool found = false;

                    while (curr) {

                        if (curr->docName == docNames[i]) { curr->frequency++; found = true; break; }
                        curr = curr->next;
                    }
                    if (!found) {

                        DocNode* newNode = new DocNode(docNames[i]);
                        newNode->next = *head;
                        *head = newNode;
                    }
                }
                currentWord = "";
            }
        }
        
        if (!currentWord.empty()) {
            DocNode** head = table.find(currentWord);
            if (!head) table.insert(currentWord, new DocNode(docNames[i]));
            else {
                DocNode* curr = *head;
                bool found = false;
                while (curr) {
                    if (curr->docName == docNames[i]) { curr->frequency++; found = true; break; }
                    curr = curr->next;
                }
                if (!found) {
                    DocNode* newNode = new DocNode(docNames[i]);
                    newNode->next = *head;
                    *head = newNode;
                }
            }
        }
        docFile.close();
    }

    string queryWords[100];
    int queryWordCount = 0;
    string temp = "";

    for (int i = 0; i <= queryLine.length(); i++) {

        if (i < queryLine.length() && isalpha(static_cast<unsigned char>(queryLine[i]))) 
            temp += tolower(static_cast<unsigned char>(queryLine[i]));

        else if (!temp.empty()) {
            queryWords[queryWordCount++] = temp;
            temp = "";
        }
    }

    ofstream outFile(argv[2]);
    bool foundDoc = false;
    bool flag = true; 

    for (int i = 0; i < num_docs; i++) {
        int* freqs = new int[queryWordCount];
        bool allPresent = (queryWordCount > 0);


        if (allPresent) {
            foundDoc = true;
            
            if (!flag) {
                outFile << endl;
            }
            outFile << "in Document " << docNames[i];
            for (int j = 0; j < queryWordCount; j++) {
                outFile << ", " << queryWords[j] << " found " << freqs[j] << " times";
            }
            outFile << ".";

            flag = false;
        }

        delete[] freqs;
    }

    if (!foundDoc) {
        outFile << "No document contains the given query.";
    }

    outFile.close();
    delete[] docNames;
    return 0;
}