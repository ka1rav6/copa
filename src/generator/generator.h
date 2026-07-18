#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>
#include "token_definitions.h"

namespace Generator {

// Generates a C header file from parsed declarations.
// outputPath: the .h file to write to.
// decls: the parsed AST declarations.
void generate_header(
    const std::string& outputPath,
    const std::vector<Lexer::Declaration>& decls);

} // namespace Generator

#endif // GENERATOR_H
