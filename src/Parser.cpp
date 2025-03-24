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
inline void Parser::reset()
{
    polynom1.clear();
    polynom2.clear();
}

/*
    Switch polynoms from first to second.
*/
inline void Parser::switch_polynoms() noexcept
{
    current_polynom = &polynom2;
    current_line += 2;
}

/*
    Add a pair of numbers to current polynom.
*/
inline void Parser::add_values(const Token& power, const Token& base)
{
    current_polynom->emplace(power, base);
    line_added = true;
}

/*
    Read all tokens from tokens list and fill both polynoms.
*/
void Parser::parse()
{
    try
    {
        lexer.extract();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
    }

    if (lexer.get_tokens().empty())
        throw std::runtime_error("[FATAL] Can't parse input file!\n");

    auto current_token{lexer.get_tokens().cbegin()};
    auto next_token{current_token};
    ++next_token;

    for (; (*next_token) != LexerParser::TokenType::Eof;
         ++current_token, ++next_token)
    {
        if (*current_token == TokenType::Number &&
            *next_token == TokenType::Number)
        {
            if (!line_added)
                add_values(*current_token, *next_token);
            else
            {
                std::ostringstream error_message;
                error_message << "[FATAL] Unexpected token: \""
                              << (*next_token).value
                              << "\" at line: " << current_line << '\n';
                throw std::runtime_error(error_message.str());
            }
        }
        else if (*current_token == TokenType::Newline &&
                 *next_token == TokenType::Newline)
        {
            switch_polynoms();
            line_added = false;
        }
        else if (*current_token == TokenType::Newline)
        {
            if (line_added)
            {
                ++current_line;
                line_added = false;
            }
            else
            {
                reset();
                throw std::runtime_error("[FATAL] Wrong count of numbers!\n");
            }
        }
    }

    if (current_polynom == &polynom1)
    {
        reset();
        throw std::runtime_error("[FATAL] There is only one polynom!\n");
    }
}

}; // namespace LexerParser
