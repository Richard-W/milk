#pragma once

#include "../util/header_guard.hpp"

#include "../parser/visitor.hpp"

namespace milk {

class visitor;

class ast_node {
public:
	ast_node() = default;

	virtual void accept(visitor&);
};

} // namespace milk
