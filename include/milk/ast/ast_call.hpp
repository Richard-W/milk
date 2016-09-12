#pragma once

#include "../util/header_guard.hpp"

#include "ast_expr.hpp"
#include "ast_sym_ref.hpp"

#include <vector>

namespace milk {

class ast_call: public ast_expr {
public:
	ast_call();
	virtual ~ast_call();

	ast_sym_ref_func* callee;
	std::vector<ast_expr*> params;

	virtual void accept(visitor&) override;
};

} // namespace milk
