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

ast_expr* parse_expression(ast_symbol& parent, lexer& lexer) {
#pragma unused(parent)
#pragma unused(lexer)
	throw std::runtime_error("not implemented");
}

} // namespace milk
