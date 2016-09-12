#include "expr_parser.hpp"

#include <milk.hpp>

#include <iostream>

namespace milk {

// Left recursive expression parser
ast_expr* parse_add_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs = nullptr);
ast_expr* parse_mul_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs = nullptr);
ast_expr* parse_exp_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs = nullptr);
ast_expr* parse_primary_expression(ast_symbol& parent, lexer& lexer);
ast_call* parse_call(ast_symbol& parent, lexer& lexer, std::vector<std::string> path);
ast_expr* parse_ref_or_call(ast_symbol& parent, lexer& lexer);

ast_expr* parse_expression(ast_symbol& parent, lexer& lexer) {
	return parse_add_expression(parent, lexer);
}

/* The following three function implement the parsing of arithmetic expressions
 * in the correct order.
 *
 * Take the expression 2 - 2 - 2
 * The correct parenthesised expression would be
 * (2 - 2) - 2 = -2
 *
 * A naive right-recursive approach would yield
 * 2 - (2 - 2) = 2
 */

ast_expr* parse_add_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs) {
	if (!lhs) {
		lhs = parse_mul_expression(parent, lexer);
	}
	if (lexer.get().type == ttype::PLUS || lexer.get().type == ttype::MINUS) {
		auto bin = new ast_bin_expr();
		bin->op = lexer.get().text;
		lexer.advance();
		bin->lhs = lhs;
		bin->rhs = parse_mul_expression(parent, lexer);
		return parse_add_expression(parent, lexer, bin);
	} else {
		return lhs;
	}
}

ast_expr* parse_mul_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs) {
	if (!lhs) {
		lhs = parse_exp_expression(parent, lexer);
	}
	if (lexer.get().type == ttype::TIMES || lexer.get().type == ttype::DIV) {
		auto bin = new ast_bin_expr();
		bin->op = lexer.get().text;
		lexer.advance();
		bin->lhs = lhs;
		bin->rhs = parse_exp_expression(parent, lexer);
		return parse_mul_expression(parent, lexer, bin);
	} else {
		return lhs;
	}
}

ast_expr* parse_exp_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs) {
	if (!lhs) {
		lhs = parse_primary_expression(parent, lexer);
	}
	if (lexer.get().type == ttype::TIMES || lexer.get().type == ttype::DIV) {
		auto bin = new ast_bin_expr();
		bin->op = lexer.get().text;
		lexer.advance();
		bin->lhs = lhs;
		bin->rhs = parse_primary_expression(parent, lexer);
		return parse_exp_expression(parent, lexer, bin);
	} else {
		return lhs;
	}
}

ast_expr* parse_ref_or_call(ast_symbol& parent, lexer& lexer);

ast_expr* parse_primary_expression(ast_symbol& parent, lexer& lexer) {
	switch (lexer.get().type) {
	case ttype::LPAR: {
		lexer.advance();
		auto expr = parse_expression(parent, lexer);
		lexer.expect(ttype::RPAR);
		lexer.advance();
		return expr;
	}
	case ttype::SLIT: {
		auto expr = new ast_str_lit();
		expr->value = lexer.get().text;
		lexer.advance();
		return expr;
	}
	case ttype::ILIT: {
		auto expr = new ast_int_lit();
		expr->value = std::atol(lexer.get().text.c_str());
		lexer.advance();
		return expr;
	}
	default:
		std::cerr << lexer.get().ref.pretty_string() << std::endl;
		throw std::runtime_error("Expected expression");
	}
}

ast_expr* parse_ref_or_call(ast_symbol& parent, lexer& lexer) {
	std::vector<std::string> path;
	while (lexer.get().type != ttype::EOS) {
		path.push_back(lexer.expect(ttype::ID).text);
		lexer.advance();
		if (lexer.get().type == ttype::DCOL) {
			lexer.advance();
		} else {
			break;
		}
	}

	if (lexer.get().type == ttype::LPAR) {
		return parse_call(parent, lexer, path);
	} else {
		auto ref = new ast_var_ref();
		ref->var->path = path;
		return ref;
	}
}

ast_call* parse_call(ast_symbol& parent, lexer& lexer, std::vector<std::string> path) {

}

} // namespace milk

