#pragma once

#include "ast_symbol.hpp"
#include "ast_type.hpp"

namespace milk {

class ast_func: public ast_symbol {
public:
	ast_func() = default;

	ast_type* return_type;

	virtual void accept(visitor&) override;
};

} // namespace milk
