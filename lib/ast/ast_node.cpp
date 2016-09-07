#include <milk/ast/ast_node.hpp>

namespace milk {

void
ast_node::accept(visitor& visitor) {
	visitor.visit(*this);
}

} // namespace milk
