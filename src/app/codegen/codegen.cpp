#include "grammar/CsharpVisitor.h"
#include "codegen.hpp"

#include <any>
#include <fstream>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

std::size_t print_counter = 0;
std::string current_function = "Global";
std::size_t index = 0;
// ID = <%INDEX, TYPE>
std::map<std::string, std::pair<std::string, std::string>> name_index;

std::string get_llvm_type(std::string p)
{
    auto ptype = "";
    if(p == "int" || p == "NUMBER")
    {
        ptype = "i32";
    } else if(p == "char" || p == "CHAR")
    {
        ptype = "i8";
    } else if(p == "float" || p == "FLOAT_NUMBER")
    {
        ptype = "float";
    }
    return ptype;
}

// std::string get_llvm_op(std::string op)
// {
//     auto ret_op = "";
//     if(op == "+")
//     {
//         ptype = "i32";
//     } else if(p == "char")
//     {
//         ptype = "i8";
//     } else if(p == "float")
//     {
//         ptype = "float";
//     }
//     return ptype;
// }

void CodeGen::visit(ASTProgram &node)
{
    stream << "source_filename = \"" << filepath << "\"\n";
    stream << "target datalayout = \"e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128\"\n";
    stream << "target triple = \"x86_64-pc-linux-gnu\"\n";
    for(auto& child : node.get_children())
    {
        child->accept(*this);
    }
    stream << "attributes #0 = { noinline nounwind optnone uwtable \"frame-pointer\"=\"all\" \"min-legal-vector-width\"=\"0\" \"no-trapping-math\"=\"true\" \"stack-protector-buffer-size\"=\"8\" \"target-cpu\"=\"x86-64\" \"target-features\"=\"+cx8,+fxsr,+mmx,+sse,+sse2,+x87\" \"tune-cpu\"=\"generic\" }\n";
    stream.close();
}

void CodeGen::visit(ASTFunction &node)
{
    stream << "define dso_local i32 @" << node.func_name();
//PARAMS
    stream << "(";
    for(auto& p : node.get_param_from_vector())
    {
        auto ptype = get_llvm_type(p.second);
        stream << ptype << " noundef %" << index;
        name_index[p.first] = std::make_pair("%"+index, ptype);
        index++;
        if(index < node.get_param_from_vector().size()-1)
        {
            stream << ", ";
        }
    }
    index++;
    stream << ") ";
    stream << "#0 {\n";
//SCOPE
    node.get_scope()->accept(*this);
// RETURN
    std::string tmp_return = "%"+std::to_string(index);
    index++;
    
    
    std::string ret_type;
    
    if(!name_index.contains(node.get_return()->get_return_value()))
    {
        
        
        ret_type = node.get_return()->get_return_type();
        ret_type = get_llvm_type(ret_type);
        stream << "ret ";
        stream << ret_type << " " << node.get_return()->get_return_value() << '\n';
    } else {
        ret_type = name_index[node.get_return()->get_return_value()].second;
        auto ind = name_index[node.get_return()->get_return_value()].first;
        stream << tmp_return << " = load " << ret_type << ", " << ret_type << "* " << ind << "\n";
        
        stream << "ret ";
        
        stream << ret_type << " " << tmp_return << '\n';
    }
    
    
    stream << "}\n";
}

void CodeGen::visit(ASTScope &node)
{
    for(auto& s : node.get_statements())
    {
        s->accept(*this);
    }
}

void CodeGen::visit(ASTAssign &node)
{
    if(node.get_lvalue()->get_var_type() != "")
    {
        auto type = get_llvm_type(node.get_lvalue()->get_var_type());
        stream << "%" << index << " = alloca " << type << "\n";
        name_index[node.get_lvalue()->get_var_name()] = std::make_pair("%"+std::to_string(index), type);
        index++;
    }
    if(node.get_rvalue1() != nullptr && node.get_rvalue1() != nullptr)
    {
        std::string type = get_llvm_type(node.get_rvalue1()->get_var_type());
        std::string op   = node.get_oper();
        float resf = 0.0f;
        int resi = 0;
        if(node.get_rvalue1()->is_literal() && node.get_rvalue2()->is_literal())
        {
            if(type == "float")
            {
                float r1 = std::stof(node.get_rvalue1()->get_var_name());
                float r2 = std::stof(node.get_rvalue2()->get_var_name());
                if(op == "+") { resf = r1 + r2; } 
                else if(op == "-") { resf = r1 - r2; }
                else if(op == "/")
                {
                    if(r2 == 0.0f)
                    {
                        std::cerr << "ERROR: Divide by zero\n";
                        throw;
                    }
                    resf = r1 / r2;
                } else if(op == "%") { std::cerr << "ERROR: invalid operands to binary expression\n"; throw; }
            } else if(type == "i32")
            {
                int r1 = std::stoi(node.get_rvalue1()->get_var_name());
                int r2 = std::stoi(node.get_rvalue2()->get_var_name());
                if(op == "+") { resi = r1 + r2; } 
                else if(op == "-") { resi = r1 - r2; }
                else if(op == "/")
                {
                    if(r2 == 0.0f)
                    {
                        std::cerr << "ERROR: Divide by zero\n";
                        throw;
                    }
                    resi = r1 / r2;
                } else if(op == "%") { resi = r1 % r2; }
            }

            stream << "store " << type << " ";
            if(type == "i32")
            {
                stream << resi << ", ";
            } else if(type == "float")
            {
                stream << resf << ", ";
            }
            stream << type << "* " << name_index[node.get_lvalue()->get_var_name()].first << "\n";
        }
    }
}