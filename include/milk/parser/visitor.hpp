#pragma once

#include "../util/header_guard.hpp"

namespace milk {

class ast_node;
class ast_symbol;
class ast_type;
class ast_expr;
class ast_bin_expr;
class ast_namespace;
class ast_func;
class ast_var;
class ast_str_lit;
class ast_int_lit;
class ast_call;
class ast_sym_ref;
class ast_var_ref;
class ast_stmt;
class ast_block;
class ast_ret_stmt;

class visitor {
public:
	virtual void visit(ast_node&) {}
	virtual void visit(ast_symbol&) {}
	virtual void visit(ast_type&) {}
	virtual void visit(ast_expr&) {}
	virtual void visit(ast_bin_expr&) {}
	virtual void visit(ast_namespace&) {}
	virtual void visit(ast_func&) {}
	virtual void visit(ast_var&) {}
	virtual void visit(ast_str_lit&) {}
	virtual void visit(ast_int_lit&) {}
	virtual void visit(ast_call&) {}
	virtual void visit(ast_sym_ref&) {}
	virtual void visit(ast_var_ref&) {}
	virtual void visit(ast_stmt&) {}
	virtual void visit(ast_block&) {}
	virtual void visit(ast_ret_stmt&) {}
};

} // namespace milk
