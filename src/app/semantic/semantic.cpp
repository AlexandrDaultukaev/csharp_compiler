#include "grammar/CsharpVisitor.h"
#include "semantic.hpp"

#include <any>
#include <fstream>
#include <iostream>

SemanticVisitor::visit(ASTProgram& node)
{
    for(auto& child : node.get_children())
    {
        child->accept(*this);
    }
}