#include "grammar/CsharpVisitor.h"
#include "semantic.hpp"

#include <any>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

// ASTProgram ASTFunction
// ASTVariable ASTFuncCall
// ASTScope ASTArgs
// ASTAssign ASTReturn
// ASTIf ASTFor
// ASTForCond ASTForOp
// ASTKw

std::string current_function_scope = "Global";

namespace cs_lang {
  void print_semantic_report(SemanticVisitor sv) 
  {
      if(!sv.get_errors().empty())
      {
        for(auto& i : sv.get_errors())
        {
          std::cout << "Semantic error: " << i;
        }
      } else {
          std::cout << "Semantic errors not found\n";
      }
  }
}

std::string SemanticVisitor::get_literal_type(std::string literal)
{
    if(table[get_fname_index(current_function_scope)][literal].type == "NUMBER")
    {
        return std::string("int");
    }
    if(table[get_fname_index(current_function_scope)][literal].type == "FLOAT_NUMBER")
    {
        return std::string("float");
    }
    if(table[get_fname_index(current_function_scope)][literal].type == "CHAR")
    {
        return std::string("char");
    }
    if(table[get_fname_index(current_function_scope)][literal].type == "STRING" || table[get_fname_index(current_function_scope)][literal].type == "TEXT")
    {
        return std::string("string");
    }
    return std::string("unknown");
}


void SemanticVisitor::visit(ASTProgram& node)
{
    for(auto& child : node.get_children())
    {
        child->accept(*this);
    }
}

int SemanticVisitor::get_level(std::string str)
{
    int i = 0;
    for(; i < 100; i++)
    {
        if(table[get_fname_index(current_function_scope)].contains(str+std::to_string(i)))
        {
            break;
        }
    }
    return i;
}

// int main(int i) {}
void SemanticVisitor::visit(ASTFunction& node)
{
    current_function_scope = node.func_name();
    if(node.get_return() != nullptr)
    {
        int lvl = get_level(node.get_return()->get_return_value()+"_return_");
        std::string ret_type = table[get_fname_index(current_function_scope)][node.get_return()->get_return_value()+"_return_"+std::to_string(lvl)].type;
        std::transform(ret_type.begin(), ret_type.end(), ret_type.begin(),
            [](unsigned char c){ return std::tolower(c); });
        if(ret_type != node.return_type())
        {
            errors.emplace_back(std::string("Cannot convert type \'" + ret_type + "\' to \'" + node.return_type() + "\'\n"));
        }
    }


    for(auto& child : node.get_scope()->get_statements())
    {
        child->accept(*this);
    }
}

