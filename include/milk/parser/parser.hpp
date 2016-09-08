#pragma once

#include "../util/header_guard.hpp"

#include "../../milk.hpp"

namespace milk {

void parse_symbol(ast_symbol& parent, lexer&);
void parse_namespace(ast_namespace& parent, lexer&);
void parse_function(ast_symbol& parent, lexer&);

ast_expr* parse_expression(ast_symbol& parent, lexer&);

} // namespace milk
