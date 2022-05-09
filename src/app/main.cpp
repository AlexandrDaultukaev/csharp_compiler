#include "grammar/CsharpLexer.h"
#include "grammar/CsharpParser.h"
#include "grammar/CsharpBaseListener.h"
#include "parser/parser.hpp"
#include "CLI/CLI.hpp"
#include "antlr4-runtime.h"
#include <string>
#include <iostream>

/*
* Запуск examples после сборки:
*  /build/bin$ ./app --dump-tokens -f ../../examples/(min\nod\substr).cs
*/

#define VERSION "0.0.1"

int main (int argc, const char * argv []) {

    CLI::App app;
    std::string filepath;
    bool dump_tokens_key = false;
    bool version_key = false;
    app.add_flag("--dump-tokens", dump_tokens_key, "Dump func");
    app.add_flag("--version", version_key, "Version func");
    //TODO: --dump-ast
    auto fileflag = app.add_option("-f, --file", filepath, "Filepath");
    fileflag->needs(fileflag);
    CLI11_PARSE(app, argc, argv);
    if(version_key)
    {
        std::cout << VERSION << '\n';
    }
    // cs_lexer::dump_tokens(filepath, dump_tokens_key);

    cs_lexer::parse_test(filepath);
    
    return 0;
}