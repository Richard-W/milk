#pragma once

#define __MILK_HPP

#include "milk/ast/ast_node.hpp"
#include "milk/ast/ast_symbol.hpp"
#include "milk/ast/ast_type.hpp"
#include "milk/ast/ast_expr.hpp"
#include "milk/ast/ast_bin_expr.hpp"
#include "milk/ast/ast_namespace.hpp"
#include "milk/ast/ast_func.hpp"
#include "milk/ast/ast_var.hpp"
#include "milk/ast/ast_str_lit.hpp"
#include "milk/ast/ast_int_lit.hpp"
#include "milk/ast/ast_call.hpp"
#include "milk/ast/ast_sym_ref.hpp"
#include "milk/ast/ast_var_ref.hpp"
#include "milk/ast/ast_stmt.hpp"
#include "milk/ast/ast_block.hpp"
#include "milk/ast/ast_ret_stmt.hpp"

#include "milk/io/file.hpp"
#include "milk/io/file_ref.hpp"

#include "milk/parser/lexer.hpp"
#include "milk/parser/visitor.hpp"
#include "milk/parser/parser.hpp"
