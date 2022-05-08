#pragma once

#include "grammar/CsharpParser.h"
#include "grammar/CsharpVisitor.h"

#include <vector>
#include <string>
#include <ostream>

class ASTProgram;
class ASTFunction;
class ASTVariable;
class ASTFuncCall;
class ASTScope;
class ASTArgs;

class Visitor: public CsharpVisitor {
public:
    antlrcpp::Any visitExpressions(CsharpParser::ExpressionsContext* context) override;

    antlrcpp::Any visitProgram(CsharpParser::ProgramContext* context) override;
    antlrcpp::Any visitVar_def(CsharpParser::Var_defContext* context) override;
    antlrcpp::Any visitFunc_def(CsharpParser::Func_defContext* context) override;

    antlrcpp::Any visitStatement(CsharpParser::StatementContext *context) override;
    antlrcpp::Any visitScope(CsharpParser::ScopeContext *context) override;
    antlrcpp::Any visitFunc_call(CsharpParser::Func_callContext *context) override;
    antlrcpp::Any visitArgs(CsharpParser::ArgsContext *context) override;

    //antlrcpp::Any visitArgs(CsharpParser::ArgsContext *context) override;
    
    virtual void visit(ASTProgram& node) = 0;
    virtual void visit(ASTFunction& node) = 0;
    virtual void visit(ASTVariable& node) = 0;
    virtual void visit(ASTFuncCall& node) = 0;
    virtual void visit(ASTScope& node) = 0;
    virtual void visit(ASTArgs& node) = 0;

};

class ASTNode {
protected:
    static inline std::size_t m_depth = 0;
    //std::string m_type;

public:
    virtual ~ASTNode() = default;
    static void increase_depth() {m_depth+=2;}
    static void decrease_depth() {if (m_depth >= 2) {m_depth-=2;}}
    static std::size_t get_depth() {return m_depth;}
    virtual void  accept(Visitor& visitor) = 0;
};

class ASTProgram: public ASTNode {
private:
    std::vector<ASTNode*> m_children;

public:
    ASTProgram() = default;

    void           append_child(ASTNode* node);
    const ASTNode* get_child(std::size_t i) const;

    std::vector<ASTNode*> get_children();

    void accept(Visitor& visitor) override;
};

class ASTVariable: public ASTNode {
private:
    std::string m_var_name;
    std::string m_var_type;

public:
    ASTVariable() = default;

    std::string& var_name();
    std::string& var_type();

    void accept(Visitor& visitor) override;
};

class ASTFuncCall: public ASTNode {
private:
    std::string m_func_name;
    std::vector<ASTArgs*> args;
    // std::vector<ASTVariable>

public:
    ASTFuncCall() = default;

    std::string& func_name();
    std::vector<ASTArgs*> get_args() { return args; }
    ASTArgs* get_arg(std::size_t i) { return args[i]; }
    void set_args(ASTArgs* a, size_t i) { args[i] = a; }
    void append_arg(ASTArgs* a) {args.push_back(a);}

    void accept(Visitor& visitor) override;
};



class ASTFunction: public ASTNode {
private:
    /* Node info */
    std::string m_func_name;
    std::string m_return_type;
    ASTScope* m_scope = nullptr;
    /* Children */
    //std::vector<ASTVariable> m_arguments;
    //ASTExpression            m_expression;

public:
    ASTFunction() = default;

    std::string& func_name();
    std::string& return_type();
    void set_scope(ASTScope* sc)
    {
        m_scope = sc;
    }
    ASTScope* get_scope()
    {
        return m_scope;
    }
    void accept(Visitor& visitor) override;
};

class ASTScope : public ASTNode {
private:
    std::vector<ASTNode*> m_statements;
    std::string scope_name;
public:
    ASTScope() = default;

    void           append_statement(ASTNode* node);
    ASTNode* get_statement(std::size_t i);
    //NOTE:
    std::string get_scope_name() {return scope_name;}
    void set_scope_name(std::string sn) {scope_name = sn;}
    std::vector<ASTNode*> get_statements();

    void accept(Visitor& visitor) override;

};

class ASTArgs : public ASTNode {
private:
    std::string arg;
public:
    std::string get_arg() { return arg; }
    void set_arg(std::string a) {arg = a;}
    void accept(Visitor& visitor) override;
};

/* Visitor Implementation */
class VisitorInitialiser: public Visitor {
private:
    antlrcpp::Any m_context;

public:
    VisitorInitialiser(antlrcpp::Any context);

    void visit(ASTProgram& node) override;
    void visit(ASTFunction& node) override;
    void visit(ASTVariable& node) override;
    void visit(ASTFuncCall& node) override;
    void visit(ASTScope& node) override;
    void visit(ASTArgs& node) override;
    
};

class VisitorTraverse: public Visitor {
private:
    std::ostream& stream;
public:
    VisitorTraverse(std::ostream& os);

    void visit(ASTProgram& node) override;
    void visit(ASTFunction& node) override;
    void visit(ASTVariable& node) override;
    void visit(ASTFuncCall& node) override;
    void visit(ASTScope& node) override;
    void visit(ASTArgs& node) override;
};
