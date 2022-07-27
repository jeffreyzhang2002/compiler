#include "./Lexer.h"

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <sstream>
#include <unordered_set>
#include <algorithm>



enum class State {
    Identifier = 0,
    Whitespace = 1,
    Operator = 2
};

State transition(std::string& current, char character, std::vector<Token>& tokens, State state) {

    TokenType type;

    switch(state) {
        case State::Identifier: {

            std::transform(current.begin(), current.end(), current.begin(), [](unsigned char c) {return std::tolower(c); });

            if(Token::keywords.find(current) != Token::keywords.end()) {
                type = TokenType::Keyword;
            } else {
                type = TokenType::Identifier;
            }

            break;
        }

        case State::Operator: {
            type = TokenType::Operator;
            break;
        }

         case State::Whitespace: {
            type = TokenType::Whitespace;
            current = " ";
            break;
         }
    }
    tokens.push_back( Token(current, type) );

    current = std::string(1, character);

    if(isalnum(character)) 
        return State::Identifier;
    else if(ispunct(character))
        return State::Operator;
    else if(isspace(character))
        return State::Whitespace;
    else
        throw std::runtime_error("Error!");
}

std::vector<Token> _tokenize(std::istream& input) { 

    char character = 0;

    State state = State::Whitespace;
    std::string current = "";
    std::vector<Token> tokens;

    while(input.get(character)) {
        switch(state) {
            case State::Identifier:
            {
                if(isalnum(character)) {
                    current += character;
                } else {
                    state = transition(current, character, tokens, state);                
                }
                break;
            }
            case State::Operator:
            {
                if(ispunct(character)) {
                    current += character;
                } else {
                    state = transition(current, character, tokens, state);
                }
                break;
            }
            case State::Whitespace:
            {
                if(!isspace(character)) {
                    state = transition(current, character, tokens, state);
                }
                break;
            }
        }
    }
    return tokens;
}


//----------------------------------------
// Implementating Lexer Class Methods
//----------------------------------------

Lexer::Lexer(const std::string & content) {
    this->tokens = tokenize(content);        
}

Lexer::Lexer(const char* content) : Lexer(std::string(content)) {}

Lexer::Lexer(std::ifstream& file) {
    this->tokens = tokenize(file);
}

std::vector<Token> Lexer::tokenize(const char* content) {
    return tokenize(std::string(content));
}

std::vector<Token> Lexer::tokenize(const std::string& content) {
    return _tokenize(std::stringstream(content));
}

std::vector<Token> Lexer::tokenize(std::ifstream& file) {
    
    if(!file.is_open()) {
        throw std::runtime_error("Unable to Open File");
    }

    return _tokenize(file);
}

std::vector<Token> Lexer::getTokens() {
    return this->tokens;
}

Token Lexer::nextToken() {
    if(this->index >= this->tokens.size())
        throw std::runtime_error("No more tokens!");

    return this->tokens[this->index++];
}

bool Lexer::hasNext() {
    return this->index < this->tokens.size();
}

void Lexer::reset() {
    this->index = 0;
}
