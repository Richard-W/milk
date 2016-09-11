#pragma once

#include "../util/header_guard.hpp"

#include "ast_node.hpp"
#include "ast_symbol.hpp"
#include "ast_type.hpp"
#include "ast_func.hpp"
#include "ast_var.hpp"

namespace milk {

class ast_symbol;
class ast_type;
class ast_func;
class ast_var;

class ast_sym_ref: public ast_node {
public:
	ast_sym_ref() = default;

	std::vector<std::string> path;

	virtual void accept(visitor&) override;

	virtual void resolve(ast_symbol&) = 0;
};

#define __MILK_SYM_REF(NAME) \
	class ast_sym_ref_##NAME: public ast_sym_ref { \
	public: \
		ast_sym_ref_##NAME() = default; \
		virtual void resolve(ast_symbol&) override; \
		ast_##NAME* value = nullptr; \
	}

__MILK_SYM_REF(type);
__MILK_SYM_REF(func);
__MILK_SYM_REF(var);

#undef __MILK_SYM_REF

} // namespace milk
