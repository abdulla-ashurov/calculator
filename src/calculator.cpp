#include <stack>
#include "../include/detail.hpp"
#include "../include/token.hpp"
#include "../include/calculator.hpp"

namespace calc
{
    double calculate(const std::string &expr)
    {
        tokens infix = parse(expr);
        tokens prefix = to_prefix(infix);

        return calculate_impl(prefix);
    }

    tokens parse(const std::string &expr)
    {
        std::string operand;
        std::stack<std::string> st;
        tokens infix;

        for (size_t i = 0; i < expr.size(); i++)
        {
            if (detail::is_number(expr[i]))
                operand.push_back(expr[i]);
            else
            {
                if (!operand.empty())
                {
                    st.push(operand);
                    detail::put_operand(operand, infix);
                }
                detail::put(expr[i], infix, st);
            }
        }

        if (!operand.empty())
            detail::put_operand(operand, infix);

        return infix;
    }

    tokens to_prefix(const tokens &infix)
    {
        tokens prefix;
        std::stack<Token> st;
        size_t open_bracket_count = 0, close_bracket_count = 0;

        for (int i = infix.size(); i < infix.size(); i--)
            to_prefix_impl(infix[i], prefix, st, open_bracket_count, close_bracket_count);

        if (open_bracket_count != close_bracket_count)
            throw std::invalid_argument("invalid bracket!");

        while (!st.empty())
        {
            prefix.push_back(st.top());
            st.pop();
        }

        std::reverse(prefix.begin(), prefix.end());

        return prefix;
    }

    void to_prefix_impl(const Token &token, tokens &prefix, std::stack<Token> &st,
                        size_t &open_bracket_count, size_t &close_bracket_count)
    {
        detail::Types type = token.get_type();
        switch (type)
        {
        case detail::Types::OPERAND:
            prefix.push_back(token);
            break;

        case detail::Types::CLOSE_BRACKET:
            st.push(token);
            close_bracket_count++;
            break;

        case detail::Types::OPEN_BRACKET:
            detail::put_all_elements_before_open_bracket(st, prefix);
            open_bracket_count++;
            break;

        case detail::Types::UNARY_MINUS:
        case detail::Types::ADDITION:
        case detail::Types::SUBTRACTION:
        case detail::Types::MULTIPLICATION:
        case detail::Types::DIVISION:
            detail::put_operator(token, prefix, st);
            break;

        case detail::Types::INCORRECT:
            throw std::invalid_argument("invalid argument!");
            break;
        }

        if (open_bracket_count > close_bracket_count)
            throw std::invalid_argument("invalid bracket!");
    }

    double calculate_impl(const tokens &prefix)
    {
        std::stack<double> st;

        for (int i = prefix.size() - 1; i >= 0; i--)
        {
            if (prefix[i].get_type() == detail::Types::OPERAND)
                st.push(std::stoi(prefix[i].get_value()));

            else if (detail::is_operator(prefix[i].get_type()))
            {
                if (st.empty())
                    throw std::invalid_argument("invalid argument!");

                double first_operand = st.top();
                st.pop();

                if (st.empty())
                    detail::calculate_one_operand(first_operand, prefix[i].get_type(), st);
                else
                {
                    double second_operand = st.top();
                    st.pop();

                    detail::calculate_two_operands(first_operand, second_operand, prefix[i].get_type(), st);
                }
            }
            else
                throw std::invalid_argument("invalid argument!");
        }

        if (st.size() != 1)
            throw std::invalid_argument("invalid argument!");

        return st.top();
    }
}
