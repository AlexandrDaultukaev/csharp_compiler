#pragma once

#include "grammar/CsharpLexer.h"
#include <string>
#include "ast/ast.hpp"
#include <vector>
#include "antlr4-runtime.h"

namespace cs_lexer { 
    
        struct token {
        int x;
        int y;
        std::string token_name;
        std::string token_str;
        token(std::size_t loc_x, std::size_t loc_y, std::string tkn_name, std::string tkn) : x(loc_x), y(loc_y), token_name(tkn_name), token_str(tkn) {}
        std::size_t get_x() {return x;}
        std::size_t get_y() {return y;}
        std::string get_token_name() {return token_name;}
        std::string get_token_str() {return token_str;}
    };

        class tokens_array {
        std::vector<token> tokens;
    public:
        token operator[](int index) {return tokens[index];}
        void push_back(std::size_t loc_x, std::size_t loc_y, std::string token_name, std::string token_str)
        {
            tokens.push_back(token(loc_x, loc_y, token_name, token_str));
        }
    };
    tokens_array dump_tokens(std::string filepath, int print_key=1);

void parse_test(std::string filepath, std::string xml);



} // namespace cs_lexer
