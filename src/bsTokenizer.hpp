#pragma once
#include <iostream>
#include <vector>
namespace BuildScript
{
    enum class TokenType
    {
        Unrecognised,
        Identifier,
        Number,
        String,
        OpenParam,
        CloseParam,
        OpenScope,
        CloseScope,
        Multiply,
        Divide,
        Add,
        Subtract,
        Semicolon,
        Primitive,
        Comma,
        FullStop,
        Assign,
        Function,
        Return
    };

    struct Token
    {
        unsigned long long line;
        std::string value;
        TokenType type;
    };

    std::vector<Token>* Tokenize(std::string source);
}