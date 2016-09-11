#include <milk/ast/ast_var_ref.hpp>

namespace milk {

ast_var_ref::ast_var_ref():
	var(new ast_sym_ref_var()) {
}

ast_var_ref::~ast_var_ref() {
	delete var;
}

void
ast_var_ref::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_expr::accept(visitor);
}

} // namespace milk




