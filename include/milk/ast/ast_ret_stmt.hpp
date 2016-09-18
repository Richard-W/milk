#pragma once

#include "../util/header_guard.hpp"

#include "ast_expr.hpp"
#include "ast_stmt.hpp"

namespace milk {

class ast_ret_stmt: public ast_stmt {
public:
	ast_ret_stmt() = default;
	~ast_ret_stmt();

	ast_expr* value = nullptr;

	virtual void accept(visitor&) override;
};

} // namespace milk

