#pragma once

#include "../util/header_guard.hpp"

#include "ast_expr.hpp"

#include <string>

namespace milk {

class ast_str_lit: public ast_expr {
public:
	ast_str_lit() = default;

	std::string value;

	virtual void accept(visitor& visitor) override;
};

}
