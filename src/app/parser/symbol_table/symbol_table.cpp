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

std::size_t VisitorTable::table_level = 0;

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
    incr_level();

    for(auto& param : node.get_params())
    {
        param->accept(*this);
    }

    for(auto& scope : node.get_scope()->get_statements())
    {
        scope->accept(*this);
    }
    if(node.get_return() != nullptr)
    {
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
    }

    decr_level();
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
        //REDEFINITION ERROR
        if(table.contains(node.var_name()) && node.get_frag() == "LEFT_ASSIGN" && node.var_type() != "" && table_level == table[node.var_name()].level)
        {
            
            try {
                throw std::runtime_error("ERROR: Redefinition variable \'" + node.var_name() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
        }
        // Because we gonna keep type variable when we assign new value to variable
        if(table.contains(node.var_name()) && node.get_frag() == "LEFT_ASSIGN" && node.var_type() == "")
        {
            return;
        }

        //UNDEFINED VARIABLE ERROR
        if(!table.contains(node.var_name()) && node.get_frag() == "LEFT_ASSIGN" && node.var_type() == "")
        {
            try {
                throw std::runtime_error("ERROR: Undefined variable \'" + node.var_name() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
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
            p.fragment_type = "PVARIABLE";
        }
         // P(arameter)Variable
    }
    p.level = table_level;
    p.type = node.var_type();
    std::string key = node.var_name();
    if((node.get_frag() == "RIGHT_ASSIGN1" || node.get_frag() == "RIGHT_ASSIGN2") && p.fragment_type[0] != 'L')
    {
        p.type = "ASSIGN_ID";
        key = node.var_name() + "_" + std::to_string(table_level);
        table[key] = p;
    }
    table[key] = p;
}

void VisitorTable::visit(ASTFuncCall& node) 
{
    Properties p;
    p.fragment_type = "FUNCTION_CALL";
    p.level = table_level;
    p.type = "~";
    table[node.func_name()] = p;
    for(auto& arg: node.get_args())
    {
        arg->accept(*this);
    }
}

void VisitorTable::visit(ASTScope& node)
{
    for(auto& child : node.get_statements())
    {
        child->accept(*this);
    }
}

void VisitorTable::visit(ASTArgs& node)
{
    Properties p;
    if(node.is_literal())
    {
        p.fragment_type = "LARGUMENT";
        p.level = table_level;
        p.type = "";
        table[node.get_arg()] = p;
    }
    // else {
    //     p.fragment_type = "ARGUMENT";
    // }
    

}

void VisitorTable::visit(ASTAssign& node)
{
    if(node.get_lvalue() != nullptr)
    {
        node.get_lvalue()->accept(*this);
    }

    if(node.get_rvalue1() != nullptr)
    {
        node.get_rvalue1()->accept(*this);
    }

    if(node.get_rvalue2() != nullptr)
    {
        node.get_rvalue2()->accept(*this);
    }
}

void VisitorTable::visit(ASTReturn& node)
{
    Properties p;
    if(node.is_literal())
    {
        p.fragment_type = "LRETURN";
    }
    else
    {
        p.fragment_type = "RETURN";
    }

    p.level = table_level;
    p.type = node.get_return_type();
    table[node.get_return_value()] = p;
}

void VisitorTable::visit(ASTIf& node)
{
    // Properties p1;
    // p1.fragment_type = "IFVARIABLE";
    // p1.level = table_level;
    // p1.type = node.get_first_type();
    // table[node.get_first()] = p1;

    // Properties p2;
    // p2.fragment_type = "IFVARIABLE";
    // p2.level = table_level;
    // p2.type = node.get_second_type();
    // table[node.get_second()] = p2;
    incr_level();
    node.get_scope()->accept(*this);
    decr_level();
}

void VisitorTable::visit(ASTFor& node)
{
    if(node.get_assing() != nullptr)
    {
        node.get_assing()->accept(*this);
    }

    if(node.get_cond() != nullptr)
    {
        node.get_cond()->accept(*this);
    }

    if(node.get_op() != nullptr)
    {
        node.get_op()->accept(*this);
    }

    incr_level();
    node.get_scope()->accept(*this);
    decr_level();
    if(table[node.get_assing()->get_lvalue()->var_name()].level > table_level)
    {   
         try {
                throw std::runtime_error("ERROR: Redefinition variable \'" + node.get_assing()->get_lvalue()->var_name() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
    }
    
}

void VisitorTable::visit(ASTForCond& node)
{
    Properties p1;
    if(node.is_literal())
    {
        p1.fragment_type = "LFORVARIABLE";
    }
    else
    {
        p1.fragment_type = "FORVARIABLE";
    }
    p1.level = table_level;
    p1.type = "";

    table[node.get_first()] = p1;

    Properties p2;
    p2.fragment_type = "FORVARIABLE";
    p2.level = table_level;
    p2.type = "";
    table[node.get_second()] = p2;
}

void VisitorTable::visit(ASTForOp& node)
{
    
    if(node.get_assign() != nullptr)
    {
        node.get_assign()->accept(*this);
    }
    else
    {
        Properties p1;
        p1.fragment_type = "FOROPVARIABLE";
        p1.level = table_level;
        p1.type = "";
        table[node.get_id()] = p1;
    }
}
