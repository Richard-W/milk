#include <milk/ast/ast_str_lit.hpp>

namespace milk {

void
ast_str_lit::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_expr::accept(visitor);
}

} // namespace milk

