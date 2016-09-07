#pragma once

#include "../util/header_guard.hpp"

namespace milk {

class ast_node;
class ast_symbol;
class ast_type;
class ast_expr;

class visitor {
public:
	virtual void visit(ast_node&) {}
	virtual void visit(ast_symbol&) {}
	virtual void visit(ast_type&) {}
	virtual void visit(ast_expr&) {}
};

} // namespace milk
