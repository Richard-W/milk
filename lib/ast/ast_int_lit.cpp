#include <milk/ast/ast_int_lit.hpp>

namespace milk {

void
ast_int_lit::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_expr::accept(visitor);
}

} // namespace milk

