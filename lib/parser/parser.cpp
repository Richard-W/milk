#include <milk/parser/parser.hpp>

#include "symbol_parser.hpp"

#include <iostream>
#include <stdexcept>

namespace milk {

void parse(ast_symbol& parent, lexer& lexer) {
	while (lexer.get().type != ttype::EOS) {
		parse_symbol(parent, lexer);
	}
}

} // namespace milk
