#include "grammar/CsharpLexer.h"
#include "lexer/lexer.hpp"
#include "CLI/CLI.hpp"
#include "antlr4-runtime.h"
#include <string>
#include <iostream>


namespace cs_lexer { 
    tokens_array dump_tokens(std::string filepath, int print_key) {
        std::ifstream stream;
        tokens_array tokens;
        stream.open(filepath);
        if (stream.is_open() == false) {
            std::cerr << "Error: " << filepath
                << ": No such file or directory\n";

            return tokens;
        }

        antlr4::ANTLRInputStream input(stream);

        CsharpLexer lexer(&input);
        
        auto vocabulary = lexer.getVocabulary();
        while (true) {
            auto tkn = lexer.nextToken();
            if (tkn -> getText() == "<EOF>") {
                break;
            }
            if(print_key) {
                std::cout << "Loc=<"
                << tkn -> getLine() << ", "
                << tkn -> getCharPositionInLine() << "> "
                << vocabulary.getSymbolicName(tkn -> getType())
                << " \'" << tkn -> getText() << "\'\n";
            }
            tokens.push_back(tkn->getLine(), tkn->getCharPositionInLine(), vocabulary.getSymbolicName(tkn->getType()), tkn->getText());
        }
        return tokens;
    }
}
