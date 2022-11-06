#include "catch_amalgamated.hpp"
#include "../include/calculator.hpp"

TEST_CASE("test calc::parse function")
{
    SECTION("should return expected_tokens")
    {
        std::deque<std::string> expressions =
        {
            "1", "23", "345", "678", "9012",
            "-/1+*",
            "1+12", "12-123", "-123*1234", "+1234/-12345",
            "(-1)", "(-23)", "(-345)", "(-9)(012)",
            "Hello!",
            "1234567890"
        };

        std::deque<calc::tokens> expected_tokens =
        {
            {Token("1", detail::Types::OPERAND)},
            {Token("23", detail::Types::OPERAND)},
            {Token("345", detail::Types::OPERAND)},
            {Token("678", detail::Types::OPERAND)},
            {Token("9012", detail::Types::OPERAND)},
            {Token("-", detail::Types::UNARY_MINUS), Token("1", detail::Types::OPERAND), 
            Token("/", detail::Types::DIVISION), Token("1", detail::Types::OPERAND)},
            {Token("1", detail::Types::OPERAND), Token("+", detail::Types::ADDITION), 
            Token("12", detail::Types::OPERAND)},
            {Token("12", detail::Types::OPERAND), Token("-", detail::Types::SUBTRACTION), 
            Token("123", detail::Types::OPERAND)},
            {Token("-", detail::Types::UNARY_MINUS), Token("123", detail::Types::OPERAND), 
            Token("*", detail::Types::MULTIPLICATION), Token("1234", detail::Types::OPERAND)},
            {Token("+", detail::Types::UNARY_PLUS), Token("1234", detail::Types::OPERAND), 
            Token("/", detail::Types::DIVISION), Token("-", detail::Types::UNARY_MINUS), 
            Token("12345", detail::Types::OPERAND)},
            {Token("(", detail::Types::OPEN_BRACKET), Token("-", detail::Types::UNARY_MINUS), 
            Token("1", detail::Types::OPERAND), Token(")", detail::Types::CLOSE_BRACKET)},
            {Token("(", detail::Types::OPEN_BRACKET), Token("-", detail::Types::UNARY_MINUS), 
            Token("23", detail::Types::OPERAND), Token(")", detail::Types::CLOSE_BRACKET)},
            {Token("(", detail::Types::OPEN_BRACKET), Token("-", detail::Types::UNARY_MINUS), 
            Token("345", detail::Types::OPERAND), Token(")", detail::Types::CLOSE_BRACKET)},
            {Token("(", detail::Types::OPEN_BRACKET), Token("-", detail::Types::UNARY_MINUS), 
            Token("9", detail::Types::OPERAND), Token(")", detail::Types::CLOSE_BRACKET),
            Token("(", detail::Types::OPEN_BRACKET), Token("012", detail::Types::OPERAND), 
            Token(")", detail::Types::CLOSE_BRACKET)},
            {Token("H", detail::Types::INCORRECT), Token("e", detail::Types::INCORRECT), 
            Token("l", detail::Types::INCORRECT), Token("l", detail::Types::INCORRECT)},
            {Token("1234567890", detail::Types::OPERAND)}
        };

        for (size_t i = 0; i < expressions.size(); i++)
        {
            calc::tokens received_tokens = calc::parse(expressions[i]);

            REQUIRE(received_tokens.size() == expected_tokens[i].size());
            for (size_t j = 0; j < received_tokens.size(); j++)
            {
                REQUIRE(received_tokens[j].get_value() == expected_tokens[i][j].get_value());
                REQUIRE(received_tokens[j].get_type() == expected_tokens[i][j].get_type());
            }
        }
    }
}
