#pragma once

#include "ast_expr.hpp"

namespace milk {

class ast_int_lit: public ast_expr {
public:
	ast_int_lit() = default;

	int64_t value;

	virtual void accept(visitor&) override;
};

} // namespace milk
