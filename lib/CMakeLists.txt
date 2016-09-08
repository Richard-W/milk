add_library(milk SHARED
	"ast/ast_expr.cpp"
	"ast/ast_func.cpp"
	"ast/ast_namespace.cpp"
	"ast/ast_node.cpp"
	"ast/ast_symbol.cpp"
	"ast/ast_type.cpp"
	"ast/ast_var.cpp"
	"io/file.cpp"
	"io/file_ref.cpp"
	"parser/lexer.cpp"
	"parser/parser.cpp"
)
target_compile_definitions(milk PRIVATE __MILK_BUILD)
