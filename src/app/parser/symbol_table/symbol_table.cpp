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
std::size_t VisitorTable::vector_num = 0;
std::string current_function = "Global";

void VisitorTable::visit(ASTProgram& node)
{
    set_fname_index(current_function);
    std::map<std::string, Properties> global;
    table.push_back(global);
    for(auto& child : node.get_children())
    {
        child->accept(*this);
    }
}

void VisitorTable::visit(ASTFunction& node)
{
    Properties p;
    p.level = table_level;
    current_function = node.func_name();
    std::map<std::string, Properties> func;
    table.push_back(func);
    set_fname_index(current_function);
    p.type = node.return_type();
    
    incr_level();
    for(auto& param : node.get_params())
    {

        param->accept(*this);

        node.append_param_to_vector(param->get_var_name(), param->get_var_type());
    }

    set_fprop(node.func_name(), std::make_pair("", ""));
    for(auto& param : node.get_param_from_vector())
    {

        set_fprop(node.func_name(), param);

        //std::cout << "Params: " << param.first << " :: " << param.second << "\n";
    }
    p.fragment_type = "FUNCTION_DEF";

    table[get_fname_index(current_function)][node.func_name()] = p;
    
    for(auto& scope : node.get_scope()->get_statements())
    {
        scope->accept(*this);
    }
    if(node.get_return() != nullptr)
    {
        // Properties p_return;
        p.level = table_level;
        if(node.get_return()->is_literal())
        {
            p.fragment_type = "LRETURN_VARIABLE"; //LRETURN -> L(iteral)RETURN
        } 
        else 
        {
            p.fragment_type = "RETURN_VARIABLE";
        }
        auto return_type = node.get_return()->get_return_type();
        if(return_type == "ID")
        {
            if(!table[get_fname_index(current_function)].contains(node.get_return()->get_return_value()))
            {
                try {
                    throw std::runtime_error("ERROR: Undifined variable \'" + node.get_return()->get_return_value() + "\' in return-statement");
                } catch(std::runtime_error& e)
                {
                    std::cerr << e.what() << "\n";
                    exit(EXIT_FAILURE);
                }
            } else {
                p.type = table[get_fname_index(current_function)][node.get_return()->get_return_value()].type;
            }
        }
        else {
            p.type = node.get_return()->get_return_type();
        }
        table[get_fname_index(current_function)][node.get_return()->get_return_value()+"_"+"return"+"_"+std::to_string(table_level)] = p;
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
        if(table[get_fname_index(current_function)].contains(node.get_var_name()) && node.get_frag() == "LEFT_ASSIGN" && node.get_var_type() != "" && table_level == table[get_fname_index(current_function)][node.get_var_name()].level)
        {
            
            try {
                throw std::runtime_error("ERROR: Redefinition variable \'" + node.get_var_name() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
        }
        // Because we gonna keep type variable when we assign new value to variable
        if(table[get_fname_index(current_function)].contains(node.get_var_name()) && node.get_frag() == "LEFT_ASSIGN" && node.get_var_type() == "")
        {
            return;
        }

        //UNDEFINED VARIABLE ERROR
        if(!table[get_fname_index(current_function)].contains(node.get_var_name()) && node.get_var_type() == "" )
        {
            //CHECK IF VARIABLE EXSITS IN GLOBAL SCOPE
            if(table[0].contains(node.get_var_name()))
            {
                node.set_var_type(table[0][node.get_var_name()].type);
            } else {
                try {
                    throw std::runtime_error("ERROR: Undefined variable \'" + node.get_var_name() + "\'");
                } catch(std::runtime_error& e)
                {
                    std::cerr << e.what() << "\n";
                    exit(EXIT_FAILURE);
                }
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
            p.fragment_type = "PVARIABLE_" + node.get_func_name();
        }
         // P(arameter)Variable
    }

    p.level = table_level;
    p.type = node.get_var_type();

    std::string key = node.get_var_name();

    if((node.get_frag() == "RIGHT_ASSIGN1" || node.get_frag() == "RIGHT_ASSIGN2") && p.fragment_type[0] != 'L')
    {

        p.type = table[get_fname_index(current_function)][node.get_var_name()].type;

        key = node.get_var_name() + "_" + std::to_string(table_level);

        //table[get_fname_index(current_function)][key] = p;

    } //else if(p.fragment_type == "PVARIABLE") {
    //     key = key + "_" + node.get_func_name();
    // }
    table[get_fname_index(current_function)][key] = p;

}


void VisitorTable::visit(ASTFuncCall& node) 
{
    Properties p;
    
    p.level = table_level;
    p.type = "~";
    for(auto& arg: node.get_args())
    {
        arg->accept(*this);
        if(arg->is_literal())
        {
            node.append_args_to_vector(arg->get_arg(), get_literal_type(arg->get_arg(), current_function));
        } else {
            node.append_args_to_vector(arg->get_arg(), table[get_fname_index(current_function)][arg->get_arg()].type);
        }
    }

    // for(auto& param : node.get_args_from_vector())
    // {
    //     std::cout << "Args: " << param.first << " :: " << param.second << "\n";
    // }
    p.fragment_type = "FUNCTION_CALL";
    table[get_fname_index(current_function)][node.func_name()] = p;
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
    std::string key = "";
    Properties p;
    if(node.is_literal())
    {
        p.fragment_type = "LARGUMENT";

        if(node.get_arg()[0] == std::string("\"")[0])
        {
            p.type = "TEXT";
        } else if(std::isdigit(node.get_arg()[0])) {
            if(node.get_arg().find(std::string(".")) != std::string::npos)
            {
                p.type = "FLOAT_NUMBER";
            } else {
                p.type = "NUMBER";
            }
            
        } else if(node.get_arg()[0] == std::string("\'")[0])
        {
            p.type = "CHAR";
        }
        key = node.get_arg();
    }
    else {
        p.fragment_type = "ARGUMENT";
        key = node.get_arg()+"_argument_"+std::to_string(table_level);
        if(!table[get_fname_index(current_function)].contains(node.get_arg()))
        {
            try {
            throw std::runtime_error("ERROR: Undefined argument \'" + node.get_arg() + "\' in function-call");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
        }
        else {
            p.type = table[get_fname_index(current_function)][node.get_arg()].type;
        }
    }
    p.level = table_level;
    table[get_fname_index(current_function)][key] = p;

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
    table[get_fname_index(current_function)][node.get_return_value()] = p;
}

void VisitorTable::visit(ASTIf& node)
{
    // Properties p1;
    // p1.fragment_type = "IFVARIABLE";
    // p1.level = table_level;
    // p1.type = node.get_first_type();
    // table[node.get_first()] = p1;
    if(node.is_literal())
    {
        Properties p2;
        p2.fragment_type = "IFVARIABLE";
        p2.level = table_level;
        p2.type = node.get_second_type();
        table[get_fname_index(current_function)][node.get_second()] = p2;
    }
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
    if(table[get_fname_index(current_function)][node.get_assing()->get_lvalue()->get_var_name()].level > table_level)
    {   
         try {
                throw std::runtime_error("ERROR: Redefinition variable \'" + node.get_assing()->get_lvalue()->get_var_name() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
    }
    
}

void VisitorTable::visit(ASTForCond& node)
{
    Properties p2;
    // std::cout << "ans" << (node.is_literal());
    if(node.is_literal())
    {
        p2.fragment_type = "LFORCONDVARIABLE";
        if(node.get_second()[0] == std::string("\"")[0])
        {
            p2.type = "TEXT";
        } else if(std::isdigit(node.get_second()[0])) {
            p2.type = "NUMBER";
        } 
    }
    else
    {
        p2.fragment_type = "FORCONDVARIABLE";
        if(table[get_fname_index(current_function)].contains(node.get_second()))
        {
            
            p2.type = table[get_fname_index(current_function)][node.get_second()].type;
        } else {
            // for(int i = 0; i < k(undefined); i++)
            try {
                throw std::runtime_error("ERROR: Undefined variable \'" + node.get_second() + "\' in cond-expression: \'" + node.get_first() + " " + node.get_op() + " " + node.get_second() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
        }
    }
    p2.level = table_level;
    // for(int i = 0; j(undefined) < 10; i++)
    if(!table[get_fname_index(current_function)].contains(node.get_first()))
    {
        try {
            throw std::runtime_error("ERROR: Undefined variable \'" + node.get_first() + "\' in cond-expression: \'" + node.get_first() + " " + node.get_op() + " " + node.get_second() + "\'");
        } catch(std::runtime_error& e)
        {
            std::cerr << e.what() << "\n";
            exit(EXIT_FAILURE);
        }
    }
    table[get_fname_index(current_function)][node.get_second()+"_cond" + "_" + std::to_string(table_level)] = p2;

    Properties p1;
    p1.fragment_type = "FORCONDVARIABLE";
    p1.level = table_level;
    p1.type = table[get_fname_index(current_function)][node.get_first()].type;
    table[get_fname_index(current_function)][node.get_first()+"_cond" + "_" + std::to_string(table_level)] = p1;
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
        if(!table[get_fname_index(current_function)].contains(node.get_id()))
        {
            try {
            throw std::runtime_error("ERROR: Undefined variable \'" + node.get_id() + "\' in loop-expression: \'" + node.get_id() + node.get_unary_op() + "\'");
            } catch(std::runtime_error& e)
            {
                std::cerr << e.what() << "\n";
                exit(EXIT_FAILURE);
            }
        }
        p1.type = table[get_fname_index(current_function)][node.get_id()].type;
        table[get_fname_index(current_function)][node.get_id()+"_op" + "_" + std::to_string(table_level)] = p1;
    }
}
