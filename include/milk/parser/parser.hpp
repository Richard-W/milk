#pragma once

#include "../util/header_guard.hpp"

#include "../ast/ast_namespace.hpp"
#include "lexer.hpp"

namespace milk {

void parse_symbol(ast_symbol& parent, lexer&);
void parse_namespace(ast_namespace& parent, lexer&);

} // namespace milk
