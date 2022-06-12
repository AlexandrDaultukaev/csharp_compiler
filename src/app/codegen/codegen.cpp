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

std::string new_index()
{
    std::string tmp = "%"+std::to_string(index);
    index++;
    return tmp;
}

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

std::string get_llvm_op(std::string op)
{
    auto ret_op = "";
    if(op == "+")
    {
        ret_op = "add";
    } else if(op == "-")
    {
        ret_op = "sub";
    } else if(op == "/")
    {
        ret_op = "sdiv";
    } else if(op == "%")
    {
        ret_op = "srem";
    }

    return ret_op;
}

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
    } // else pass
    if(node.get_rvalue1() != nullptr && node.get_rvalue2() != nullptr)
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
        if(node.get_rvalue1()->is_literal() && !node.get_rvalue2()->is_literal())
        {
            std::cout<<"r1!r2\n";
            std::string tmp_ind_b   = new_index();
            std::string tmp_literal = new_index();
            std::string op          = get_llvm_op(node.get_oper());
            std::string r1_literal  = node.get_rvalue1()->get_var_name();
            std::string r2_type     = name_index[node.get_rvalue2()->get_var_name()].second;
            std::string r2_ind      = name_index[node.get_rvalue2()->get_var_name()].first;
            std::string l_ind       = name_index[node.get_lvalue()->get_var_name()].first;
            stream << tmp_ind_b << " = load " << r2_type << ", " << r2_type << "* " << r2_ind << "\n";
            stream << tmp_literal << " = " << op << " " << r2_type << " " << r1_literal << ", " << tmp_ind_b << "\n";
            stream << "store " << r2_type << " " << tmp_literal << ", " << r2_type << "* " << l_ind << "\n";
        }
        if(!node.get_rvalue1()->is_literal() && node.get_rvalue2()->is_literal())
        {
            std::cout<<"!r1r2\n";
            std::string tmp_ind_b   = new_index();
            std::string tmp_literal = new_index();
            std::string op          = get_llvm_op(node.get_oper());
            std::string r2_literal  = node.get_rvalue2()->get_var_name();
            std::string r1_type     = name_index[node.get_rvalue1()->get_var_name()].second;
            std::string r1_ind      = name_index[node.get_rvalue1()->get_var_name()].first;
            std::string l_ind       = name_index[node.get_lvalue()->get_var_name()].first;
            stream << tmp_ind_b << " = load " << r1_type << ", " << r1_type << "* " << r1_ind << "\n";
            stream << tmp_literal << " = " << op << " " << r1_type << " " << tmp_ind_b << ", " << r2_literal << "\n";
            stream << "store " << r1_type << " " << tmp_literal << ", " << r1_type << "* " << l_ind << "\n";
        }
        if(!node.get_rvalue1()->is_literal() && !node.get_rvalue2()->is_literal())
        {
            std::string tmp_ind_r1 = new_index();
            std::string tmp_ind_r2 = new_index();
            std::string res_r1_r2  = new_index();
            std::string op         = get_llvm_op(node.get_oper());
            std::string r1_type    = name_index[node.get_rvalue1()->get_var_name()].second;
            std::string r2_type    = name_index[node.get_rvalue2()->get_var_name()].second;
            std::string r1_ind     = name_index[node.get_rvalue1()->get_var_name()].first;
            std::string r2_ind     = name_index[node.get_rvalue2()->get_var_name()].first;
            std::string l_ind      = name_index[node.get_lvalue()->get_var_name()].first;
            stream << tmp_ind_r1 << " = load " << r1_type << ", " << r1_type << "* " << r1_ind << "\n";
            stream << tmp_ind_r2 << " = load " << r2_type << ", " << r2_type << "* " << r2_ind << "\n";
            stream << res_r1_r2  << " = " << op << " " << r1_type << " " << tmp_ind_r1 << ", " << tmp_ind_r2 << "\n";
            stream << "store " << r1_type << " " << res_r1_r2 << ", " << r1_type << "* " << l_ind << "\n";
        }
    } else if(node.get_rvalue1() != nullptr)
    {
        if(node.get_rvalue1()->is_literal())
        {
            std::string literal = node.get_rvalue1()->get_var_name();
            std::string l_ind   = name_index[node.get_lvalue()->get_var_name()].first;
            std::string l_type  = name_index[node.get_lvalue()->get_var_name()].second;
            stream << "store " << l_type << " " << literal << ", " << l_type << "* " << l_ind << "\n"; 
        }
        if(!node.get_rvalue1()->is_literal())
        {
            std::string r1_ind  = name_index[node.get_rvalue1()->get_var_name()].first;
            std::string l_ind   = name_index[node.get_lvalue()->get_var_name()].first;
            std::string l_type  = name_index[node.get_lvalue()->get_var_name()].second;
            std::string tmp_ind = new_index();
            stream << tmp_ind << " = load " << l_type << ", " << l_type << "* " << r1_ind << "\n";
            stream << "store " << l_type << " " << tmp_ind << ", " << l_type << "* " << l_ind << "\n"; 
        }
    }
}

void CodeGen::visit(ASTIf &node)
{
    
}