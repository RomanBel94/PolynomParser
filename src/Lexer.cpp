#include "Lexer.h"

namespace LexerParser
{
/*
    Constructor. Open input file and read first char.
*/
Lexer::Lexer()
    : current_token_type(TokenType::Undefined), current_token_value(""),
      current_char('\0'), current_line(1)
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
        current_token_value += current_char;
        ++current_line;
    }
    else
    {
        while (!isspace(current_char) && !input_file.eof())
        {
            current_token_value += current_char;
            current_char = input_file.get();
        }
    }
    add_token();
}

/*
    Define type of extracted token.
*/
void Lexer::define_token_type()
{
    if (current_token_value == "\n")
        current_token_type = TokenType::Newline;
    else if (is_number(current_token_value))
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
    Create token and add it to the token list.
*/
void Lexer::add_token()
{
    define_token_type();

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
    Check if string is number.
*/
bool Lexer::is_number(const std::string& token)
{
    for (char symbol : token)
        if (!isdigit(symbol))
            return false;

    return true;
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
