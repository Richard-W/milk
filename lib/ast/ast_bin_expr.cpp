#include <milk/ast/ast_bin_expr.hpp>

namespace milk {

void
ast_bin_expr::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_expr::accept(visitor);
}

} // namespace milk


