#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <string>
#include "calculator.hpp"

namespace detail
{
    enum class Types
    {
        OPERAND = 0b00000001,
        OPEN_BRACKET = 0b00000010,
        CLOSE_BRACKET = 0b00000011,
        ADDITION = 0b00000100,
        SUBTRACTION = 0b00000101,
        MULTIPLICATION = 0b00000110,
        DIVISION = 0b00000111,
        UNARY_MINUS = 0b00001000,
        UNARY_PLUS = 0b00001001,
        INCORRECT = 0b00001010
    };

    bool is_number(const char s)
    {
        return s >= '0' && s <= '9';
    }

    bool is_operand(const std::string &value)
    {
        for (size_t i = 0; i < value.length(); i++)
            if (!is_number(value[i]))
                return false;

        return true;
    }

    bool is_operator(const Types type)
    {
        return type == detail::Types::ADDITION ||
               type == detail::Types::SUBTRACTION ||
               type == detail::Types::MULTIPLICATION ||
               type == detail::Types::DIVISION ||
               type == detail::Types::UNARY_PLUS ||
               type == detail::Types::UNARY_MINUS;
    }

    bool is_plus(const std::string &value)
    {
        return value == "+";
    }

    bool is_minus(const std::string &value)
    {
        return value == "-";
    }

    bool is_multiplication(const std::string &value)
    {
        return value == "*";
    }

    bool is_division(const std::string &value)
    {
        return value == "/";
    }

    bool is_open_bracket(const std::string &value)
    {
        return value == "(";
    }

    bool is_close_bracket(const std::string &value)
    {
        return value == ")";
    }

    detail::Types define_type(const std::string &value)
    {
        detail::Types defined_type;

        if (detail::is_operand(value))
            defined_type = detail::Types::OPERAND;
        else if (detail::is_plus(value))
            defined_type = detail::Types::ADDITION;
        else if (detail::is_minus(value))
            defined_type = detail::Types::SUBTRACTION;
        else if (detail::is_multiplication(value))
            defined_type = detail::Types::MULTIPLICATION;
        else if (detail::is_division(value))
            defined_type = detail::Types::DIVISION;
        else if (detail::is_open_bracket(value))
            defined_type = detail::Types::OPEN_BRACKET;
        else if (detail::is_close_bracket(value))
            defined_type = detail::Types::CLOSE_BRACKET;
        else
            defined_type = detail::Types::INCORRECT;

        return defined_type;
    }

    void put_operand(std::string &operand, calc::tokens &t)
    {
        t.push_back(Token(operand, detail::Types::OPERAND));
        operand.clear();
    }

    void put(const char s, calc::tokens &t, std::stack<std::string> &st)
    {
        detail::Types type = detail::define_type(std::string(1, s));

        if (st.empty())
        {
            if (type == detail::Types::ADDITION)
                type = detail::Types::UNARY_PLUS;
            else if (type == detail::Types::SUBTRACTION)
                type == detail::Types::UNARY_MINUS;
        }
        else 
            st.pop();
        
        t.push_back(Token(s, type));
    }
}

#endif
