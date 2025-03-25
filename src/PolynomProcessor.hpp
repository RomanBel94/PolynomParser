#ifndef POLYNOM_PROCESSOR_H
#include "Parser.h"
#include <utility>

/*
    PolynomProcessor proceeds two polynoms with passed functional object.
*/
template <class BinaryOperator>
class PolynomProcessor
{
    using Parser = LexerParser::Parser;

private:
    Parser parser;
    BinaryOperator op;
    std::map<int, int>& polynom1;
    std::map<int, int>& polynom2;
    std::map<int, int> result_polynom;

    PolynomProcessor(const PolynomProcessor&) = delete;
    PolynomProcessor(PolynomProcessor&&) noexcept = delete;
    PolynomProcessor& operator=(const PolynomProcessor&) = delete;
    PolynomProcessor&& operator=(PolynomProcessor&&) noexcept = delete;

    inline size_t find_max_key();

public:
    explicit PolynomProcessor(BinaryOperator&& op);
    ~PolynomProcessor() = default;

    std::map<int, int> operator()();
};

template <class BinaryOperator>
PolynomProcessor<BinaryOperator>::PolynomProcessor(BinaryOperator&& op)
    : op(std::forward<BinaryOperator>(op)), polynom1(parser.get_polynom1()),
      polynom2(parser.get_polynom2()){};

template <class BinaryOperator>
inline size_t PolynomProcessor<BinaryOperator>::find_max_key()
{
    return std::max((*(polynom1.crbegin())).first,
                    (*(polynom2.crbegin())).first);
}

template <class BinaryOperator>
std::map<int, int> PolynomProcessor<BinaryOperator>::operator()()
{
    if (!result_polynom.empty())
        return result_polynom;

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
        result_polynom[i] = op(polynom1[i], polynom2[i]);

    return result_polynom;
}

#define POLYNOM_PROCESSOR_H
#endif // POLYNOM_PROCESSOR_H