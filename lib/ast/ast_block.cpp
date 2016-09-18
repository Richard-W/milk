#include <milk/ast/ast_block.hpp>

namespace milk {

void
ast_block::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_expr::accept(visitor);
}

} // namespace milk
