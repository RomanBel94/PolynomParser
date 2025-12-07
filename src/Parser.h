#ifndef PARSER_H
#include "Lexer.h"

namespace LexerParser
{
/*
    Parser reads a list of tokens and fills two polynoms.
*/
class Parser
{
private:
    Lexer lexer;
    std::map<int, int> polynom1;
    std::map<int, int> polynom2;
    std::map<int, int>* current_polynom;
    std::size_t current_line;
    bool line_added;

    void reset();
    void extract_tokens();
    void preparsing_check();
    void postparsing_check();
    void switch_polynoms() noexcept;
    void switch_lines() noexcept;
    void add_values(const Token& power, const Token& base);
    void parsing_loop();

public:
    Parser();
    ~Parser() = default;

    void parse();

    std::map<int, int>& get_polynom1() { return polynom1; }
    std::map<int, int>& get_polynom2() { return polynom2; }
};
}; // namespace LexerParser

#define PARSER_H
#endif // PARSER_H
