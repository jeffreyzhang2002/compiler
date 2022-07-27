#include "./Token.h"

#include <string>
#include <unordered_set>
#include <algorithm>


const std::unordered_set<std::string> Token::keywords = std::unordered_set<std::string> {"byte", "if", "else", "while"};

Token::Token(std::string value, TokenType type) {
    this->value = value;
    this->type = type;
} ;
