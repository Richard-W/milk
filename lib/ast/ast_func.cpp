#include <milk/ast/ast_func.hpp>

namespace milk {

void
ast_func::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

} // namespace milk



