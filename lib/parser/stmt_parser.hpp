#pragma once

#include <milk/ast/ast_stmt.hpp>
#include <milk/parser/lexer.hpp>

namespace milk {

ast_stmt* parse_stmt(ast_symbol& parent, lexer&);

} // namespace milk
