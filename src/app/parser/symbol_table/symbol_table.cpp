#include "ast.hpp"

#include "grammar/CsharpVisitor.h"
#include "symbol_table.hpp"

#include <any>
#include <fstream>
#include <iostream>

//   void visit(ASTProgram &node) override;
//   void visit(ASTFunction &node) override;
//   void visit(ASTVariable &node) override;
//   void visit(ASTFuncCall &node) override;
//   void visit(ASTScope &node) override;
//   void visit(ASTArgs &node) override;
//   void visit(ASTAssign &node) override;
//   void visit(ASTReturn &node) override;
//   void visit(ASTIf &node) override;
//   void visit(ASTFor &node) override;
//   void visit(ASTForCond &node) override;
//   void visit(ASTForOp &node) override;
//   void visit(ASTKw &node) override;



void VisitorTable::visit(ASTProgram& node)
{
    for(auto& child : node.get_children())
    {
        child->accept(*this);
    }
}

void VisitorTable::visit(ASTFunction& node)
{
    Properties p;
    p.level = table_level;
    p.fragment_type = "FUNCTION_DEF";
    p.type = node.return_type();
    table[node.func_name()] = p;
    table_level++;

    for(auto& param : node.get_params())
    {
        param->accept(*this);
    }

    for(auto& scope : node.get_scope()->get_statements())
    {
        scope->accept(*this);
    }

    Properties p_return;
    p.level = table_level;
    if(node.get_return()->is_literal())
    {
        p.fragment_type = "LRETURN_VARIABLE"; //LRETURN -> L(iteral)RETURN
    } 
    else 
    {
        p.fragment_type = "RETURN_VARIABLE";
    }
    p.type = node.get_return()->get_return_type();
    table[node.get_return()->get_return_value()] = p;
    table_level--;
}

void VisitorTable::visit(ASTVariable& node) 
{
    Properties p;
    if(node.get_ctx_type() == "ASSIGN")
    {
        if(node.is_literal())
        {
            p.fragment_type = "LVARIABLE";
        }
        else
        {
            p.fragment_type = "VARIABLE";
        }
        
    }
    else if(node.get_ctx_type() == "PARS")
    {
        if(node.is_literal())
        {
            //error
            throw "Parameter cannot be literal!\n";
            
            //p.fragment_type = "LPVARIABLE";
        }
        else
        {
            p.fragment_type = "PVARIABLE"
        }
         // P(arameter)Variable
    }
    p.level = table_level;
    p.type = node.var_type();
    table[node.var_name()] = p;
}

void VisitorTable::visit(ASTFuncCall& node) 
{
    Properties p;
    p.fragment_type = "FUNCTION_CALL";
    p.level = table_level;
    
}