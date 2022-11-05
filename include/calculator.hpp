#ifndef CALCULATOR_HPP
#define CALCULATOR_HPP

#include <string>
#include <deque>
#include "token.hpp"

namespace calc
{
    typedef std::deque<Token> tokens;

    double calculate(const std::string &expr);

    tokens parse(const std::string &expr);
    tokens to_prefix(const tokens &infix);
    double calculate_impl(const tokens &prefix);
}

#endif
