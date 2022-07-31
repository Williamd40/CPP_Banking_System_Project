#ifndef fileReadManip_h
#define fileReadManip_h
#include <fstream>
#include <string>
#include <vector>
#include <sstream>




std::vector<std::vector<std::string>> readFile(std::string fileName) {

    std::vector<std::vector<std::string>> content; // vector of vectors of strings, each string is a section of the line. 
    //each vector in the vector is a line. top vector is whole file.
    std::vector<std::string> row; // vector of strings that make up each row
    std::string line, word; // stings of each word and line of the csv
    std::fstream file (fileName, std::ios::in); // whole file
    if(file.is_open())// checking that file opened correctly
    {
    while(getline(file, line))
    {
    row.clear();
    
    std::stringstream str(line);
    
    while(getline(str, word, ','))
    row.push_back(word);
    content.push_back(row);
    }
    }
    else
    std::cout<<"Could resolve file name\n";
    return content;
}




#endif // fileRead_h