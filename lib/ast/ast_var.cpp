#include <milk/ast/ast_var.hpp>

namespace milk {

void
ast_var::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

} // namespace milk

