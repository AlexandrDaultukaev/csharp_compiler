#include "ast.hpp"

#include "grammar/CsharpVisitor.h"

#include <any>
#include <fstream>
#include <iostream>

antlrcpp::Any
Visitor::visitExpressions(CsharpParser::ExpressionsContext *context) {

  if (context->func_def()) {
    return antlrcpp::Any(context->func_def());
  }

  if (context->assign_statement()) {
    return antlrcpp::Any(context->assign_statement());
  }

  if (context->if_statement()) {
    return antlrcpp::Any(context->if_statement());
  }

  if (context->for_statement()) {
    return antlrcpp::Any(context->for_statement());
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
  if (context->if_statement()) {
    return antlrcpp::Any(context->if_statement());
  }
  if (context->kw_statement()) {
    return antlrcpp::Any(context->kw_statement());
  }
  if (context->for_statement()) {
    return antlrcpp::Any(context->for_statement());
  }

  return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitProgram(CsharpParser::ProgramContext *context) {
  return antlrcpp::Any(context);
}

antlrcpp::Any
Visitor::visitAssign_statement(CsharpParser::Assign_statementContext *context) {
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
  if (context->arg().size()) {
    return antlrcpp::Any(context->arg());
  }
  return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitPars(CsharpParser::ParsContext *context) {
  return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitIf_statement(CsharpParser::If_statementContext *context) {
  return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitLiteral(CsharpParser::LiteralContext *context) {
  if (context->NUMBER()) {
    return antlrcpp::Any(context->NUMBER());
  }
  if (context->FLOAT_NUMBER()) {
    return antlrcpp::Any(context->FLOAT_NUMBER());
  }
  if (context->TEXT()) {
    return antlrcpp::Any(context->TEXT());
  }
  if (context->CHARv()) {
    return antlrcpp::Any(context->CHARv());
  }
  return antlrcpp::Any(context);
}

antlrcpp::Any
Visitor::visitReturn_statement(CsharpParser::Return_statementContext *context) {
  if (context->ID()) {
    return antlrcpp::Any(context->ID());
  }
  if (context->literal()) {
    if (context->literal()->NUMBER()) {
      return antlrcpp::Any(context->literal()->NUMBER());
    }
    if (context->literal()->FLOAT_NUMBER()) {
      return antlrcpp::Any(context->literal()->FLOAT_NUMBER());
    }
    if (context->literal()->TEXT()) {
      return antlrcpp::Any(context->literal()->TEXT());
    }
    if (context->literal()->CHARv()) {
      return antlrcpp::Any(context->literal()->CHARv());
    }
  }
  return antlrcpp::Any(context);
}

antlrcpp::Any Visitor::visitArg(CsharpParser::ArgContext *context) {
  if (context->ID() != nullptr) {
    return antlrcpp::Any(context->ID());
  }
  if (context->literal() != nullptr) {
    return visitLiteral(context->literal());
  }
  return antlrcpp::Any(context);
}

antlrcpp::Any
Visitor::visitFor_statement(CsharpParser::For_statementContext *context) {
  return antlrcpp::Any(context);
}
antlrcpp::Any
Visitor::visitFor_condition(CsharpParser::For_conditionContext *context) {
  return antlrcpp::Any(context);
}
antlrcpp::Any
Visitor::visitFor_operation(CsharpParser::For_operationContext *context) {
  return antlrcpp::Any(context);
}

antlrcpp::Any
Visitor::visitKw_statement(CsharpParser::Kw_statementContext *context) {
  return antlrcpp::Any(context);
}
/* ASTProgram */

void ASTProgram::append_child(ASTNode *node) { m_children.push_back(node); }
const ASTNode *ASTProgram::get_child(std::size_t i) const {
  return m_children[i];
}

std::vector<ASTNode *> ASTProgram::get_children() { return m_children; }

void ASTProgram::accept(Visitor &visitor) { visitor.visit(*this); }
void ASTAssign::accept(Visitor &visitor) { visitor.visit(*this); }
void ASTFor::accept(Visitor &visitor) { visitor.visit(*this); }
void ASTForCond::accept(Visitor &visitor) { visitor.visit(*this); }
void ASTForOp::accept(Visitor &visitor) { visitor.visit(*this); }

/* ASTVariable */

std::string &ASTVariable::var_name() { return m_var_name; }
std::string &ASTVariable::var_type() { return m_var_type; }

void ASTVariable::accept(Visitor &visitor) { visitor.visit(*this); }

/* ASTFuncCall */

std::string &ASTFuncCall::func_name() { return m_func_name; }

void ASTFuncCall::accept(Visitor &visitor) { visitor.visit(*this); }

/* ASTFunction */

std::string &ASTFunction::func_name() { return m_func_name; }
std::string &ASTFunction::return_type() { return m_return_type; }

void ASTFunction::accept(Visitor &visitor) { visitor.visit(*this); }

/* ASTScope */

void ASTScope::append_statement(ASTNode *node) { m_statements.push_back(node); }
ASTNode *ASTScope::get_statement(std::size_t i) { return m_statements[i]; }

std::vector<ASTNode *> ASTScope::get_statements() { return m_statements; }

void ASTScope::accept(Visitor &visitor) { visitor.visit(*this); }

void ASTArgs::accept(Visitor &visitor) { visitor.visit(*this); }

void ASTReturn::accept(Visitor &visitor) { visitor.visit(*this); }
void ASTIf::accept(Visitor &visitor) { visitor.visit(*this); }

VisitorInitialiser::VisitorInitialiser(antlrcpp::Any context)
    : m_context(context) {}

void VisitorInitialiser::visit(ASTProgram &node) {
  // std::vector<ASTNode*> children;

  auto ctx = m_context.as<CsharpParser::ProgramContext *>();
  auto exprs = ctx->expressions();

  ASTNode *child = nullptr;
  ASTNode *child2 = nullptr;
  for (unsigned int i = 0; i < exprs.size(); i++) {

    auto expr = visitExpressions(exprs[i]);

    if (expr.isNotNull()) {
      // Check if statement is function call: "Console.Writeln("Hello!\n")"
      if (expr.is<CsharpParser::Func_defContext *>()) {
        VisitorInitialiser visitor(expr.as<CsharpParser::Func_defContext *>());

        child = new ASTFunction;
        child->accept(visitor);

        node.append_child(child);
      }

      if (expr.is<CsharpParser::Assign_statementContext *>()) {

        VisitorInitialiser visitor(
            expr.as<CsharpParser::Assign_statementContext *>());

        child = new ASTVariable;
        static_cast<ASTVariable *>(child)->set_ctx_type("ASSIGN");
        child->accept(visitor);

        // Lock to add variable of undefined type
        if (static_cast<ASTVariable *>(child)->var_type() != "") {
          node.append_child(child);
        }

        // Check if statement looks like "(int) a = b + (c)"
        if (expr.as<CsharpParser::Assign_statementContext *>()->ASSIGN() !=
            nullptr) {

          child2 = new ASTAssign;
          child2->accept(visitor);
          node.append_child(child2);
        }
      }

      if (expr.is<CsharpParser::If_statementContext *>()) {
        VisitorInitialiser visitor(
            expr.as<CsharpParser::If_statementContext *>());
        child = new ASTIf;
        child->accept(visitor);
        node.append_child(child);
      }
      if (expr.is<CsharpParser::For_statementContext *>()) {
        VisitorInitialiser visitor(
            expr.as<CsharpParser::For_statementContext *>());
        child = new ASTFor;
        child->accept(visitor);
        node.append_child(child);
      }
    }
  }
}

void VisitorInitialiser::visit(ASTFor &node) {

  auto ctx = m_context.as<CsharpParser::For_statementContext *>();
  ASTAssign *for_assign = new ASTAssign;
  ASTForCond *for_cond = new ASTForCond;
  ASTForOp *for_op = new ASTForOp;
  ASTScope *scope = new ASTScope;

  VisitorInitialiser visitor(ctx->assign_statement());
  for_assign->accept(visitor);
  node.set_assing(for_assign);

  VisitorInitialiser visitor_cond(ctx->for_condition());
  for_cond->accept(visitor_cond);
  node.set_cond(for_cond);

  VisitorInitialiser visitor_op(ctx->for_operation());
  for_op->accept(visitor_op);
  node.set_op(for_op);

  VisitorInitialiser visitor_scope(ctx->scope());
  scope->accept(visitor_scope);
  node.set_scope(scope);
}

void VisitorInitialiser::visit(ASTForCond &node) {

  auto ctx = m_context.as<CsharpParser::For_conditionContext *>();
  node.set_first(ctx->ID(0)->getText());
  node.set_op(ctx->LOGIC_OP()->getText());
  if (ctx->ID().size() > 1) {
    node.set_second(ctx->ID(1)->getText());
  } else {
    node.set_second(visitLiteral(ctx->literal())
                        .as<antlr4::tree::TerminalNode *>()
                        ->getText());
    node.set_literal(true);
  }
}

void VisitorInitialiser::visit(ASTForOp &node) {
  auto ctx = m_context.as<CsharpParser::For_operationContext *>();
  if (ctx->assign_statement() != nullptr) {
    ASTAssign *asgn = new ASTAssign;
    VisitorInitialiser visitor(ctx->assign_statement());
    asgn->accept(visitor);
    node.set_assign(asgn);
  } else {
    node.set_id(ctx->ID()->getText());
    node.set_unary_op(ctx->UNARYMATHEXP()->getText());
  }
}

void VisitorInitialiser::visit(ASTScope &node) {

  auto ctx = m_context.as<CsharpParser::ScopeContext *>();
  auto exprs = ctx->statement();

  ASTNode *child;

  for (unsigned int i = 0; i < exprs.size(); i++) {

    auto expr = visitStatement(exprs[i]);

    if (expr.isNotNull()) {
      if (expr.is<CsharpParser::Func_callContext *>()) {
        VisitorInitialiser visitor(expr.as<CsharpParser::Func_callContext *>());

        child = new ASTFuncCall;
        child->accept(visitor);

        node.append_statement(child);
      }
      if (expr.is<CsharpParser::Assign_statementContext *>()) {
        VisitorInitialiser visitor(
            expr.as<CsharpParser::Assign_statementContext *>());


        //**********************************************************
        // allow: <variable a, int>
        //        <assign a, ...>

        // child = new ASTVariable;
        
        // static_cast<ASTVariable *>(child)->set_ctx_type("ASSIGN");
        // static_cast<ASTVariable *>(child)->set_frag("LEFT_ASSIGN");
        // child->accept(visitor);

        // Lock to add variable of undefined type
        // if (static_cast<ASTVariable *>(child)->var_type() != "") {
        //   node.append_statement(child);
        // }
        //**********************************************************
        // Check if statement looks like "(int) a = b + (c)"
        if (expr.as<CsharpParser::Assign_statementContext *>()->ASSIGN() !=
            nullptr) {
          ASTNode *child2 = nullptr;
          child2 = new ASTAssign;
          child2->accept(visitor);
          node.append_statement(child2);
        }
      }
      if (expr.is<CsharpParser::If_statementContext *>()) {
        VisitorInitialiser visitor(
            expr.as<CsharpParser::If_statementContext *>());
        child = new ASTIf;
        child->accept(visitor);
        node.append_statement(child);
      }

      if (expr.is<CsharpParser::Kw_statementContext *>()) {
        VisitorInitialiser visitor(
            expr.as<CsharpParser::Kw_statementContext *>());
        child = new ASTKw;
        child->accept(visitor);
        node.append_statement(child);
      }

      if (expr.is<CsharpParser::For_statementContext *>()) {
        VisitorInitialiser visitor(
            expr.as<CsharpParser::For_statementContext *>());
        child = new ASTFor;
        child->accept(visitor);
        node.append_statement(child);
      }
    }
  }
}

void VisitorInitialiser::visit(ASTArgs &node) {
  auto ctx = visitArg(m_context.as<CsharpParser::ArgContext *>())
                 .as<antlr4::tree::TerminalNode *>();
  if(m_context.as<CsharpParser::ArgContext *>()->literal())
  {
    node.set_literal(true);
  }
  node.set_arg(ctx->getText());
}

void SetLiteralVariable(ASTVariable *var, CsharpParser::LiteralContext *ctx) {
  var->set_literal(true);
  if (ctx->TEXT() != nullptr) {
    var->var_name() = ctx->TEXT()->getText();
    var->var_type() = "TEXT";
  } else if (ctx->NUMBER() != nullptr) {
    var->var_name() = ctx->NUMBER()->getText();
    var->var_type() = "NUMBER";
  } else if (ctx->FLOAT_NUMBER() != nullptr) {
    var->var_name() = ctx->FLOAT_NUMBER()->getText();
    var->var_type() = "FLOAT_NUMBER";
  } else if (ctx->CHARv() != nullptr) {
    var->var_name() = ctx->CHARv()->getText();
    var->var_type() = "CHAR";
  }
}

void VisitorInitialiser::visit(ASTAssign &node) {
  auto ctx = m_context.as<CsharpParser::Assign_statementContext *>();
  ASTVariable *l = new ASTVariable;
  ASTVariable *r1 = new ASTVariable;
  ASTVariable *r2 = new ASTVariable;
  ASTFuncCall *f = new ASTFuncCall;
  bool is_r2_set = false;
  int ind = 0;
  int lit_ind = 0;
  l->set_ctx_type("ASSIGN");
  r1->set_ctx_type("ASSIGN");
  r2->set_ctx_type("ASSIGN");
  // Lvalue
  if (ctx->var_def() == nullptr) {
    l->var_name() = ctx->ID(ind)->getText();
    ind++;
  } else {
    l->var_name() = ctx->var_def()->ID()->getText();
    l->var_type() = ctx->var_def()->VAR()->getText();
  }
  l->set_frag("LEFT_ASSIGN");
  node.set_lvalue(l);

  // FuncCall, like 'bool b = s1.Contains(s2);'
  if (ctx->func_call() != nullptr) {
    VisitorInitialiser visitor(ctx->func_call());
    f->accept(visitor);
    node.set_funccall(f);
  } else {
    // Rvalue1
    delete f;
    if (ctx->literal(lit_ind) != nullptr) {
      SetLiteralVariable(r1, ctx->literal(lit_ind));
      lit_ind++;
    } else {
      r1->var_name() = ctx->ID(ind)->getText();
      ind++;
    }
    r1->set_frag("RIGHT_ASSIGN1");
    // Rvalue2
    if (ctx->ID(ind) != nullptr) {
      is_r2_set = true;
      r2->var_name() = ctx->ID(ind)->getText();
      r2->set_frag("RIGHT_ASSIGN2");
    } else if (ctx->literal(lit_ind) != nullptr) {
      is_r2_set = true;
      SetLiteralVariable(r2, ctx->literal(lit_ind));
      r2->set_frag("LRIGHT_ASSIGN2");
    }

    node.set_rvalue1(r1);
    if (is_r2_set) {
      node.set_oper(ctx->BINARY_OP()->getText());
      node.set_rvalue2(r2);
    } else {
      delete r2;
      node.set_rvalue2(nullptr);
    }
  }
}

void VisitorInitialiser::visit(ASTFunction &node) {
  auto ctx = m_context.as<CsharpParser::Func_defContext *>();
  if (ctx->scope() != nullptr) {
    auto child = new ASTScope;
    VisitorInitialiser visitor(ctx->scope());
    child->accept(visitor);
    child->set_scope_name(ctx->ID()->getText());
    node.set_scope(child);
  }
  if (ctx->return_statement() != nullptr) {
    auto return_child = new ASTReturn;
    VisitorInitialiser visitor(ctx->return_statement());
    return_child->accept(visitor);
    node.set_return(return_child);
  }
  node.func_name() = ctx->ID()->getText();
  node.return_type() = ctx->VAR()->getText();
  if(ctx->pars() != nullptr)
  {
    auto pars_ctx = ctx->pars();
    for(std::size_t i = 0; i < pars_ctx->var_def().size(); i++)
    {
      auto param = new ASTVariable;
      param->set_ctx_type("PARS");
      VisitorInitialiser visitor(pars_ctx->var_def(i));
      param->accept(visitor);
      node.append_param(param);
    }
  }
}

// NOTE: Perhabs i should implement this as "visit(ASTAssign &node)",
// making "visitReturn_statement" implementation more clearly, cleaner and
// shorter
void VisitorInitialiser::visit(ASTReturn &node) {
  auto ctx = m_context.as<CsharpParser::Return_statementContext *>();
  auto ret_ctx = visitReturn_statement(ctx);
  node.set_return_value(ret_ctx.as<antlr4::tree::TerminalNode *>()->getText());
  if (ctx->ID() != nullptr) {
    node.set_return_type("ID");
  } else if (ctx->literal()->NUMBER() != nullptr) {
    node.set_return_type("NUMBER");
  } else if (ctx->literal()->CHARv() != nullptr) {
    node.set_return_type("CHAR");
  } else if (ctx->literal()->FLOAT_NUMBER() != nullptr) {
    node.set_return_type("FLOAT");
  } else if (ctx->literal()->TEXT() != nullptr) {
    node.set_return_type("STRING");
  }
  node.set_literal((ctx->ID() == nullptr));
}

void VisitorInitialiser::visit(ASTVariable &node) {

  if(node.get_ctx_type() == "ASSIGN")
  {  // TODO: If var == literal -> ERROR
    auto ctx = m_context.as<CsharpParser::Assign_statementContext *>();
    if (ctx->ID().size() < 1) {
      node.var_name() = ctx->var_def()->ID()->getText();
      node.var_type() = ctx->var_def()->VAR()->getText();

    } else {
      node.var_type() = "";

      node.var_name() = ctx->ID()[0]->getText();
    }
  }
  if(node.get_ctx_type() == "PARS")
  {
      auto ctx = m_context.as<CsharpParser::Var_defContext *>();
      node.var_name() = ctx->ID()->getText();
      node.var_type() = ctx->VAR()->getText();
  }

}

void VisitorInitialiser::visit(ASTFuncCall &node) {
  auto ctx = m_context.as<CsharpParser::Func_callContext *>();
  node.func_name() =
      ctx->ID()->getText(); // TODO: Console.Writeln() -> Console/Writeln/args
  if (ctx->args() != nullptr) {
    for (std::size_t i = 0; i < ctx->args()->arg().size(); i++) {
      auto child = new ASTArgs;
      VisitorInitialiser visitor(ctx->args()->arg(i));
      child->accept(visitor);
      node.append_arg(child);
    }
  }
}

void VisitorInitialiser::visit(ASTIf &node) {
  auto ctx = m_context.as<CsharpParser::If_statementContext *>();
  node.set_first(ctx->ID(0)->getText());
  node.set_first_type("ID");
  if (ctx->ID().size() > 1) {
    node.set_first(ctx->ID(1)->getText());
    node.set_first_type("ID");

    node.set_op(ctx->LOGIC_OP()->getText());

  } else if (ctx->literal() != nullptr) {
    auto ctx_literal =
        visitLiteral(ctx->literal()).as<antlr4::tree::TerminalNode *>();
    node.set_second(ctx_literal->getText());
    if (ctx->literal()->NUMBER() != nullptr) {
      node.set_second_type("NUMBER");
    } else if (ctx->literal()->CHARv() != nullptr) {
      node.set_second_type("CHAR");
    } else if (ctx->literal()->FLOAT_NUMBER() != nullptr) {
      node.set_second_type("FLOAT");
    } else if (ctx->literal()->TEXT() != nullptr) {
      node.set_second_type("STRING");
    }
    node.set_op(ctx->LOGIC_OP()->getText());
  }
  if (ctx->scope() != nullptr) {
    auto child = new ASTScope;
    VisitorInitialiser visitor(ctx->scope());
    child->accept(visitor);
    child->set_scope_name("if" + node.get_first());
    node.set_scope(child);
  }
}

void VisitorInitialiser::visit(ASTKw &node) {
  auto ctx = m_context.as<CsharpParser::Kw_statementContext *>();
  node.set_kw(ctx->KEYWORD()->getText());
}

VisitorTraverse::VisitorTraverse(std::ofstream &os) : stream(os) {}

void VisitorTraverse::visit(ASTProgram &node) {
  for (std::size_t i = 0; i < node.get_depth(); i++) {
    stream << " ";
  }
  stream << "<program>\n";

  auto children = node.get_children();

  for (unsigned int i = 0; i < children.size(); i++) {
    node.increase_depth();
    children[i]->accept(*this);
    node.decrease_depth();
  }

  for (std::size_t i = 0; i < node.get_depth(); i++) {
    stream << " ";
  }
  stream << "</program>\n";
}

void VisitorTraverse::visit(ASTFunction &node) {
  set_indent(node.get_depth());
  stream << "<function name=\'" << node.func_name() << "\' ";
  node.set_dpsn(true);
  std::size_t tmp = node.get_depth();
  node.set_depth(0);
  if(!node.get_params().empty())
  {
    auto params = node.get_params();
    stream << "\b, params=(";
    for(std::size_t i = 0; i < params.size(); i++)
    {
      stream << params[i]->var_name() << ", ";
      stream << params[i]->var_type() << "; ";
    }
    stream << "\b\b";
    stream << "), ";
  }
  

  node.set_depth(tmp);
  node.set_dpsn(false);
  stream << "return-type=\'"
         << node.return_type() << "\'";
  if (node.get_return() != nullptr) {
    stream << ", return_statement=";
    node.get_return()->accept(*this);
  }
  stream << "/>\n";
  if (node.get_scope() != nullptr) {
    node.increase_depth();
    node.get_scope()->accept(*this);
    node.decrease_depth();
  }
}

void VisitorTraverse::visit(ASTVariable &node) {
  set_indent(node.get_depth());
  stream << "<variable name=\'" << node.var_name() << "\' type=\'"
         << node.var_type() << "\'/>";
  if(!node.get_dpsn())
  {
    stream << "\n";
  }
}

void VisitorTraverse::visit(ASTAssign &node) {
  set_indent(node.get_depth());
  stream << "<assign lhs=" << node.get_lvalue()->var_name() << ", rhs=";
  if (node.get_rvalue1() != nullptr) {
    if (node.get_rvalue2() != nullptr) {
      stream << "(" << node.get_rvalue1()->var_name() << ", "
             << node.get_rvalue2()->var_name() << "), op=\'" << node.get_oper()
             << "\'/>";
    } else {
      stream << node.get_rvalue1()->var_name() << ", op=\'" << node.get_oper()
             << "\'/>";
    }
  } else if (node.get_funccall() != nullptr) {
    std::size_t tmp = node.get_depth();
    node.set_dpsn(true);
    node.set_depth(0);
    node.get_funccall()->accept(*this);
    stream << ">";
    node.set_depth(tmp);
    node.decrease_depth();
    node.set_dpsn(false);
  }
  if (!node.get_dpsn()) {
    stream << "\n";
  }
}

void VisitorTraverse::visit(ASTFuncCall &node) {
  set_indent(node.get_depth());
  stream << "<call name=\'" << node.func_name() << "\', args=(";
  for (std::size_t i = 0; i < node.get_args().size(); i++) {

    node.get_arg(i)->accept(*this);

    if (i + 1 != node.get_args().size()) {
      stream << ", ";
    }
  }
  stream << ")/>";
  if (!node.get_dpsn()) {
    stream << "\n";
  }
}

void VisitorTraverse::visit(ASTScope &node) {
  // NOTE:
  set_indent(node.get_depth());
  stream << "<scope "
         << "name=\'" << node.get_scope_name() << "\'>\n";
  for (std::size_t i = 0; i < node.get_statements().size(); i++) {
    node.increase_depth();
    node.get_statement(i)->accept(*this);
    node.decrease_depth();
  }
  set_indent(node.get_depth());
  stream << "</scope>\n";
}

void VisitorTraverse::visit(ASTArgs &node) { stream << node.get_arg(); }

void VisitorTraverse::visit(ASTIf &node) {
  set_indent(node.get_depth());
  stream << "<if lhs=(value=" << node.get_first()
         << ", type=" << node.get_first_type() << ")";
  if (node.get_second() != "") {
    stream << ", lhs=(value=" << node.get_second()
           << ", type=" << node.get_second_type() << ")";
    stream << ", op=\'" << node.get_op() << "\'";
  }
  stream << ">\n";
  if (node.get_scope() != nullptr) {
    node.increase_depth();
    node.get_scope()->accept(*this);
    node.decrease_depth();
  }
}

void VisitorTraverse::visit(ASTReturn &node) {
  stream << "(value=" << node.get_return_value()
         << ", literal=" << node.is_literal()
         << ", type=" << node.get_return_type() << ")";
}

void VisitorTraverse::visit(ASTForOp &node) {
  if (node.get_assign() != nullptr) {
    stream << ", operation=(";
    node.get_assign()->accept(*this);
    stream << ")/>\n";
  } else {
    stream << ", operation=(" << node.get_id() << node.get_unary_op()
           << ")/>\n";
  }
}

void VisitorTraverse::visit(ASTForCond &node) {
  stream << ", condition=(" << node.get_first() << node.get_op()
         << node.get_second() << ")";
}

void VisitorTraverse::visit(ASTFor &node) {
  set_indent(node.get_depth());
  stream << "<for ";
  std::size_t tmp = node.get_depth();
  node.set_depth(0);
  node.set_dpsn(true);
  node.get_assing()->accept(*this);
  node.get_cond()->accept(*this);
  node.get_op()->accept(*this);
  node.set_dpsn(false);
  node.set_depth(tmp);
  node.get_scope()->accept(*this);
}

void VisitorTraverse::visit(ASTKw &node) {
  set_indent(node.get_depth());
  stream << "<keyword value=\'" << node.get_kw() << "\'/>\n";
}