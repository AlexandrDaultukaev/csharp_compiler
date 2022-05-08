#include "ast.hpp"

#include "grammar/CsharpVisitor.h"

#include <iostream>
#include <any>

antlrcpp::Any Visitor::visitExpressions(CsharpParser::ExpressionsContext* context) {

    if (context->func_def()) {
        return antlrcpp::Any(context->func_def());
    }

    if (context->var_def()) {
        return antlrcpp::Any(context->var_def());
    }

    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitStatement(CsharpParser::StatementContext *context) {
    if (context->func_call()) {
        return antlrcpp::Any(context->func_call());
    }
    return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitProgram(CsharpParser::ProgramContext *context) {
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

/* ASTProgram */

void ASTProgram::append_child(ASTNode* node) { m_children.push_back(node); }
const ASTNode* ASTProgram::get_child(std::size_t i) const { return m_children[i]; }

std::vector<ASTNode*> ASTProgram::get_children() { return m_children; }

void ASTProgram::accept(Visitor& visitor) { visitor.visit(*this); }

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

/* ASTArgs */
void ASTArgs::accept(Visitor& visitor) { visitor.visit(*this); }

/* Visitor Implementation */
VisitorInitialiser::VisitorInitialiser(antlrcpp::Any context)
    : m_context(context) { }

void VisitorInitialiser::visit(ASTProgram& node) {
    // std::vector<ASTNode*> children;

    auto ctx = m_context.as<CsharpParser::ProgramContext*>();
    auto exprs = ctx->expressions();

    ASTNode* child;

    for (unsigned int i = 0; i < exprs.size(); i++) {

        auto expr = visitExpressions(exprs[i]);

        if (expr.isNotNull()) {

            if (expr.is<CsharpParser::Func_defContext*>()) {
                VisitorInitialiser visitor(expr.as<CsharpParser::Func_defContext*>());
                
                child = new ASTFunction;
                child->accept(visitor);

                node.append_child(child);
            }

            if (expr.is<CsharpParser::Var_defContext*>()) {
                VisitorInitialiser visitor(expr.as<CsharpParser::Var_defContext*>());

                child = new ASTVariable;
                child->accept(visitor);

                node.append_child(child);
            }
        }
    }
}

void VisitorInitialiser::visit(ASTScope& node) {
    // std::vector<ASTNode*> children;

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
        }
    }
}

void VisitorInitialiser::visit(ASTArgs& node) {
    //NOTE:
    auto ctx = m_context.as<antlr4::tree::TerminalNode*>();
    // std::cout << node.get_arg();
    node.set_arg(ctx->getText());

    // auto ctx = m_context.as<CsharpParser::ArgsContext*>();
    // node.set_arg(ctx->);
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

    auto ctx = m_context.as<CsharpParser::Var_defContext*>();

    node.var_name() = ctx->ID()->getText();
    node.var_type() = ctx->VAR()->getText();
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
    for(std::size_t i = 0; i < node.get_depth(); i++)
    {
        stream << " ";
    }
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
    for(std::size_t i = 0; i < node.get_depth(); i++)
    {
        stream << " ";
    }
    stream << "<variable name=\'"
       << node.var_name()
       << "\' type=\'"
       << node.var_type()
       << "\'/>\n";
}

void VisitorTraverse::visit(ASTFuncCall& node) {
    for(std::size_t i = 0; i < node.get_depth(); i++) { stream << " "; }
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
    for(std::size_t i = 0; i < node.get_depth(); i++) { stream << " "; }
    stream << "<scope " << "name=\'" << node.get_scope_name() << "\'>\n";
    VisitorTraverse visitor(stream);
    for(std::size_t i = 0; i < node.get_statements().size(); i++)
    {
        node.increase_depth();
        node.get_statement(i)->accept(visitor);
        node.decrease_depth();
    }
    for(std::size_t i = 0; i < node.get_depth(); i++) { stream << " "; }
    stream << "</scope>\n";
}

void VisitorTraverse::visit(ASTArgs& node) {
    //NOTE:
    stream << node.get_arg();
}
