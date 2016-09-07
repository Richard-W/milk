#pragma once

#include "../util/header_guard.hpp"

#include "ast_node.hpp"

#include <string>
#include <vector>

namespace milk {

class ast_symbol: public ast_node {
public:
	ast_symbol() = default;

	std::string name;
	ast_symbol* parent = nullptr;
	std::vector<ast_symbol*> children;

	virtual void accept(visitor&) override;
};

} // namespace milk
