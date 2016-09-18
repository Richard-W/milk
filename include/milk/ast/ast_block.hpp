#pragma once

#include "../util/header_guard.hpp"

#include "ast_expr.hpp"

#include <vector>

namespace milk {

class ast_block: public ast_expr {
public:
	ast_block() = default;

	std::vector<ast_stmt*> stmt_list;

	virtual void accept(visitor&) override;
};

} // namespace milk
