#include "lexer.h"
#include <iostream>
#include <fstream>

namespace Lexer{

std::vector<std::string> read_file(const std::string& fileName) {
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

static std::vector<Token> tokenise_include(
    const std::string& line,
    size_t line_num,
    size_t* i
) {
    while (line[*i] == ' ') (*i)++;
    bool system = false;
    if (line[*i] == '<') 
        system = true;
    (*i)++;
    std::string path = "";
    if (system) {
        while (*i < line.size() && line[*i] != '>')
            path += line[(*i)++];

        if (*i == line.size())
            std::cerr << "[ERROR] include doesnt end. line : " << line << "\nline number: " << line_num << std::endl;
        return {Token{IncludeStatement(true, path), std::nullopt, line, (size_t)-1, line_num}};
    }
    if (line[*i] == '\"') {
        while (*i < line.size() && line[*i] != '"')
            path += line[(*i)++];
        if (*i == line.size())
            std::cerr << "[ERROR] include doesn't end. line : " << line << "\nline number: " << line_num << std::endl;
        return {Token{IncludeStatement(false, path), std::nullopt, line, (size_t)-1, line_num}};
    }
    std::cerr << "[ERROR] Illegal include statement. Line : " << line << "\nline number : " << line_num << std::endl;
    return {Token{IncludeStatement(false, ""), std::nullopt, line, (size_t)-1, line_num}};
}

static std::vector<Token> tokenise_define(
    const std::string& line,
    size_t line_num,
    size_t* i
) {
    std::string name = "";
    while (line[*i] == ' ') 
        ++(*i);
    while (line[*i] != ' ')
        name += line[(*i)++];

    while (line[*i] == ' ')
        ++(*i);
    std::string params = "";
    std::string body = "";

    if (line[*i] == '(') {
        while (*i < line.size() && line[*i] != ')')
            params += line[(*i)++];
        if (*i == line.size())
            std::cerr << "Macro parameters missing a parenthesis. Line : " << line << "\nLine number : " << line_num << std::endl;
        ++(*i);
    }
    while (*i != line.size()) 
        body += line[(*i)++];

    if (params == "")
        return {Token{Macro(name, body), std::nullopt, line, (size_t)-1, line_num}};
    return {Token{Macro(name, body, params), std::nullopt, line, (size_t)-1, line_num}};
}

static std::vector<Token> tokenise_unknown_directive(
    const std::string& line,
    size_t line_num
) {
    std::cerr << "Preprocessor directive not defined!\nLine : " << line << "\nLine number : " << line_num << std::endl;
    return {};
}

static std::vector<Token> handle_preprocessor_directives(
    const std::string& line,
    size_t line_num,
    size_t* i
) {
    std::string directive = "";
    while (*i < line.size() && line[*i] != ' ')
        directive += line[(*i)++];

    if (directive == "include") 
        return tokenise_include(line, line_num, i);
    if (directive == "define")
        return tokenise_define(line, line_num, i);

    return tokenise_unknown_directive(line, line_num);
}

std::vector<Token> tokenise_line(const std::string& line, size_t line_num) {
    if (line.size() == 0) {
        return {};
    }

    if (line.at(0) == '#') {
        size_t i = 1;
        return handle_preprocessor_directives(line, line_num, &i);
    }

    return {};
} 

}// namespace Lexer
