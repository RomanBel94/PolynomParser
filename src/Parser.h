#ifndef PARSER_H
#include "Lexer.h"
#include <map>

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
    size_t current_line;
    bool line_added;

    inline void reset();
    inline void switch_polynoms() noexcept;
    inline void add_values(const Token& power, const Token& base);

public:
    Parser();
    ~Parser() = default;

    void parse();

    inline std::map<int, int>& Parser::get_polynom1() { return polynom1; }
    inline std::map<int, int>& Parser::get_polynom2() { return polynom2; }
};
}; // namespace LexerParser

#define PARSER_H
#endif // PARSER_H