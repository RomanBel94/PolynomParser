#include "PolynomProcessor.h"

int main()
{
    LexerParser::Lexer lexer;
    try
    {
        lexer.extract();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
    }

    std::cout << "[DEBUG] Lexer has read theese tokens:\n";
    for (const LexerParser::Token& token : lexer.get_tokens())
    {
        switch (token.type)
        {
        case LexerParser::TokenType::Newline:
            std::cout << "[DEBUG] Token type: Newline; "
                      << "token value: \\n\n";
            break;
        case LexerParser::TokenType::Number:
            std::cout << "[DEBUG] Token type: Number; "
                      << "token value: " << token.value << '\n';
            break;
        case LexerParser::TokenType::Eof:
            std::cout << "[DEBUG] Token type: Eof; "
                      << "token value: eof()\n";
            break;
        default:
            std::cout << "[DEBUG] Token type: Undefined; "
                      << "token value: " << token.value << '\n';
        }
    }

    LexerParser::Parser parser;
    try
    {
        parser.parse();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
    }

    std::cout << "[DEBUG] Polynom1: \n";
    for (const auto& [power, base] : parser.get_polynom1())
        std::cout << "[DEBUG] Power: " << power << ", base: " << base << '\n';

    std::cout << "[DEBUG] Polynom2: \n";
    for (const auto& [power, base] : parser.get_polynom2())
        std::cout << "[DEBUG] Power: " << power << ", base: " << base << '\n';

    PolynomProcessor proc;
    auto result = proc(std::plus());

    std::cout << "[DEBUG] Result: \n";
    for (const auto& [power, base] : result)
        std::cout << "[DEBUG] Power: " << power << ", base: " << base << '\n';

    return EXIT_SUCCESS;
}