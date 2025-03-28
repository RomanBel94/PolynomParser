#ifndef LEXER_H
#include <fstream>
#include <iostream>
#include <list>
#include <regex>
#include <sstream>

#include "Token.hpp"

namespace LexerParser
{
/*
    Lexer extracts tokens from input file
*/
class Lexer
{
private:
    std::ifstream input_file;
    const std::regex number_regex;
    std::string current_token_value;
    std::list<Token> tokens;
    size_t current_line;
    TokenType current_token_type;
    char current_char;

    inline void skip_spaces();
    inline void process_newline();
    inline void process_sequence();
    inline void read_token();
    inline void define_token_type();
    inline void add_token();
    inline void add_eof();
    inline void reset_current_token();

public:
    Lexer();
    ~Lexer() = default;

    void extract();

    inline const std::list<Token>& get_tokens() const { return tokens; }
};

}; // namespace LexerParser

#define LEXER_H
#endif // LEXER_H
