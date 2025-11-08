#ifndef LEXER_H
#include <fstream>
#include <list>
#include <regex>

#include "Token.hpp"

namespace LexerParser
{
class LexerContext
{
private:
    size_t current_line{1};
    size_t current_char_pos{0};
    char current_char{'\0'};
    TokenType current_token_type{TokenType::Undefined};

public:
    LexerContext() = default;

    inline void go_to_next_line() noexcept
    {
        ++current_line;
        reset_current_char_pos();
    }
    inline size_t get_current_line() const noexcept { return current_line; }

    inline void go_to_next_char() noexcept { ++current_char_pos; }
    inline void reset_current_char_pos() noexcept { current_char_pos = 0; }
    inline size_t get_current_char_pos() const noexcept
    {
        return current_char_pos;
    }

    inline void set_current_token_type(TokenType new_type) noexcept
    {
        current_token_type = new_type;
    }
    inline TokenType get_current_token_type() const noexcept
    {
        return current_token_type;
    }

    inline void set_current_char(char ch) noexcept
    {
        current_char = ch;
        go_to_next_char();
    }
    inline char get_current_char() const noexcept { return current_char; }
};

/*
    Lexer extracts tokens from input file
*/
class Lexer
{
private:
    static const std::regex number_regex;

    std::ifstream input_file;
    LexerContext context;
    std::string current_token_value;
    std::list<Token> tokens;

    inline void skip_spaces();
    inline void process_newline();
    inline void process_sequence();
    inline void read_token();
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
