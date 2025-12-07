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
    std::size_t current_line{1};
    std::size_t current_char_pos{0};
    char current_char{'\0'};
    TokenType current_token_type{TokenType::Undefined};

public:
    LexerContext() = default;

    void go_to_next_line() noexcept
    {
        ++current_line;
        reset_current_char_pos();
    }

    std::size_t get_current_line() const noexcept { return current_line; }

    void go_to_next_char() noexcept { ++current_char_pos; }

    void reset_current_char_pos() noexcept { current_char_pos = 0; }

    std::size_t get_current_char_pos() const noexcept
    {
        return current_char_pos;
    }

    void set_current_token_type(TokenType new_type) noexcept
    {
        current_token_type = new_type;
    }

    TokenType get_current_token_type() const noexcept
    {
        return current_token_type;
    }

    void set_current_char(char ch) noexcept
    {
        current_char = ch;
        go_to_next_char();
    }

    char get_current_char() const noexcept { return current_char; }
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

    void skip_spaces();
    void process_newline();
    void process_sequence();
    void read_token();
    void add_token();
    void add_eof();
    void reset_current_token();

public:
    Lexer();
    ~Lexer() = default;

    void extract();

    const std::list<Token>& get_tokens() const { return tokens; }
};

}; // namespace LexerParser

#define LEXER_H
#endif // LEXER_H
