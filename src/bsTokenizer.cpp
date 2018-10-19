#include "bsTokenizer.hpp"

namespace BuildScript
{
    std::string tokenizeString(
        std::string source, uint64_t* line, uint64_t* index
    )
    {
        std::string out;
        *index += 1;
        while(source[*index] != '\"')
        {
            if(source[*index] == '\\')
            {
                *index += 1;
                switch(source[*index])
                {
                    case 'n':
                        out += '\n';
                    break;
                    case 't':
                        out += '\t';
                    break;
                    case '\"':
                        out += '\"';
                    break;
                    case '\\':
                        out += '\\';
                    break;
                    case 'v':
                        out += '\v';
                    break;
                    case 'r':
                        out += '\r';
                    break;
                    case 'f':
                        out += '\f';
                    break;
                    case '0':
                        out += '\0';
                    break;
                    default:
                        printf("Incorrect string formatting on line %i\n",line);
                    break;
                }
                *index += 1;
                continue;
            }
            if(source[*index] == '\n')
            {
                *line += 1;
            }
            out += source[*index];
            *index += 1;
        }
        return out;
    }
    std::vector<Token>* Tokenize(std::string source)
    {
        std::vector<Token>* tokens = new std::vector<Token>();
        uint64_t line = 1;

        for(uint64_t i = 0; i < source.length(); i++)
        {
            //Skip empty line
            if(source[i] == '\n') { line++; continue; }

            //Handle one-line comments
            if(source[i] == '/' && source[i+1] == '/')
            {
                while(source[i] != '\n') { i++; }
                i--;
                continue;
            }

            //Handle multi-line comments
            if(source[i] == '/' && source[i+1] == '*')
            {
                while(!(source[i] == '*' && source[i+1] == '/'))
                {
                    if(source[i] == '\n') { line++; }
                    i++;
                }
                i++;
                continue;
            }

            //Predefine token for the switch statement
            Token token;
            token.type = TokenType::Unrecognised;
            token.line = line;

            switch(source[i])
            {
                case ';':
                    token.type = TokenType::Semicolon;
                    token.value = ";";
                break;
                case ',':
                    token.type = TokenType::Comma;
                    token.value = ",";
                break;
                case '=':
                    token.type = TokenType::Assign;
                    token.value = "=";
                break;
                case '+':
                    token.type = TokenType::Add;
                    token.value = "+";
                break;
                case '-':
                    token.type = TokenType::Subtract;
                    token.value = "-";
                break;
                case '*':
                    token.type = TokenType::Multiply;
                    token.value = "*";
                break;
                case '/':
                    token.type = TokenType::Divide;
                    token.value = "/";
                break;
                case '(':
                    token.type = TokenType::OpenParam;
                    token.value = "(";
                break;
                case ')':
                    token.type = TokenType::CloseParam;
                    token.value = ")";
                break;
                case '{':
                    token.type = TokenType::OpenScope;
                    token.value = "{";
                break;
                case '}':
                    token.type = TokenType::CloseScope;
                    token.value = "}";
                break;
                case '\"':
                    token.type = TokenType::String;
                    token.value = tokenizeString(source, &line, &i);
                break;
                default:
                    if(isalpha(source[i]))
                    {
                        while(isalpha(source[i]) || isdigit(source[i]))
                        {
                            token.value += source[i];
                            i++;
                        }
                        i--;
                        if(token.value == "func")
                        {
                            token.type = TokenType::Function;
                        }
                        else if(token.value == "return")
                        {
                            token.type = TokenType::Return;
                        }
                        else if(token.value == "int8")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "uint8")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "int16")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "uint16")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "int32")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "uint32")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "int64")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "uint64")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "float32")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "float64")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else if(token.value == "string")
                        {
                            token.type = TokenType::Primitive;
                        }
                        else
                        {
                            token.type = TokenType::Identifier;
                        }
                    }
                    else if(isdigit(source[i]))
                    {
                        while(isdigit(source[i]) || source[i] == '.')
                        {
                            token.value += source[i];
                            i++;
                        }
                        i--;
                        token.type = TokenType::Number;
                    }
                    else
                    {
                        continue;
                    }
                break;
            }
        }

        return tokens;
    }
}