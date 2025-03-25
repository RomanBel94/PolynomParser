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

    inline size_t define_max_iterations();
    inline bool parse_polynoms();

public:
    explicit PolynomProcessor(BinaryOperator&& op);
    ~PolynomProcessor() = default;

    std::map<int, int> operator()();
};

/*
    Constructor.
*/
template <class BinaryOperator>
PolynomProcessor<BinaryOperator>::PolynomProcessor(BinaryOperator&& op)
    : op(std::forward<BinaryOperator>(op)), polynom1(parser.get_polynom1()),
      polynom2(parser.get_polynom2()){};

/*
    Return number of necessary iterations for processing polynoms.
*/
template <class BinaryOperator>
inline size_t PolynomProcessor<BinaryOperator>::define_max_iterations()
{
    return std::max((*(polynom1.crbegin())).first,
                    (*(polynom2.crbegin())).first);
}

/*
    Try to parse polynoms.
*/
template <class BinaryOperator>
inline bool PolynomProcessor<BinaryOperator>::parse_polynoms()
{
    try
    {
        parser.parse();
        return true;
    }
    catch (const std::exception& ex)
    {
        std::cerr << ex.what();
        return false;
    }
}

/*
    Main function of processing polynoms.
*/
template <class BinaryOperator>
std::map<int, int> PolynomProcessor<BinaryOperator>::operator()()
{
    if (!result_polynom.empty())
        return result_polynom;

    if (parse_polynoms())
    {
        size_t iterations = define_max_iterations();

        for (size_t i{0}; i <= iterations; ++i)
            result_polynom[i] = op(polynom1[i], polynom2[i]);

        return result_polynom;
    }
    return {};
}

#define POLYNOM_PROCESSOR_H
#endif // POLYNOM_PROCESSOR_H