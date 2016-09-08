#pragma once

#include "ast_symbol.hpp"
#include "ast_type.hpp"
#include "ast_var.hpp"

namespace milk {

class ast_func: public ast_symbol {
public:
	ast_func() = default;

	ast_type* return_type;
	std::vector<ast_var*> args;
	ast_expr* body;

	virtual void accept(visitor&) override;
};

} // namespace milk
