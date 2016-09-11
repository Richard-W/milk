#pragma once

#include "../util/header_guard.hpp"

#include "ast_symbol.hpp"

namespace milk {

class ast_type: public ast_symbol {
public:
	ast_type() = default;

	virtual void accept(visitor&) override;
};

} // namespace milk
