#pragma once

#include "../util/header_guard.hpp"

#include "ast_symbol.hpp"

namespace milk {

class ast_namespace: public ast_symbol {
public:
	ast_namespace() = default;

	virtual void accept(visitor&) override;
};

} // namespace milk
