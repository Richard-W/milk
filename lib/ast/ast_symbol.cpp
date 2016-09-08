#include <milk/ast/ast_symbol.hpp>

namespace milk {

void
ast_symbol::accept(visitor& visitor) {
	visitor.visit(*this);
	ast_node::accept(visitor);
}

ast_symbol::~ast_symbol() {
	for (auto child: children) {
		delete child;
	}
}

ast_symbol*
ast_symbol::find_child(const std::string& name) {
	for (auto child: children) {
		if (child->name == name) {
			return child;
		}
	}
	return nullptr;
}

} // namespace milk
