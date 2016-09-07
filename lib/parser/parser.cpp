#include <milk/parser/parser.hpp>

#include <iostream>
#include <stdexcept>

namespace milk {

void parse_symbol(ast_symbol& parent, lexer& lexer) {
	switch (lexer.get().type) {
	case ttype::NS:
		parse_namespace(dynamic_cast<ast_namespace&>(parent), lexer);
		break;
	default:
		std::cerr << lexer.get().ref.pretty_string() << std::endl;
		throw std::runtime_error("Unexpected token");
	}
}

void parse_namespace(ast_namespace& parent, lexer& lexer) {
	lexer.expect(ttype::NS);
	lexer.advance();

	ast_namespace* current = new ast_namespace();
	parent.children.emplace_back(current);
	current->name = lexer.expect(ttype::ID).text;
	lexer.advance();

	while (lexer.get().type == ttype::DOT) {
		lexer.advance();

		current->children.emplace_back(new ast_namespace());
		current = dynamic_cast<ast_namespace*>(current->children.back());
		current->name = lexer.expect(ttype::ID).text;
		lexer.advance();
	}

	lexer.expect(ttype::LBRACE);
	lexer.advance();
	
	while (lexer.get().type != ttype::RBRACE && lexer.get().type != ttype::EOS) {
		parse_symbol(*current, lexer);
	}

	lexer.expect(ttype::RBRACE);
	lexer.advance();
}

} // namespace milk
