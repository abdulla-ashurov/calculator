#ifndef DETAIL_HPP
#define DETAIL_HPP

#include <string>
#include "calculator.hpp"
#include "token.hpp"

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
                type = detail::Types::UNARY_MINUS;
        }
        else 
            st.pop();

        t.push_back(Token(s, type));
    }

    void put_all_elements_before_open_bracket(std::stack<Token> &st, calc::tokens &prefix)
    {
        while (st.top().get_type() != detail::Types::CLOSE_BRACKET)
        {
            prefix.push_back(st.top());
            st.pop();
        }
        st.pop();
    }

    void put_operator(const Token &token, calc::tokens &prefix, std::stack<Token> &st)
    {
        while (!st.empty() && token.get_type() <= st.top().get_type())
        {
            prefix.push_back(st.top());
            st.pop();
        }
        st.push(token);
    }

    void calculate_one_operand(const double operand, const detail::Types unary_operator, std::stack<double> &st)
    {
        switch (unary_operator)
        {
        case detail::Types::UNARY_PLUS:
            st.push(operand);
            break;

        case detail::Types::UNARY_MINUS:
            st.push(-operand);
            break;

        default:
            throw std::invalid_argument("invalid argument!");
            break;
        }
    }

    void calculate_two_operands(const double first_operand, const double second_operand, const detail::Types type_operator, std::stack<double> &st)
    {
        switch (type_operator)
        {
        case detail::Types::UNARY_PLUS:
            st.push(second_operand);
            st.push(first_operand);
            break;

        case detail::Types::UNARY_MINUS:
            st.push(second_operand);
            st.push(-first_operand);
            break;

        case detail::Types::ADDITION:
            st.push(first_operand + second_operand);
            break;

        case detail::Types::SUBTRACTION:
            st.push(first_operand - second_operand);
            break;

        case detail::Types::MULTIPLICATION:
            st.push(first_operand * second_operand);
            break;

        case detail::Types::DIVISION:
            if (second_operand == 0.0)
                throw std::invalid_argument("we cannot division to zero");
            st.push(first_operand / second_operand);
            break;

        default:
            throw std::invalid_argument("invalid argument!");
            break;
        }
    }
}

#endif
