#include "grammar/CsharpLexer.h"
#include "grammar/CsharpParser.h"
#include "parser/parser.hpp"
#include "ast/ast.hpp"
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

void parse_test(std::string filepath) {
    std::ifstream stream(filepath);

    if (!stream.is_open()) {
        std::cerr << "Error: FileNotFound\n";

        return;
    }

    antlr4::ANTLRInputStream input(stream);
    CsharpLexer lexer(&input);

    antlr4::CommonTokenStream tokens(&lexer);
    CsharpParser parser(&tokens);

    antlrcpp::Any program = parser.program();

    VisitorInitialiser visitor_init(program);
    VisitorTraverse visitor_print(std::cout);

    ASTNode* ast = new ASTProgram;

    ast->accept(visitor_init);
    ast->accept(visitor_print);
    delete ast;
}

}
