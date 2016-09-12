#pragma once

#include "ast_node.hpp"

namespace milk {

class ast_stmt: public ast_node {
public:
	ast_stmt() = default;

	virtual void accept(visitor&) override;
};

} // namespace milk
