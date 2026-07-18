# Changelog

## v0.1.0 (2026-07-18)

Initial release.

### Features

- **Lexer** -- Full C tokenization: identifiers, keywords, all operators (single/double/triple char), number literals (int, float, hex, octal, with type suffixes), string/char literals with escape handling, preprocessor directives, single-line and block comments
- **Parser** -- Recursive descent parser for C top-level declarations:
  - Types with qualifiers (`const`, `static`, `extern`, `volatile`, `signed`), pointer levels, struct/union/enum tags
  - Function declarations and definitions (parameters, variadics, `(void)` handling)
  - Struct, union, enum definitions with named and anonymous fields
  - Typedefs: scalar, struct, enum, function pointers
  - Preprocessor directives: `#include` (system and local), `#define` (simple and function-like)
  - Extern variables and forward declarations
  - Multi-line declarations
  - Error recovery (skips to next semicolon on parse failure)
- **Header Generator** -- Produces `.h` files from parsed AST:
  - Include guards derived from filename
  - Function bodies stripped to prototypes, duplicates deduplicated
  - Anonymous `typedef struct/union/enum { ... } Name;` combined into single declarations
  - All declaration types emitted: includes, macros, structs, unions, enums, typedefs, function pointers, extern variables, forward declarations, function prototypes
- **CLI** -- Single file, directory, and recursive (`-r`) modes
- Headers generated in the same directory as the source file
- Debug logging (build with `-DCMAKE_BUILD_TYPE=Debug` to enable)

### Test files

- `test/test.c` -- Basic: includes, macros, typedef struct/enum, function pointer, extern, prototypes, forward declarations
- `test/test2.c` -- Extended: multiple includes, named structs/unions/enums, multiple typedefs, extern with qualifiers
- `test/test_edge.c` -- Edge cases: bitfields, variadics, self-referential structs, anonymous struct/union members
- `test/test_multiline.c` -- Multi-line function signatures and struct definitions
- `test/test_selfref.c` -- Self-referential struct typedef (linked list node)
