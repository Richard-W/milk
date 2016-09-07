#pragma once

#include "../util/header_guard.hpp"

#include "ast_node.hpp"
#include "ast_type.hpp"

namespace milk {

class ast_expr: public ast_node {
public:
	ast_expr() = default;

	ast_type* type = nullptr;

	virtual void accept(visitor&) override;
};

} // namespace milk

