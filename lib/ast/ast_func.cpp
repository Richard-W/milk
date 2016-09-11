#include <milk/ast/ast_func.hpp>

namespace milk {

ast_func::ast_func():
	return_type(new ast_sym_ref_type()) {
}

ast_func::~ast_func() {
	delete return_type;
	if (body) {
		delete body;
	}
}

void
ast_func::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_symbol::accept(visitor);
}

} // namespace milk



