#include <milk/parser/parser.hpp>

#include <iostream>
#include <stdexcept>

namespace milk {

void parse_symbol(ast_symbol& parent, lexer& lexer) {
	switch (lexer.get().type) {
	case ttype::NS:
		ast_namespace* ns;
		try {
			ns = &dynamic_cast<ast_namespace&>(parent);
		} catch (...) {
			std::cerr << lexer.get().ref.pretty_string() << std::endl;
			std::runtime_error("parent of namespace must be a namespace too");
		}
		parse_namespace(*ns, lexer);
		break;
	case ttype::FN:
		parse_function(parent, lexer);
		break;
	default:
		std::cerr << lexer.get().ref.pretty_string() << std::endl;
		throw std::runtime_error("Unexpected token");
	}
}

void parse_namespace(ast_namespace& parent, lexer& lexer) {
	lexer.expect(ttype::NS);

	ast_namespace* current = &parent;
	do {
		lexer.advance();

		auto name = lexer.expect(ttype::ID).text;
		auto child = current->find_child(name);
		if (child) {
			current = dynamic_cast<ast_namespace*>(child);
			if (!current) {
				std::cerr << lexer.get().ref.pretty_string() << std::endl;
				throw std::runtime_error("symbol exists and is no namespace");
			}
		} else {
			current->children.emplace_back(new ast_namespace());
			current = static_cast<ast_namespace*>(current->children.back());
			current->name = name;
		}

		lexer.advance();
	} while(lexer.get().type == ttype::DCOL);

	lexer.expect(ttype::LBRACE);
	lexer.advance();
	
	while (lexer.get().type != ttype::RBRACE && lexer.get().type != ttype::EOS) {
		parse_symbol(*current, lexer);
	}

	lexer.expect(ttype::RBRACE);
	lexer.advance();
}

void parse_function(ast_symbol& parent, lexer& lexer) {
	lexer.expect(ttype::FN);
	lexer.advance();

	auto fn = new ast_func();
	parent.children.push_back(fn);
	fn->parent = &parent;

	fn->name = lexer.expect(ttype::ID).text;
	lexer.advance();
	lexer.expect(ttype::LPAR);
	lexer.advance();

	while (lexer.get().type != ttype::RPAR && lexer.get().type != ttype::EOS) {
		auto arg = new ast_var();
		arg->parent = fn;
		fn->children.push_back(arg);
		fn->args.push_back(arg);

		arg->name = lexer.expect(ttype::ID).text;
		lexer.advance();
		lexer.expect(ttype::COL);

		auto type = new ast_type_ref();
		arg->type = type;
		do {
			lexer.advance();
			type->path.push_back(lexer.expect(ttype::ID).text);
			lexer.advance();
		} while (lexer.get().type == ttype::DCOL);

		if (lexer.get().type == ttype::COMMA) {
			lexer.advance();
		} else {
			break;
		}
	}
	lexer.expect(ttype::RPAR);
	lexer.advance();

	lexer.expect(ttype::COL);
	auto type = new ast_type_ref();
	fn->return_type = type;
	do {
		lexer.advance();
		type->path.push_back(lexer.expect(ttype::ID).text);
		lexer.advance();
	} while (lexer.get().type == ttype::DCOL);

	if (lexer.get().type == ttype::ASSIGN) {
		lexer.advance();
		fn->body = parse_expression(*fn, lexer);
	}
}

// Left recursive expression parser
ast_expr* parse_add_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs = nullptr);
ast_expr* parse_mul_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs = nullptr);
ast_expr* parse_exp_expression(ast_symbol& parent, lexer& lexer, ast_expr* lhs = nullptr);
ast_expr* parse_primary_expression(ast_symbol& parent, lexer& lexer);

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

} // namespace milk
