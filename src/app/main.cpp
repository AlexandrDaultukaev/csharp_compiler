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
*  /build/bin$ ./app --dump-tokens -f ../../examples/(min\nod\substr).cs
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
    //TODO: --dump-ast
    auto fileflag = app.add_option("-f, --file", filepath, "Filepath");
    app.add_option("-x, --to-xml", xml_file, "Filepath XML");
    fileflag->needs(fileflag);
    CLI11_PARSE(app, argc, argv);
    if(version_key)
    {
        std::cout << VERSION << '\n';
    }
    // cs_lexer::dump_tokens(filepath, dump_tokens_key);
    bool delete_tmp = false;
    if(xml_file == "" && dump_ast)
    {
        delete_tmp = true;
        std::cout << "\nHERE!\n";
        xml_file = "../../examples/tmp.xml";
    }
    cs_lexer::parse_test(filepath, xml_file);
    
    // To be modified
    if(dump_ast)
    {
        
        std::string line;
        // if(xml_file == "")
        // {
        //     delete_tmp = true;
            
        //     std::ofstream cf(xml_file);
        //     cf.open(xml_file);
        // }
        std::ifstream myfile(xml_file);
        
        if (myfile.is_open())
        {
            
            while ( std::getline (myfile,line) )
            {
                std::cout << line << '\n';
            }
            myfile.close();
        }
        if(delete_tmp) { std::remove("../../examples/tmp.xml");}
    }
    return 0;
}