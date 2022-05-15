#pragma once

#include "grammar/CsharpParser.h"
#include "grammar/CsharpVisitor.h"

#include <vector>
#include <string>
#include <fstream>

class ASTProgram;
class ASTFunction;
class ASTVariable;
class ASTFuncCall;
class ASTScope;
class ASTArgs;
class ASTAssign;
class ASTReturn;
class ASTIf;

class Visitor: public CsharpVisitor {
public:
    antlrcpp::Any visitExpressions(CsharpParser::ExpressionsContext* context) override;

    antlrcpp::Any visitProgram(CsharpParser::ProgramContext* context) override;
    antlrcpp::Any visitVar_def(CsharpParser::Var_defContext* context) override;
    antlrcpp::Any visitFunc_def(CsharpParser::Func_defContext* context) override;

    antlrcpp::Any visitAssign_statement(CsharpParser::Assign_statementContext *context) override;
    antlrcpp::Any visitStatement(CsharpParser::StatementContext *context) override;
    antlrcpp::Any visitScope(CsharpParser::ScopeContext *context) override;
    antlrcpp::Any visitFunc_call(CsharpParser::Func_callContext *context) override;
    antlrcpp::Any visitArgs(CsharpParser::ArgsContext *context) override;
    antlrcpp::Any visitLiteral(CsharpParser::LiteralContext *context) override;
    antlrcpp::Any visitReturn_statement(CsharpParser::Return_statementContext *context) override;
    antlrcpp::Any visitArg(CsharpParser::ArgContext *context) override;
    antlrcpp::Any visitIf_statement(CsharpParser::If_statementContext *context) override;

    //antlrcpp::Any visitArgs(CsharpParser::ArgsContext *context) override;
    
    virtual void visit(ASTProgram& node) = 0;
    virtual void visit(ASTFunction& node) = 0;
    virtual void visit(ASTVariable& node) = 0;
    virtual void visit(ASTFuncCall& node) = 0;
    virtual void visit(ASTScope& node) = 0;
    virtual void visit(ASTArgs& node) = 0;
    virtual void visit(ASTAssign& node) = 0;
    virtual void visit(ASTReturn& node) = 0;
    virtual void visit(ASTIf& node) = 0;

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

class ASTArgs : public ASTNode {
private:
    std::string arg;
public:
    ASTArgs() = default;
    std::string get_arg() { return arg; }
    void set_arg(std::string a) {arg = a;}
    void accept(Visitor& visitor) override;
    ~ASTArgs() = default;
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
    ~ASTScope()
    {
        for(std::size_t i = 0; i < m_statements.size(); i++)
        {
            delete m_statements[i];
        }
    }
};

class ASTAssign: public ASTNode
{
private:
    ASTVariable* lvalue = nullptr;
    ASTVariable* rvalue1 = nullptr;
    ASTVariable* rvalue2 = nullptr;
    std::string oper;
public:
    ASTAssign() = default;
    void set_lvalue(ASTVariable* a) {lvalue = a;}
    void set_rvalue1(ASTVariable* a) {rvalue1 = a;}
    void set_rvalue2(ASTVariable* a) {rvalue2 = a;}
    void set_oper(std::string o) { oper = o; }

    ASTVariable* get_lvalue() { return lvalue; }
    ASTVariable* get_rvalue1() { return rvalue1; }
    ASTVariable* get_rvalue2() { return rvalue2; }
    std::string get_oper() { return oper; }

    void accept(Visitor& visitor) override;
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
    ~ASTProgram()
    {
        for(std::size_t i = 0; i < m_children.size(); i++)
        {
            delete m_children[i];
        }
    }
};

class ASTVariable: public ASTNode {
private:
    // m_var_name - NAME if var isn't literal, and VALUE if var is literal
    std::string m_var_name;
    bool is_lit = false;
    //TODO: literal: 'A', 'Hello', 12, 12.4
    std::string m_var_type;

public:
    ASTVariable() = default;

    std::string& var_name();
    std::string& var_type();
    void set_literal(bool l) { is_lit = l;}
    bool is_literal() {return is_lit;}
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
    ~ASTFuncCall()
    {
        for(std::size_t i = 0; i < args.size(); i++)
        {
            delete args[i];
        }
        
    }
};

class ASTReturn : public ASTNode {
private:
    std::string return_value = "";
    std::string type = "";
    bool is_lit = false;

public:
    ASTReturn() = default;
    bool is_literal() { return is_lit; }
    std::string get_return_value() { return return_value; }
    void set_return_value(std::string rv) { return_value = rv; }
    std::string get_return_type() { return type; }
    void set_return_type(std::string t) { type = t; }
    void set_literal(bool l) { is_lit = l; }
    ~ASTReturn() = default;
    
    void accept(Visitor& visitor) override;
};

class ASTFunction: public ASTNode {
private:
    /* Node info */
    std::string m_func_name;
    std::string m_return_type;
    ASTReturn* m_return = nullptr;
    ASTScope* m_scope = nullptr;
public:
    ASTFunction() = default;
    std::string& return_type();
    std::string& func_name();
    void set_scope(ASTScope* sc)
    {
        m_scope = sc;
    }
    ASTScope* get_scope()
    {
        return m_scope;
    }
    void set_return(ASTReturn* r)
    {
        m_return = r;
    }
    ASTReturn* get_return()
    {
        return m_return;
    }

    void accept(Visitor& visitor) override;
    ~ASTFunction()
    {
        delete m_scope;
        delete m_return;
    }
};

class ASTIf : public ASTNode {
    std::string first = "";
    std::string first_type = "";
    std::string second = "";
    std::string second_type = "";
    std::string op = "";
    ASTScope* m_scope = nullptr;
public:
    ASTIf() = default;
    void set_first(std::string s) { first = s;}
    void set_first_type(std::string s) { first_type = s;}
    void set_second(std::string s) { second = s;}
    void set_second_type(std::string s) { second_type = s;}
    void set_op(std::string s) { op = s;}

    std::string get_first() { return first; }
    std::string get_first_type() { return first_type; }
    std::string get_second() { return second; }
    std::string get_second_type() { return second_type; }
    std::string get_op() { return op; }

    void set_scope(ASTScope* sc) { m_scope = sc; }
    ASTScope* get_scope() { return m_scope; }

    void accept(Visitor& visitor) override;

    ~ASTIf() { delete m_scope; }
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
    void visit(ASTAssign& node) override;
    void visit(ASTReturn& node) override;
    void visit(ASTIf& node) override;
    
};

class VisitorTraverse: public Visitor {
private:
    std::ofstream& stream;
public:
    VisitorTraverse(std::ofstream& os);

    void set_indent(std::size_t spaces) {for(std::size_t i = 0; i < spaces; i++) { stream << " "; }}
    void visit(ASTProgram& node) override;
    void visit(ASTFunction& node) override;
    void visit(ASTVariable& node) override;
    void visit(ASTFuncCall& node) override;
    void visit(ASTScope& node) override;
    void visit(ASTArgs& node) override;
    void visit(ASTAssign& node) override;
    void visit(ASTReturn& node) override;
    void visit(ASTIf& node) override;
};



