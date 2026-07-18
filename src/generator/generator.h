#ifndef GENERATOR_H
#define GENERATOR_H

#include <string>
#include <vector>
#include "token_definitions.h"

namespace Generator {

enum class IndentStyle { Spaces, Tabs };

struct FormatOptions {
    IndentStyle indent_style = IndentStyle::Spaces;
    int indent_width = 4;
    bool use_pragma_once = false;
};

void generate_header(
    const std::string& outputPath,
    const std::vector<Lexer::Declaration>& decls,
    const FormatOptions& opts = FormatOptions());

} // namespace Generator

#endif // GENERATOR_H
