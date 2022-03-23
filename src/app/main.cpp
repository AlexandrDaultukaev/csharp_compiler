#include "grammar/CsharpLexer.h"
#include "lexer/lexer.hpp"
#include "CLI/CLI.hpp"
#include "antlr4-runtime.h"
#include <string>
#include <iostream>

/*
* Запуск examples после сборки:
*  /build/bin$ ./app --dump-tokens ../../examples/(min\nod\substr).cs
*/

int main (int argc, const char * argv []) {
    CLI::App app;
    std::string filepath;
    app.add_option("--dump-tokens", filepath, "Dump func");
    CLI11_PARSE(app, argc, argv);
    cs_lexer::dump_tokens(filepath);
    return 0;
}