#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>

std::vector<std::string> read_file(std::string fileName);
void tokenise_line(std::string line);

#endif // LEXER_H
