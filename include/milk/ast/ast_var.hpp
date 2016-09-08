#pragma once

#include "ast_symbol.hpp"

namespace milk {

class ast_var: public ast_symbol {
public:
	ast_var() = default;

	ast_type* type;
	ast_expr* expr;

	virtual void accept(visitor&) override;
};

} // namespace milk
