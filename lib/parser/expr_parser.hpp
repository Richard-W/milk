#pragma once

#include <milk/ast/ast_symbol.hpp>
#include <milk/parser/lexer.hpp>

namespace milk {

ast_expr* parse_expression(ast_symbol& parent, lexer& lexer);

} // namespace milk
