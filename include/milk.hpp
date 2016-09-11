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

#include "milk/io/file.hpp"
#include "milk/io/file_ref.hpp"

#include "milk/parser/lexer.hpp"
#include "milk/parser/visitor.hpp"
#include "milk/parser/parser.hpp"
