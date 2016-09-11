#include <milk/ast/ast_var.hpp>

namespace milk {

ast_var::ast_var():
	type(new ast_sym_ref_type()) {
}

ast_var::~ast_var() {
	delete type;
}

void
ast_var::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

} // namespace milk

