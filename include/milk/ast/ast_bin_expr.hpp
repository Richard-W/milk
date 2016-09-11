#pragma once

#include "../util/header_guard.hpp"

#include "ast_expr.hpp"

namespace milk {

class ast_bin_expr: public ast_expr {
public:
	ast_bin_expr() = default;

	ast_expr* lhs;
	ast_expr* rhs;
	std::string op;

	virtual void accept(visitor&) override;
};

} // namespace milk
