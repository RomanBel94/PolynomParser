#include "Lexer.h"
#include <filesystem>
#include <format>

namespace LexerParser
{
const std::regex Lexer::number_regex{R"(\d+)"};

/*
    Constructor. Initialize all fields.
*/
Lexer::Lexer() : current_token_value("") {}

/*
    Skip any space excluding newline symbol.
*/
void Lexer::skip_spaces()
{
    while (isspace(context.get_current_char()) &&
           context.get_current_char() != '\n')
        context.set_current_char(input_file.get());
}

/*
    Read newline symbol.
*/
void Lexer::process_newline()
{
    current_token_value += context.get_current_char();
    context.set_current_token_type(TokenType::Newline);
    context.go_to_next_line();
}

/*
    Read sequence of symbols.
*/
void Lexer::process_sequence()
{
    while (!isspace(context.get_current_char()) && !input_file.eof())
    {
        current_token_value += context.get_current_char();
        context.set_current_char(input_file.get());
    }
    if (std::regex_match(current_token_value, number_regex))
        context.set_current_token_type(TokenType::Number);
    else
    {
        tokens.clear();
        throw std::runtime_error(std::format(
            "[FATAL] Invalid token \"{}\" at line: {}, pos: {}\n",
            current_token_value, context.get_current_line(),
            context.get_current_char_pos() - current_token_value.size()));
    }
}

/*
    Exstract next token, and add it to token list.
*/
void Lexer::read_token()
{
    if (input_file.eof())
    {
        add_eof();
        return;
    }

    skip_spaces();

    if (context.get_current_char() == '\n')
    {
        process_newline();
    }
    else
    {
        process_sequence();
    }
    add_token();
}

/*
    Create token and add it to the token list.
*/
void Lexer::add_token()
{
    if (context.get_current_token_type() == TokenType::Number)
        tokens.emplace_back(context.get_current_token_type(),
                            std::stoi(current_token_value));
    else if (context.get_current_token_type() == TokenType::Newline)
        tokens.emplace_back(context.get_current_token_type(), '\n');

    reset_current_token();
}

/*
    Add special "EOF" token.
*/
void Lexer::add_eof()
{
    context.set_current_token_type(TokenType::Eof);
    tokens.emplace_back(context.get_current_token_type());
}

/*
    Reset current token type and value.
*/
void Lexer::reset_current_token()
{
    if (context.get_current_token_type() == TokenType::Newline)
        context.set_current_char(input_file.get());

    context.set_current_token_type(TokenType::Undefined);
    current_token_value.clear();
}

/*
    Extract all tokens from input file.
*/
void Lexer::extract()
{
    std::filesystem::path filename{"polynoms.txt"};
    input_file.open(filename, std::ios::in);
    if (!input_file.is_open())
    {
        tokens.clear();
        throw std::runtime_error("[FATAL] Can't open input file!\n");
    }
    else
        context.set_current_char(input_file.get());

    while (context.get_current_token_type() != TokenType::Eof)
        read_token();
}

}; // namespace LexerParser