void SemanticVisitor::visit(ASTVariable& node) {}
void SemanticVisitor::visit(ASTFuncCall& node) {
    if(!f_props.contains(node.func_name()))
    {
        try {
            throw std::runtime_error("ERROR: Undefined function \'" + node.func_name() + "\'");
        } catch(std::runtime_error& e)
        {
            std::cerr << e.what() << "\n";
            exit(EXIT_FAILURE);
        }
    }
    int i = 0;
    if(node.get_args_from_vector().size() != f_props[node.func_name()].size())
    {
        try {
            throw std::runtime_error("ERROR: Incorrect number of arguments when calling a function \'" + node.func_name() + "\'\n");
        } catch(std::runtime_error& e)
        {
            std::cerr << e.what() << "\n";
            exit(EXIT_FAILURE);
        }
        
    }
    for(auto& arg : node.get_args_from_vector())
    {
        
        if(arg.second != f_props[node.func_name()][i].second)
        {
            errors.emplace_back(std::string("Cannot convert type \'" + arg.second + "\' to \'" + f_props[node.func_name()][i].second + "\'\n"));
        }
        i++;
    }
}
void SemanticVisitor::visit(ASTScope& node) {
    for(auto& child : node.get_statements())
    {
        child->accept(*this);
    }
}
void SemanticVisitor::visit(ASTArgs& node) {}
void SemanticVisitor::visit(ASTAssign& node) {
    bool is_def = node.get_lvalue()->get_var_type() == ""? false : true;
    std::string lhs_type = "";
    if(table[get_fname_index(current_function_scope)].contains(node.get_lvalue()->get_var_name()))
    {
        lhs_type = table[get_fname_index(current_function_scope)][node.get_lvalue()->get_var_name()].type;
    } else if(table[0].contains(node.get_lvalue()->get_var_name()))
    {
        lhs_type = table[0][node.get_lvalue()->get_var_name()].type;
    }
    if(node.get_rvalue1() != nullptr)
    {
        std::string type_r1 = "";
        std::string type_r2 = "";
        if(node.get_rvalue1()->is_literal())
        {
            type_r1 = get_literal_type(node.get_rvalue1()->get_var_name());
        }
        else
        {
            type_r1 = table[get_fname_index(current_function_scope)][node.get_rvalue1()->get_var_name()].type;
            //CHECK: 'string str = str;'
            if(is_def && node.get_rvalue1()->get_var_name() == node.get_lvalue()->get_var_name())
            {
                errors.emplace_back(std::string("Use of unassigned local variable \'" + node.get_lvalue()->get_var_name() + "\'\n"));
            }
        }
        if(lhs_type == type_r1)
        {
            if(node.get_rvalue2() != nullptr)
            {
                if(node.get_rvalue2()->is_literal())
                {
                    type_r2 = get_literal_type(node.get_rvalue2()->get_var_name());
                }
                else
                {
                    type_r2 = table[get_fname_index(current_function_scope)][node.get_rvalue2()->get_var_name()].type;
                    //CHECK: 'string str = "10" + str;'
                    if(is_def && node.get_rvalue2()->get_var_name() == node.get_lvalue()->get_var_name())
                    {
                        errors.emplace_back(std::string("Use of unassigned local variable \'" + node.get_lvalue()->get_var_name() + "\'\n"));
                    }
                }
                if(lhs_type != type_r2)
                {
                    errors.emplace_back(std::string("Cannot convert type \'" + lhs_type + "\' to \'" + type_r2 + "\' in assign-statement\n"));
                }
            }
        } else {
            errors.emplace_back(std::string("Cannot convert type \'" + lhs_type + "\' to \'" + type_r1 + "\' in assign-statement\n"));
        }
    }
    
}
void SemanticVisitor::visit(ASTReturn& node) {}
void SemanticVisitor::visit(ASTIf& node) {
    std::string type_second_operand = "";
    if(node.get_second() != "")
    {
        if(node.is_literal())
        {
            type_second_operand = get_literal_type(node.get_second());
        } else {
            type_second_operand = table[get_fname_index(current_function_scope)][node.get_second()].type;
        }

        if(table[get_fname_index(current_function_scope)][node.get_first()].type != type_second_operand)
        {
            errors.emplace_back(std::string("Operator \'" + node.get_op() + "\' cannot be applied to operands of type \'"+ table[get_fname_index(current_function_scope)][node.get_first()].type + "\' to \'" + type_second_operand + "\' in if-statement\n"));
        }
    } else {
        errors.emplace_back(std::string("Cannot implicitly convert type \'" + node.get_second_type() + "\' to \'bool\'"));
    }
    node.get_scope()->accept(*this);
}
void SemanticVisitor::visit(ASTFor& node) {
    node.get_assing()->accept(*this);
    node.get_cond()->accept(*this);
    node.get_op()->accept(*this);
    node.get_scope()->accept(*this);
}
void SemanticVisitor::visit(ASTForCond& node) {
    std::string type_second_operand = "";
    if(node.get_second() != "")
    {
        if(node.is_literal())
        {
            type_second_operand = get_literal_type(node.get_second());
        } else {
            type_second_operand = table[get_fname_index(current_function_scope)][node.get_second()].type;
        }
    } else {
        errors.emplace_back(std::string("Cannot implicitly convert type \'" + table[get_fname_index(current_function_scope)][node.get_second()].type + "\' to \'bool\'\n"));
    }
    if(table[get_fname_index(current_function_scope)][node.get_first()].type != "int" && table[get_fname_index(current_function_scope)][node.get_first()].type != "float")
    {
        errors.emplace_back(std::string("Cannot iterate by type \'" + table[get_fname_index(current_function_scope)][node.get_first()].type + "\'\n"));
    }
    
}
void SemanticVisitor::visit(ASTForOp& node) {
    if(node.get_assign() != nullptr)
    {
        node.get_assign()->accept(*this);
    } else {
        if(table[get_fname_index(current_function_scope)][node.get_id()].type != "int" && table[get_fname_index(current_function_scope)][node.get_id()].type != "float")
        {
            errors.emplace_back(std::string("Operator \'" + node.get_unary_op() + "\' cannot be applied to operand of type \'"+ table[get_fname_index(current_function_scope)][node.get_id()].type + "\' in for-statement\n"));
        }
    }
}
void SemanticVisitor::visit(ASTKw& node) {}

