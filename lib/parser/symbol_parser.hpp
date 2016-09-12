#pragma once

#include <milk/ast/ast_symbol.hpp>
#include <milk/parser/lexer.hpp>

namespace milk {

void parse_symbol(ast_symbol& parent, lexer& lexer);

} // namespace milk
