#include <milk/ast/ast_symbol.hpp>

namespace milk {

void
ast_symbol::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_node::accept(visitor);
}

} // namespace milk
