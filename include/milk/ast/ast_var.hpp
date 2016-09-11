#pragma once

#include "../util/header_guard.hpp"

#include "ast_symbol.hpp"
#include "ast_sym_ref.hpp"

namespace milk {

class ast_sym_ref_type;

class ast_var: public ast_symbol {
public:
	ast_var();
	virtual ~ast_var();

	ast_sym_ref_type* type;
	ast_expr* expr = nullptr;

	virtual void accept(visitor&) override;
};

} // namespace milk
