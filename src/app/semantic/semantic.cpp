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
        if(table.contains(str+std::to_string(i)))
        {
            break;
        }
    }
    return i;
}

// int main(int i) {}
void SemanticVisitor::visit(ASTFunction& node)
{
     
    if(node.get_return() != nullptr)
    {
        int lvl = get_level(node.get_return()->get_return_value()+"_return_");
        std::string ret_type = table[node.get_return()->get_return_value()+"_return_"+std::to_string(lvl)].type;
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
    // std::vector<std::pair<std::string, std::string>> pars;
    // for(auto const& [key, prop] : table)
    // {
    //     if(prop.fragment_type == std::string("PVARIABLE_"+node.func_name()))
    //     {
    //         pars.push_back(std::make_pair(key, prop.type));
    //     }
    // }
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
void SemanticVisitor::visit(ASTScope& node) {}
void SemanticVisitor::visit(ASTArgs& node) {}
void SemanticVisitor::visit(ASTAssign& node) {}
void SemanticVisitor::visit(ASTReturn& node) {}
void SemanticVisitor::visit(ASTIf& node) {}
void SemanticVisitor::visit(ASTFor& node) {}
void SemanticVisitor::visit(ASTForCond& node) {}
void SemanticVisitor::visit(ASTForOp& node) {}
void SemanticVisitor::visit(ASTKw& node) {}

