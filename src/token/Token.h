#pragma once

#include <string>
#include <unordered_set>

enum class TokenType {
    Identifier,
    Whitespace,
    Operator,
    Keyword,
};



class Token {

public:

    const static std::unordered_set<std::string> keywords;


    std::string value;
    TokenType type;

    Token(std::string value, TokenType type);
};
