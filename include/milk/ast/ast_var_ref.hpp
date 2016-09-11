#pragma once

#include "ast_expr.hpp"
#include "ast_sym_ref.hpp"

namespace milk {

class ast_var_ref: public ast_expr {
public:
	ast_var_ref();
	virtual ~ast_var_ref();

	ast_sym_ref_var* var;

	virtual void accept(visitor&) override;
};

} // namespace milk
