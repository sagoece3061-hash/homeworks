/** 
 * Title: Hashing 
 * Author : Sevval Ece Candogan
 * ID:  22402843
 * Section : 1 
 * Homework : 3 
 * Description : Question3 solution
 */
#include "HashTable.h"
#include <fstream>
#include <iostream>

int main(int argc, char const *argv[])
{
    if(argc < 3){
        std::cerr << "Error: NO INPUT\n";
        return 1;
    }
    std::string inputFilename = argv[1];
    std::string outputFileName = argv[2];
    std::ifstream istrm(inputFilename);

    if (!istrm.is_open())
        std::cout << "failed to open " << inputFilename << '\n';
    else{
        std::string line;
        std::getline(istrm, line);
        istrm.close();

        std::ofstream outFile(outputFileName);

        if(!outFile.is_open()){
            std::cout << "failed to open " << outputFileName << '\n';
            return 0;
        }
        
        HashTable<std::string, int> table;
        
        for(int i = 0; i < 26; i++)
            table.insert(std::string(1, 'a' + i), i);
        
        int next_code = 26;
        int next_char = 0;

        while(next_char < line.size()){
            int prefix_length = 1;
            std::string prefix = line.substr(next_char, prefix_length);

            while(next_char + prefix_length < line.size()){
                std::string new_prefix = line.substr(next_char, prefix_length + 1);
                if(table.contains(new_prefix)){
                    prefix = new_prefix;
                    prefix_length++;
                }
                else{
                    table.insert(new_prefix, next_code++);
                    break;
                }
            }

            int output;
            table.get(prefix, output);
            outFile << output;

            next_char += prefix_length;

            if(next_char < line.size())
                outFile << " ";
        }

        outFile.close();
    }

    return 0;
}
