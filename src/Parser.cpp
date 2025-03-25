#include "Parser.h"

namespace LexerParser
{
/*
    Default constructor.
*/
Parser::Parser()
    : current_polynom(&polynom1), current_line(1), line_added(false)
{
}

/*
    Clear both polynoms.
*/
void Parser::reset()
{
    polynom1.clear();
    polynom2.clear();
}

/*
    Start extracting tokens.
*/
void Parser::extract_tokens()
{
    try
    {
        lexer.extract();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
    }
}

/*
    Check cases when parsing is not possible.
*/
void Parser::preparsing_check()
{
    if (lexer.get_tokens().empty())
        throw std::runtime_error("[FATAL] Can't parse input file!\n");

    if (std::count_if(std::begin(lexer.get_tokens()),
                      std::end(lexer.get_tokens()), [](const Token& tok)
                      { return tok.type == TokenType::Number; }) %
            2 ==
        1)
        throw std::runtime_error(
            "[FATAL] Odd count of numbers is not permitted!\n");
}

/*
    Check result of parsing.
*/
void Parser::postparsing_check()
{
    if (!polynom1.size() || !polynom2.size())
    {
        reset();
        throw std::runtime_error("[FATAL] Couldn't read all polynoms!\n");
    }
}

/*
    Switch polynoms from first to second.
*/
void Parser::switch_polynoms() noexcept
{
    current_polynom = &polynom2;
    current_line += 2;
    line_added = false;
}

/*
    Increment current line.
*/
void Parser::switch_lines() noexcept
{
    ++current_line;
    line_added = false;
}

/*
    Add a pair of numbers to current polynom.
*/
void Parser::add_values(const Token& power, const Token& base)
{
    if (!line_added)
    {
        current_polynom->emplace(power, base);
        line_added = true;
    }
    else
    {
        std::ostringstream error_message;
        error_message << "[FATAL] Unexpected token: \"" << base.value
                      << "\" at line: " << current_line << '\n';
        throw std::runtime_error(error_message.str());
    }
}

/*
    Read all tokens from tokens list and fill both polynoms.
*/
void Parser::parse()
{
    extract_tokens();

    preparsing_check();

    parsing_loop();

    postparsing_check();
}

/*
    Main loop of parsing algorithm.
*/
void Parser::parsing_loop()
{
    auto current_token{lexer.get_tokens().cbegin()};
    auto next_token{current_token};
    ++next_token;

    for (; (*next_token) != LexerParser::TokenType::Eof;
         ++current_token, ++next_token)
    {
        if (*current_token == TokenType::Number &&
            *next_token == TokenType::Number)
        {
            add_values(*current_token, *next_token);
        }
        else if (*current_token == TokenType::Newline &&
                 *next_token == TokenType::Newline)
        {
            switch_polynoms();
        }
        else if (*current_token == TokenType::Newline)
        {
            switch_lines();
        }
    }
}
}; // namespace LexerParser
