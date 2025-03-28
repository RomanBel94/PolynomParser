#include "Lexer.h"

namespace LexerParser
{
/*
    Constructor. Initialize all fields.
*/
Lexer::Lexer()
    : current_token_type(TokenType::Undefined), current_token_value(""),
      current_char('\0'), current_line(1), number_regex("\\d+")
{
}

/*
    Skip any space excluding newline symbol.
*/
void Lexer::skip_spaces()
{
    while (isspace(current_char) && current_char != '\n')
        current_char = input_file.get();
}

/*
    Read newline symbol.
*/
void Lexer::process_newline()
{
    current_token_value += current_char;
    current_token_type = TokenType::Newline;
    ++current_line;
}

/*
    Read sequence of symbols.
*/
void Lexer::process_sequence()
{
    while (!isspace(current_char) && !input_file.eof())
    {
        current_token_value += current_char;
        current_char = input_file.get();
    }
    if (std::regex_match(current_token_value, number_regex))
        current_token_type = TokenType::Number;
    else
    {
        tokens.clear();
        std::ostringstream error_message;
        error_message << "[FATAL] Invalid token \"" << current_token_value
                      << "\" at line: " << current_line << '\n';
        throw std::runtime_error(error_message.str());
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

    if (current_char == '\n')
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
    if (current_token_type == TokenType::Number)
        tokens.emplace_back(current_token_type, std::stoi(current_token_value));
    else if (current_token_type == TokenType::Newline)
        tokens.emplace_back(current_token_type, '\n');

    reset_current_token();
}

/*
    Add special "EOF" token.
*/
void Lexer::add_eof()
{
    current_token_type = TokenType::Eof;
    tokens.emplace_back(current_token_type);
}

/*
    Reset current token type and value.
*/
void Lexer::reset_current_token()
{
    if (current_token_type == TokenType::Newline)
        current_char = input_file.get();

    current_token_type = TokenType::Undefined;
    current_token_value.clear();
}

/*
    Extract all tokens from input file.
*/
void Lexer::extract()
{
    input_file.open("polynoms.txt", std::ios::in);
    if (!input_file.is_open())
    {
        tokens.clear();
        throw std::runtime_error("[FATAL] Can't open input file!\n");
    }
    else
        current_char = input_file.get();

    while (current_token_type != TokenType::Eof)
        read_token();
}

}; // namespace LexerParser
