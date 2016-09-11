#include <milk/ast/ast_expr.hpp>

namespace milk {

ast_expr::ast_expr():
	type(new ast_sym_ref_type()) {
}

ast_expr::~ast_expr() {
	delete type;
}

void
ast_expr::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_node::accept(visitor);
}

} // namespace milk

