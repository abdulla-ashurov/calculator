#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include "detail.hpp"

class Token
{
    std::string value;
    detail::Types type;

public:
    Token(const char value, const detail::Types type)
        : Token(std::string(1, value), type) {}

    Token(const std::string &value, const detail::Types type)
        : value(value), type(type) {}

    const std::string &get_value() const { return value; }
    detail::Types get_type() const { return type; }
};

#endif
