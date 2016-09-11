#include <milk/ast/ast_sym_ref.hpp>

namespace milk {

void
ast_sym_ref::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_node::accept(visitor);
}

#define __MILK_SYM_REF(NAME) \
	void \
	ast_sym_ref_##NAME::resolve(ast_symbol& sym) { \
		value = &dynamic_cast<ast_##NAME&>(sym); \
	};

__MILK_SYM_REF(type);
__MILK_SYM_REF(func);
__MILK_SYM_REF(var);

#undef __MILK_SYM_REF

} // namespace milk
