#pragma once

#include "../util/header_guard.hpp"

#include "ast_node.hpp"

#include <string>
#include <vector>

namespace milk {

class ast_symbol: public ast_node {
public:
	ast_symbol() = default;
	virtual ~ast_symbol() override;

	std::string name;
	ast_symbol* parent = nullptr;
	std::vector<ast_symbol*> children;

	ast_symbol* find_child(const std::string& name);

	virtual void accept(visitor&) override;
};

} // namespace milk
