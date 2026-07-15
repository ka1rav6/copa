#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include "token_definitions.h"

namespace Lexer{

std::vector<std::string> read_file(const std::string& fileName);
std::vector<Token> tokenise_line(const std::string& line, size_t line_num);

}

#endif // LEXER_H
