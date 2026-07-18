# copa

A C header file generator that parses C source files and generates clean, ready-to-use header files with include guards.

## How it works

copa processes a `.c` file through a 4-stage pipeline:

1. **Lexer** -- Reads the source file and tokenizes it into a stream of tokens (identifiers, keywords, operators, literals, preprocessor directives, etc.)
2. **Flattener** -- Merges per-line token vectors into a single stream, stripping comments and newlines.
3. **Parser** -- Parses the token stream into an AST of top-level declarations (functions, structs, unions, enums, typedefs, macros, includes, extern variables, forward declarations, function pointers).
4. **Generator** -- Walks the AST and emits a valid `.h` header file with:
   - A header comment crediting copa
   - Include guards (derived from the filename)
   - All declarations converted to header-appropriate form (function bodies stripped to prototypes, duplicates removed)

## Building

Requires CMake 3.16+ and a C++20 compiler.

```bash
cmake -B build -S .
cmake --build build
```

The executable is at `build/src/copa`.

## Usage

```bash
./build/src/copa <file.c>
```

This generates `<basename>.h` in the current directory. For example, `./copa src/foo.c` produces `foo.h`.

## What's implemented

### Lexer (`src/lexer/`)
- Full C tokenization: identifiers, keywords, all operators (single/double/triple char), number literals (int, float, hex, octal, with suffixes), string/char literals with escape handling
- Preprocessor directives (consumed as single tokens)
- Single-line (`//`) and block (`/* */`) comments

### Parser (`src/parser/`)
- Type parsing with qualifiers (`const`, `static`, `extern`, `volatile`, `signed`), pointer levels, struct/union/enum tags
- Function declarations and definitions (parameters, variadics, `(void)` handling)
- Struct, union, enum definitions with named and anonymous fields
- Typedefs: scalar, struct, enum, function pointers
- Preprocessor directives: `#include` (system and local), `#define` (simple and function-like)
- Extern variables and forward declarations
- Multi-line declarations
- Error recovery (skips to next semicolon on parse failure)

### Header Generator (`src/generator/`)
- Include guards derived from output filename
- Outputs all relevant declarations for a header:
  - `#include` directives (system `<...>` and local `"..."`)
  - `#define` macros (with and without parameters)
  - Struct, union, enum definitions with full field bodies
  - Anonymous `typedef struct/union/enum { ... } Name;` emitted as combined declarations
  - Function pointer typedefs
  - Extern variable declarations
  - Function prototypes (bodies stripped, duplicates deduplicated)
  - Forward declarations (`struct Foo;`, etc.)

## Test files

| File | Contents |
|------|----------|
| `test/test.c` | Basic: includes, macros, typedef struct/enum, function pointer, extern, prototypes, forward decl, function definitions |
| `test/test2.c` | Extended: multiple includes, named structs/unions/enums, multiple typedefs, function pointer typedefs, extern with qualifiers |
| `test/test_edge.c` | Edge cases: bitfields, variadics, self-referential structs, anonymous struct/union members |
| `test/test_multiline.c` | Multi-line function signatures and struct definitions |
| `test/test_selfref.c` | Self-referential struct typedef (linked list node) |

Run any test with:

```bash
./build/src/copa test/test.c   # produces test.h
./build/src/copa test/test2.c  # produces test2.h
```
