#include "lexer.h"
#include <fstream>
#include <iostream>

std::vector<std::string> read_file(std::string fileName) {
    std::vector<std::string> lines;
    std::ifstream file(fileName);
    if (!file.is_open()) {
        std::cerr << "Error: could not open file: " << fileName << std::endl;
        return lines;
    }
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
    return lines;
}

void tokenise_line(std::string line) {
    for (size_t i = 0; i < line.size(); ++i){
        char ch = line[i];


    }
}

