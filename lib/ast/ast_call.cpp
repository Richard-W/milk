#include <milk/ast/ast_call.hpp>

namespace milk {

ast_call::ast_call():
	callee(new ast_sym_ref_func()) {
}

ast_call::~ast_call() {
	delete callee;
	for (auto param: params) {
		delete param;
	}
}

void
ast_call::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_expr::accept(visitor);
}

} // namespace milk



