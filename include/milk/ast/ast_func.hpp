#pragma once

#include "../util/header_guard.hpp"

#include "ast_symbol.hpp"
#include "ast_type.hpp"
#include "ast_var.hpp"
#include "ast_sym_ref.hpp"
#include "ast_expr.hpp"

namespace milk {

class ast_sym_ref_type;

class ast_func: public ast_symbol {
public:
	ast_func();
	virtual ~ast_func();

	ast_sym_ref_type* return_type;
	std::vector<ast_var*> args;
	ast_expr* body = nullptr;

	virtual void accept(visitor&) override;
};

} // namespace milk
