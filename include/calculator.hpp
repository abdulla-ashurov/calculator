#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <deque>
#include "token.hpp"
#include "detail.hpp"

namespace calc
{
    typedef std::deque<Token> tokens;

    double calculate(const std::string &expr);

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);

    void to_prefix_impl(const Token &token, tokens &prefix, std::stack<Token> &st,
                        size_t &open_bracket_count, size_t &close_bracket_count);
}

#endif
