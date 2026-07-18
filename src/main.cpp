#include "lexer.h"
#include "parser.h"
#include "generator.h"
#include <iostream>

static std::string derive_header_path(const std::string& filePath) {
    std::string baseName = filePath;
    auto slashPos = baseName.find_last_of('/');
    if (slashPos != std::string::npos)
        baseName = baseName.substr(slashPos + 1);
    auto dotPos = baseName.find_last_of('.');
    if (dotPos != std::string::npos)
        baseName = baseName.substr(0, dotPos);
    return baseName + ".h";
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: copa <file.c>" << std::endl;
        return 1;
    }

    std::string fileName = argv[1];
    std::vector<std::string> lines = Lexer::read_file(fileName);
    if (lines.empty()) {
        std::cerr << "Error: no lines read from " << fileName << std::endl;
        return 1;
    }

    // Tokenize all lines
    std::vector<std::vector<Lexer::Token>> line_tokens;
    for (size_t i = 0; i < lines.size(); i++) {
        line_tokens.push_back(Lexer::tokenise_line(lines[i], i + 1));
    }

    // Flatten into a single token stream
    std::vector<Lexer::Token> tokens = Parser::flatten_tokens(line_tokens);

    // Parse declarations
    std::vector<Lexer::Declaration> decls = Parser::parse(tokens);

    // Generate header file
    std::string headerPath = derive_header_path(fileName);
    Generator::generate_header(headerPath, decls);

    return 0;
}
