#pragma once

#include "../util/header_guard.hpp"

#include "ast_node.hpp"
#include "ast_type.hpp"
#include "ast_sym_ref.hpp"

namespace milk {

class ast_sym_ref_type;

class ast_expr: public ast_node {
public:
	ast_expr();
	virtual ~ast_expr();

	ast_sym_ref_type* type;

	virtual void accept(visitor&) override;
};

} // namespace milk

