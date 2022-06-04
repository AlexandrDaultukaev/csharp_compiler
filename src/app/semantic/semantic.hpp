#pragma once

#include "grammar/CsharpParser.h"
#include "grammar/CsharpVisitor.h"

#include "parser/ast/ast.hpp"

#include <fstream>
#include <string>
#include <vector>

class SemanticVisitor : public Visitor {
  private:
    
  public:
    
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