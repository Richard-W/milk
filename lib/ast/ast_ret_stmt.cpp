#include <milk/ast/ast_ret_stmt.hpp>

namespace milk {

ast_ret_stmt::~ast_ret_stmt() {
	if (value) {
		delete value;
	}
}

void
ast_ret_stmt::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_stmt::accept(visitor);
}

} // namespace milk



