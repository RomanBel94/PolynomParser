#ifndef LEXER_H
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>

namespace LexerParser
{
/*
    Types of used tokens
*/
enum class TokenType : unsigned char
{
    Undefined,
    Number,
    Newline,
    Eof
};

/*
    Struct for token description
*/
struct Token
{
    const int value;
    const TokenType type;

    explicit Token(const TokenType type, const short value = '\0')
        : type(type), value(value)
    {
    }
    ~Token() = default;

    inline bool Token::operator==(TokenType rhs) const
    {
        return this->type == rhs;
    }

    inline bool Token::operator!=(TokenType rhs) const
    {
        return this->type != rhs;
    }

    inline Token::operator TokenType() const { return type; }
    inline Token::operator int() const { return value; }

private:
    Token() = delete;
    Token(const Token&) = delete;
    Token(Token&&) noexcept = delete;
    const Token& operator=(const Token&) = delete;
    Token&& operator=(Token&&) noexcept = delete;
};

/*
    Lexer extracts tokens from input file
*/
class Lexer
{
private:
    std::ifstream input_file;
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
    inline bool is_number(const std::string& token);

public:
    Lexer();
    ~Lexer() = default;

    void extract();

    inline const std::list<Token>& Lexer::get_tokens() const { return tokens; }
};

}; // namespace LexerParser

#define LEXER_H
#endif // LEXER_H