#include "ast.hpp"

#include "grammar/CsharpVisitor.h"

#include <iostream>
#include <any>

antlrcpp::Any Visitor::visitExpressions(CsharpParser::ExpressionsContext* context) {

    if (context->func_def()) {
        return antlrcpp::Any(context->func_def());
    }

    if (context->assign_statement()) {
        return antlrcpp::Any(context->assign_statement());
    }

    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitStatement(CsharpParser::StatementContext *context) {
    if (context->func_call()) {
        return antlrcpp::Any(context->func_call());
    }
    if (context->assign_statement()) {
        return antlrcpp::Any(context->assign_statement());
    }
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitProgram(CsharpParser::ProgramContext *context) {
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitAssign_statement(CsharpParser::Assign_statementContext *context) {
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitVar_def(CsharpParser::Var_defContext *context) {
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitScope(CsharpParser::ScopeContext *context) {
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitFunc_def(CsharpParser::Func_defContext *context) {
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitFunc_call(CsharpParser::Func_callContext *context) {
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitArgs(CsharpParser::ArgsContext *context) {
    if (context->UNIT().size()) {
        return antlrcpp::Any(context->UNIT());
    }
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitLiteral(CsharpParser::LiteralContext *context) {
    return antlrcpp::Any(context);
}

/* ASTProgram */

void ASTProgram::append_child(ASTNode* node) { m_children.push_back(node); }
const ASTNode* ASTProgram::get_child(std::size_t i) const { return m_children[i]; }

std::vector<ASTNode*> ASTProgram::get_children() { return m_children; }

void ASTProgram::accept(Visitor& visitor) { visitor.visit(*this); }
void ASTAssign::accept(Visitor& visitor) { visitor.visit(*this); }

/* ASTVariable */

std::string& ASTVariable::var_name() { return m_var_name; }
std::string& ASTVariable::var_type() { return m_var_type; }

void ASTVariable::accept(Visitor& visitor) {
    visitor.visit(*this); }

/* ASTFuncCall */

std::string& ASTFuncCall::func_name() { return m_func_name; }

void ASTFuncCall::accept(Visitor& visitor) {
    visitor.visit(*this);
}


/* ASTFunction */

std::string& ASTFunction::func_name() { return m_func_name; }
std::string& ASTFunction::return_type() { return m_return_type; }

void ASTFunction::accept(Visitor& visitor) { visitor.visit(*this); }


/* ASTScope */

    void ASTScope::append_statement(ASTNode* node) {
        m_statements.push_back(node);
    }
    ASTNode* ASTScope::get_statement(std::size_t i) {
        return m_statements[i];
    }

    std::vector<ASTNode*> ASTScope::get_statements() {
        return m_statements;
    }

    void ASTScope::accept(Visitor& visitor) { visitor.visit(*this); }


void ASTArgs::accept(Visitor& visitor) { visitor.visit(*this); }


VisitorInitialiser::VisitorInitialiser(antlrcpp::Any context)
    : m_context(context) { }

void VisitorInitialiser::visit(ASTProgram& node) {
    // std::vector<ASTNode*> children;
    
    auto ctx = m_context.as<CsharpParser::ProgramContext*>();
    auto exprs = ctx->expressions();

    ASTNode* child = nullptr;
    ASTNode* child2 = nullptr;
    for (unsigned int i = 0; i < exprs.size(); i++) {

        auto expr = visitExpressions(exprs[i]);

        if (expr.isNotNull()) {
            // Check if statement is function call: "Console.Writeln("Hello!\n")"
            if (expr.is<CsharpParser::Func_defContext*>()) {
                VisitorInitialiser visitor(expr.as<CsharpParser::Func_defContext*>());
                
                child = new ASTFunction;
                child->accept(visitor);

                node.append_child(child);
            }

            if (expr.is<CsharpParser::Assign_statementContext*>()) {
 
                VisitorInitialiser visitor(expr.as<CsharpParser::Assign_statementContext*>());
  
                child = new ASTVariable;

                child->accept(visitor);

                // Lock to add variable of undefined type
                if(static_cast<ASTVariable*>(child)->var_type() != "")
                    {node.append_child(child);}
                
                // Check if statement looks like "(int) a = b + (c)"
                if(expr.as<CsharpParser::Assign_statementContext*>()->ASSIGN() != nullptr)
                {
                    
                    child2 = new ASTAssign;
                    child2->accept(visitor);
                    node.append_child(child2);
                }
                
                
            }
        }
    }
}

void VisitorInitialiser::visit(ASTScope& node) {

    auto ctx = m_context.as<CsharpParser::ScopeContext*>();
    auto exprs = ctx->statement();

    ASTNode* child;

    for (unsigned int i = 0; i < exprs.size(); i++) {

        auto expr = visitStatement(exprs[i]);

        if (expr.isNotNull()) {

            if (expr.is<CsharpParser::Func_callContext*>()) {
                VisitorInitialiser visitor(expr.as<CsharpParser::Func_callContext*>());
                
                child = new ASTFuncCall;
                child->accept(visitor);

                node.append_statement(child);
            }
            if (expr.is<CsharpParser::Assign_statementContext*>()) {
                VisitorInitialiser visitor(expr.as<CsharpParser::Assign_statementContext*>());
  
                child = new ASTVariable;

                child->accept(visitor);

                // Lock to add variable of undefined type
                if(static_cast<ASTVariable*>(child)->var_type() != "")
                    {node.append_statement(child);}
                
                // Check if statement looks like "(int) a = b + (c)"
                if(expr.as<CsharpParser::Assign_statementContext*>()->ASSIGN() != nullptr)
                {
                    ASTNode* child2 = nullptr;
                    child2 = new ASTAssign;
                    child2->accept(visitor);
                    node.append_statement(child2);
                }
            }
        }
    }
}

void VisitorInitialiser::visit(ASTArgs& node) {
    //NOTE: Context for ASTArgs is certain argument
    auto ctx = m_context.as<antlr4::tree::TerminalNode*>();

    node.set_arg(ctx->getText());
}

void VisitorInitialiser::visit(ASTAssign& node)
{
    auto ctx = m_context.as<CsharpParser::Assign_statementContext*>();
    ASTVariable* l = new ASTVariable;
    ASTVariable* r1 = new ASTVariable;
    ASTVariable* r2 = new ASTVariable;
    bool is_r2_set = false;
    int ind = 0;
    int lit_ind = 0;
    // Lvalue
    if(ctx->var_def() == nullptr)
    {
        l->var_name() = ctx->ID(ind)->getText();
        ind++;

    } else {
        l->var_name() = ctx->var_def()->ID()->getText();
    }

    // Rvalue1
    if(ctx->literal(lit_ind) != nullptr)
    {
        if(ctx->literal(lit_ind)->TEXT() != nullptr) {
            r1->var_name() = ctx->literal(lit_ind)->TEXT()->getText();
            r1->set_literal(true);
            r1->var_type() = "TEXT";
        } else if(ctx->literal(lit_ind)->NUMBER() != nullptr) {
            r1->var_name() = ctx->literal(lit_ind)->NUMBER()->getText();
            r1->set_literal(true);
            r1->var_type() = "NUMBER";
        } else if(ctx->literal(lit_ind)->FLOAT_NUMBER() != nullptr) {
            r1->var_name() = ctx->literal(lit_ind)->FLOAT_NUMBER()->getText();
            r1->set_literal(true);
            r1->var_type() = "FLOAT_NUMBER";
        } else if(ctx->literal(lit_ind)->CHAR() != nullptr) {
            r1->var_name() = ctx->literal(lit_ind)->CHAR()->getText();
            r1->set_literal(true);
            r1->var_type() = "CHAR";
        }
        lit_ind++;
    } else {
        r1->var_name() = ctx->ID(ind)->getText();
        ind++;
    }

    //Rvalue2
    if(ctx->ID(ind) != nullptr)
    {
        is_r2_set = true;
        r2->var_name() = ctx->ID(ind)->getText();
    } else if(ctx->literal(lit_ind) != nullptr)
    {
        is_r2_set = true;
        if(ctx->literal(lit_ind)->TEXT() != nullptr) {
            r2->var_name() = ctx->literal(lit_ind)->TEXT()->getText();
            r2->set_literal(true);
            r2->var_type() = "TEXT";
        } else if(ctx->literal(lit_ind)->NUMBER() != nullptr) {
            r2->var_name() = ctx->literal(lit_ind)->NUMBER()->getText();
            r2->set_literal(true);
            r2->var_type() = "NUMBER";
        } else if(ctx->literal(lit_ind)->FLOAT_NUMBER() != nullptr) {
            r2->var_name() = ctx->literal(lit_ind)->FLOAT_NUMBER()->getText();
            r2->set_literal(true);
            r2->var_type() = "FLOAT_NUMBER";
        } else if(ctx->literal(lit_ind)->CHAR() != nullptr) {
            r2->var_name() = ctx->literal(lit_ind)->CHAR()->getText();
            r2->set_literal(true);
            r2->var_type() = "CHAR";
        }
    }

    node.set_lvalue(l);
    node.set_rvalue1(r1);
    if(is_r2_set)
        {node.set_oper(ctx->BINARY_OP()->getText()); node.set_rvalue2(r2);}
    else 
        {node.set_rvalue2(nullptr);}
}

void VisitorInitialiser::visit(ASTFunction& node) {
    auto ctx = m_context.as<CsharpParser::Func_defContext*>();
    //NOTE:
    if(ctx->scope() != nullptr)
    {
        auto child = new ASTScope;
        VisitorInitialiser visitor(ctx->scope());
        child->accept(visitor);
        child->set_scope_name(ctx->ID()->getText());
        node.set_scope(child);
    }
    node.func_name() = ctx->ID()->getText();
    node.return_type() = ctx->VAR()->getText();
}

void VisitorInitialiser::visit(ASTVariable& node) {

    //TODO: If var == literal -> ERROR
    auto ctx = m_context.as<CsharpParser::Assign_statementContext*>();
    if(ctx->ID().size() < 1)
    {
        node.var_name() = ctx->var_def()->ID()->getText();
        node.var_type() = ctx->var_def()->VAR()->getText();

    } else {
        node.var_type() = "";
        
        node.var_name() = ctx->ID()[0]->getText();
        
    }
    
}

void VisitorInitialiser::visit(ASTFuncCall& node) {
    auto ctx = m_context.as<CsharpParser::Func_callContext*>();
    node.func_name() = ctx->ID()->getText(); //TODO: Console.Writeln() -> Console/Writeln/args
    if(ctx->args() != nullptr)
    {
        for(std::size_t i = 0; i < ctx->args()->UNIT().size(); i++)
        {
            auto child = new ASTArgs;
            VisitorInitialiser visitor(ctx->args()->UNIT(i));
            child->accept(visitor);
            //child->set_arg(ctx->args()->UNIT(i)->getText());
            node.append_arg(child);
        }
    }
}

VisitorTraverse::VisitorTraverse(std::ostream& os) : stream(os) { }

void VisitorTraverse::visit(ASTProgram& node) {
    for(std::size_t i = 0; i < node.get_depth(); i++)
    {
        stream << " ";
    }

    stream << "<program>\n";

    auto children = node.get_children();

    VisitorTraverse visitor(stream);
    for (unsigned int i = 0; i < children.size(); i++) {
        node.increase_depth();
        children[i]->accept(visitor);
        node.decrease_depth();
    }

    for(std::size_t i = 0; i < node.get_depth(); i++)
    {
        stream << " ";
    }
    stream << "</program>\n";

}

void VisitorTraverse::visit(ASTFunction& node) {
    set_indent(node.get_depth());
    stream << "<function name=\'"
       << node.func_name()
       << "\' return-type=\'"
       << node.return_type()
       << "\'/>\n";
    VisitorTraverse visitor(stream);
    //NOTE:
    if(node.get_scope() != nullptr)
    {
        node.increase_depth();
        node.get_scope()->accept(visitor);
        node.decrease_depth();
    }
}

void VisitorTraverse::visit(ASTVariable& node) {
    set_indent(node.get_depth());
    stream << "<variable name=\'"
       << node.var_name()
       << "\' type=\'"
       << node.var_type()
       << "\'/>\n";
}

void VisitorTraverse::visit(ASTAssign& node)
{
    set_indent(node.get_depth());
    stream << "<assign lhs=" << node.get_lvalue()->var_name()
        << ", rhs=";
    if(node.get_rvalue2() != nullptr)
    {
        stream << "(" << node.get_rvalue1()->var_name() << ", " << node.get_rvalue2()->var_name() << "), op=\'" << node.get_oper() << "\'/>\n";
    } else {
        stream << node.get_rvalue1()->var_name() << ", op=\'" << node.get_oper() << "\'/>\n";
    }
    
}

void VisitorTraverse::visit(ASTFuncCall& node) {
    set_indent(node.get_depth());
    stream << "<call name=\'"
       << node.func_name() << "\', args=";
    for(std::size_t i = 0; i < node.get_args().size(); i++)
    {
        VisitorTraverse visitor(stream);

        node.get_arg(i)->accept(visitor);

        if(i+1 != node.get_args().size())
        {
            stream << ", ";
        }
    }
    stream << "/>\n";
}

void VisitorTraverse::visit(ASTScope& node) {
    //NOTE:
    set_indent(node.get_depth());
    stream << "<scope " << "name=\'" << node.get_scope_name() << "\'>\n";
    VisitorTraverse visitor(stream);
    for(std::size_t i = 0; i < node.get_statements().size(); i++)
    {
        node.increase_depth();
        node.get_statement(i)->accept(visitor);
        node.decrease_depth();
    }
    set_indent(node.get_depth());
    stream << "</scope>\n";
}

void VisitorTraverse::visit(ASTArgs& node) {
    //NOTE:
    stream << node.get_arg();
}
