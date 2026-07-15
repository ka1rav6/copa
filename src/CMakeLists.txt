add_library(lexer
    lexer/lexer.cpp
)

# Stubs — currently empty files, will be filled in later
add_library(generator
    generator/generator.cpp
)

add_library(parser
    parser/parser.cpp
)

# Target for the full executable (add main.cpp later)
add_executable(give-head
    main.cpp
)

target_link_libraries(give-head
    PRIVATE
        lexer
        generator
        parser
)

target_include_directories(lexer
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer
)

target_include_directories(give-head
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/generator
        ${CMAKE_CURRENT_SOURCE_DIR}/parser
)
