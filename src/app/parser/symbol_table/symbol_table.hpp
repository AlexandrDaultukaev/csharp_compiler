#pragma once

#include "grammar/CsharpParser.h"
#include "grammar/CsharpVisitor.h"

#include "ast/ast.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

class ASTProgram;
class ASTFunction;
class ASTVariable;
class ASTFuncCall;
class ASTScope;
class ASTArgs;
class ASTAssign;
class ASTReturn;
class ASTIf;
class ASTFor;
class ASTForOp;
class ASTForCond;
class ASTKw;

struct Properties {
    std::string fragment_type; // VARIABLE, FUNCTION
    std::size_t level=0;
    std::string type="";
};

class VisitorTable : public Visitor {
    using Table = std::map<std::string, Properties>;
private:
  Table table;
	static std::size_t table_level;
public:
  VisitorTable();

	Table& get_table() { return table; }
	void set_symbol(std::string s, Properties p)  { table[s] = p; }
	static void incr_level() { table_level++; }
	static void decr_level() { table_level--; }

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
  void visit(ASTKw &node) override;
};

std::size_t VisitorTable::table_level = 0;