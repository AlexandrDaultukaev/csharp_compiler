#include "grammar/CsharpLexer.h"
#include "grammar/CsharpParser.h"
#include "grammar/CsharpBaseListener.h"
#include "parser/parser.hpp"
#include "optimizer/optimizer.hpp"
#include "semantic/semantic.hpp"
#include "codegen/codegen.hpp"
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
    std::string fileout;
    std::string xml_file = "";
    bool dump_tokens_key = false;
    bool version_key = false;
    bool dump_ast = false;
    bool dump_tab = false;
    bool dump_sem = false;
    bool optim1 = false;
    bool wall = false;
    app.add_flag("--dump-tokens", dump_tokens_key, "Dump func");
    app.add_flag("--dump-ast", dump_ast, "Dump ast");
    app.add_flag("--dump-table", dump_tab, "Dump table");
    app.add_flag("--dump-semantic", dump_sem, "Dump semantic report");
    app.add_flag("--version", version_key, "Version func");
    app.add_flag("--opt", optim1, "Unable optimization");
    app.add_flag("--wall", wall, "Warnings info");
    auto fileflag = app.add_option("-f, --file", filepath, "Filepath");
    auto fileflagout = app.add_option("-o, --out", fileout, "Out file");
    app.add_option("-x, --to-xml", xml_file, "Filepath XML");
    fileflag->needs(fileflag);
    fileflagout->needs(fileflagout);
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
    VisitorTable visitor;
    parse_result.m_program->accept(visitor);


    if (dump_tab) {
        cs_lang::dump_table(visitor);
    }

    if(dump_tokens_key) {
        cs_lang::dump_tokens(filepath);
    }
    SemanticVisitor semantic_visitor(visitor.get_table(), visitor.get_fprops(), visitor.get_indexer());
    parse_result.m_program->accept(semantic_visitor);
    if(dump_sem)
    {
        cs_lang::print_semantic_report(semantic_visitor);
    }
    if(optim1 || wall)
    {
        OptimizerVisitor visitor_optimizer(visitor.get_table(), visitor.get_indexer(), wall, optim1);
        parse_result.m_program->accept(visitor_optimizer);
    }
    if (dump_ast || xml_file != "") {
        cs_lang::dump_ast(parse_result.m_program, xml_file, dump_ast);
    }
    std::ofstream stream(fileout);
    CodeGen code_generator(stream, filepath, fileout);
    parse_result.m_program->accept(code_generator);
    stream.close();
    return 0;
}