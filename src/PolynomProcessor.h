#ifndef POLYNOM_PROCESSOR_H
#include "Parser.h"

/*
    PolynomProcessor proceeds two polynoms with passed functionsl object.
*/
class PolynomProcessor
{
    using Parser = LexerParser::Parser;

private:
    Parser parser;
    std::map<int, int>& polynom1;
    std::map<int, int>& polynom2;

    PolynomProcessor(const PolynomProcessor&) = delete;
    PolynomProcessor(PolynomProcessor&&) noexcept = delete;
    PolynomProcessor& operator=(const PolynomProcessor&) = delete;
    PolynomProcessor&& operator=(PolynomProcessor&&) noexcept = delete;

    inline size_t find_max_key();

public:
    PolynomProcessor();
    ~PolynomProcessor() = default;

    template <class Binary_Operator>
    std::map<int, int> operator()(Binary_Operator&& op);
};

PolynomProcessor::PolynomProcessor()
    : polynom1(parser.get_polynom1()), polynom2(parser.get_polynom2()) {};

inline size_t PolynomProcessor::find_max_key()
{
    return std::max((*(polynom1.crbegin())).first,
                    (*(polynom2.crbegin())).first);
}

template <class Binary_Operator>
std::map<int, int> PolynomProcessor::operator()(Binary_Operator&& op)
{
    std::map<int, int> result;
    try
    {
        parser.parse();
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
        return {};
    }

    size_t iterations = find_max_key();

    for (size_t i{0}; i <= iterations; ++i)
        result[i] = op(polynom1[i], polynom2[i]);

    return result;
}

#define POLYNOM_PROCESSOR_H
#endif // POLYNOM_PROCESSOR_H