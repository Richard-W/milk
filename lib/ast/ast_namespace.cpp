#include <milk/ast/ast_namespace.hpp>

namespace milk {

void
ast_namespace::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

} // namespace milk


