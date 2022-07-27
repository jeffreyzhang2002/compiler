#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "./../token/Token.h"

class Lexer {

private:
    std::vector<Token> tokens;
    int index = 0;

public:

    Lexer(const std::string& content);

    Lexer(const char* content);

    Lexer(std::ifstream& file);

    static std::vector<Token> tokenize(const std::string& content);

    static std::vector<Token> tokenize(const char* content);

    static std::vector<Token> tokenize(std::ifstream& file);

    std::vector<Token> getTokens();

    Token nextToken();

    bool hasNext();

    void reset();
};