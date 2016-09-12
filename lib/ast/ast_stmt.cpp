#include <milk/ast/ast_stmt.hpp>

namespace milk {

void
ast_stmt::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_node::accept(visitor);
}

} // namespace milk
