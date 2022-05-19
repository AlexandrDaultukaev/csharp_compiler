#include "grammar/CsharpLexer.h"
#include "grammar/CsharpParser.h"
#include "grammar/CsharpBaseListener.h"
#include "parser/parser.hpp"
#include "CLI/CLI.hpp"
#include "antlr4-runtime.h"
#include <string>
#include <iostream>
#include <cstdio>

/*
* Запуск examples после сборки:
*  /build/bin$ ./app --dump-tokens -f ../../examples/(nod\substr\test).cs
*/

#define VERSION "0.0.1"

int main (int argc, const char * argv []) {

    CLI::App app;
    std::string filepath;
    std::string xml_file = "";
    bool dump_tokens_key = false;
    bool version_key = false;
    bool dump_ast = false;
    app.add_flag("--dump-tokens", dump_tokens_key, "Dump func");
    app.add_flag("--dump-ast", dump_ast, "Dump ast");
    app.add_flag("--version", version_key, "Version func");
    auto fileflag = app.add_option("-f, --file", filepath, "Filepath");
    app.add_option("-x, --to-xml", xml_file, "Filepath XML");
    fileflag->needs(fileflag);
    CLI11_PARSE(app, argc, argv);
    if(version_key)
    {
        std::cout << VERSION << '\n';
    }
    //parse_test
    // cs_lexer::dump_tokens(filepath, dump_tokens_key);
    // cs_lexer::dump_ast(filepath, xml_file, dump_ast);
    auto parse_result = cs_lang::parse_test(filepath);

    if (!parse_result.m_errors.empty()) {
        cs_lang::dump_errors(parse_result.m_errors);
        return -1;
    }
    
    if (dump_ast || xml_file != "") {
        cs_lang::dump_ast(parse_result.m_program, xml_file, dump_ast);
    }

    if(dump_tokens_key) {
        cs_lang::dump_tokens(filepath);
    }
    
    return 0;
}