#include <milk/ast/ast_type.hpp>

namespace milk {

void
ast_type::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

} // namespace milk

