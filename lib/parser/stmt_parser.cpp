#include "stmt_parser.hpp"
#include "expr_parser.hpp"

#include <milk.hpp>

#include <iostream>
#include <stdexcept>

namespace milk {

ast_ret_stmt* parse_ret_stmt(ast_symbol& parent, lexer& lexer);

ast_stmt* parse_stmt(ast_symbol& parent, lexer& lexer) {
	switch (lexer.get().type) {
	case ttype::RET: {
		return parse_ret_stmt(parent, lexer);
	}
	default:
		std::cerr << lexer.get().ref.pretty_string();
		throw std::runtime_error("Expected statement");
	}
}

ast_ret_stmt* parse_ret_stmt(ast_symbol& parent, lexer& lexer) {
	lexer.expect(ttype::RET);
	lexer.advance();
	
	auto stmt = new ast_ret_stmt();
	stmt->value = parse_expression(parent, lexer);
	return stmt;
}

} // namespace milk
