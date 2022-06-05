#pragma once

#include "grammar/CsharpParser.h"
#include "grammar/CsharpVisitor.h"

#include "parser/ast/ast.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


struct Properties {
    std::string fragment_type; // VARIABLE, FUNCTION
    std::size_t level=0;
    std::string type="";
};

class VisitorTable : public Visitor {
    using Table = std::map<std::string, Properties>;
    using FunctionProp = std::map<std::string, std::vector<std::pair<std::string, std::string>>>;
private:
  Table table;
  FunctionProp f_props;
	static std::size_t table_level;
  
public:
  VisitorTable() = default;

	Table& get_table() { return table; }
  FunctionProp& get_fprops() { return f_props; }
  void set_fprop(std::string f_name, std::pair<std::string, std::string> p) {
    if(p.first == "" || p.second == "")
    {
      f_props[f_name] = {};
    }
    else {
      f_props[f_name].push_back(p); 
    } 
    
  }
	void set_symbol(std::string s, Properties p)  { table[s] = p; }
	static void incr_level() { table_level++; }
	static void decr_level() { table_level--; }
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

  void print_table() { 
    for(auto it = table.begin(); it != table.end(); it++)
    {
      std::cout << std::setw(5) << it->first << std::setw(10) << it->second.type << ", " << it->second.level << "\n";
    }
    
  }

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
  void visit(ASTKw &node) {};
};
