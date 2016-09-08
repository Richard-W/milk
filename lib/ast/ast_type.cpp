#include <milk/ast/ast_type.hpp>

namespace milk {

void
ast_type::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

void
ast_type_ref::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_type::accept(visitor);
}

} // namespace milk

