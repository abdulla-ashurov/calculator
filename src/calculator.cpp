#include <stack>
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
}
