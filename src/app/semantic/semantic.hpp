#pragma once

#include "grammar/CsharpParser.h"
#include "grammar/CsharpVisitor.h"
#include "parser/symbol_table/symbol_table.hpp"
#include "parser/ast/ast.hpp"

#include <fstream>
#include <string>
#include <vector>

class SemanticVisitor : public Visitor {
  using Table = std::map<std::string, Properties>;
  using FunctionProp = std::map<std::string, std::vector<std::pair<std::string, std::string>>>;
  private:
    std::vector<std::string> errors;
    Table table;
    FunctionProp f_props;
  public:
    SemanticVisitor(Table t, FunctionProp p) { table = t; f_props = p; }
    void append_error(std::string s) { errors.emplace_back(s); }
    std::vector<std::string> get_errors() { return errors; }
    int get_level(std::string str);
  void visit(ASTProgram &node) override;
  void visit(ASTFunction &node) override;
  void visit(ASTVariable &node) override;
  void visit(ASTFuncCall &node) override;
  void visit(ASTScope &node) override;
  void visit(ASTArgs &node) override;
  void visit(ASTAssign &node) override;
  void visit(ASTReturn &node) override;
  void visit(ASTIf &node) override;
  void visit(ASTFor &node) override;
  void visit(ASTForCond &node) override;
  void visit(ASTForOp &node) override;
  void visit(ASTKw &node) override;
  std::string get_literal_type(std::string literal)
  {
    if(table[literal].type == "NUMBER")
    {
      return std::string("int");
    }
    if(table[literal].type == "FLOAT_NUMBER")
    {
      return std::string("float");
    }
    if(table[literal].type == "CHAR")
    {
      return std::string("char");
    }
    if(table[literal].type == "STRING" || table[literal].type == "TEXT")
    {
      return std::string("string");
    }
    return std::string("unknown");
  }
};

namespace cs_lang {
  void print_semantic_report(SemanticVisitor sv);
}