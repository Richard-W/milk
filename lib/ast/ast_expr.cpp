#include <milk/ast/ast_expr.hpp>

namespace milk {

void
ast_expr::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_node::accept(visitor);
}

} // namespace milk

