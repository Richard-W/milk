#include <gtest/gtest.h>

#include <milk.hpp>

#include <fstream>

TEST(parser, namespaces) {
	std::ofstream os("./parser_namespaces.milk");
	os
		<< "namespace foo {" << std::endl
		<< "}" << std::endl
		<< "namespace bar {" << std::endl
		<< "	namespace baz {" << std::endl
		<< "	}" << std::endl
		<< "}" << std::endl
		<< "namespace foo {" << std::endl
		<< "	namespace foobar {" << std::endl
		<< "	}" << std::endl
		<< "}" << std::endl
		<< "namespace foo::bar {" << std::endl
		<< "	namespace baz {" << std::endl
		<< "	}" << std::endl
		<< "}" << std::endl;

	milk::file file("./parser_namespaces.milk");
	milk::lexer lexer(file);

	milk::ast_namespace root;
	milk::parse(root, lexer);

	ASSERT_EQ("foo", root.children[0]->name);
	ASSERT_EQ("foobar", root.children[0]->children[0]->name);
	ASSERT_EQ("bar", root.children[1]->name);
	ASSERT_EQ("baz", root.children[1]->children[0]->name);
}

TEST(parser, function_definitions) {
	std::ofstream os("./parser_function_definitions.milk");
	os
		<< "namespace foo {" << std::endl
		<< "	fn add(a: int, b: int): int" << std::endl
		<< "	fn mul(a: int, b: int): int" << std::endl
		<< "}" << std::endl;

	milk::file file("./parser_function_definitions.milk");
	milk::lexer lexer(file);

	milk::ast_namespace root;
	milk::parse(root, lexer);

	ASSERT_EQ("foo", root.children[0]->name);
	ASSERT_EQ("add", root.children[0]->children[0]->name);
	ASSERT_EQ("mul", root.children[0]->children[1]->name);
	ASSERT_EQ("int", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->return_type->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->return_type->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[0]->type->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[1]->type->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[0]->type->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[1]->type->path[0]);
	ASSERT_EQ("a", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[0]->name);
	ASSERT_EQ("b", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[1]->name);
	ASSERT_EQ("a", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[0]->name);
	ASSERT_EQ("b", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[1]->name);
}

TEST(parser, order_of_operations) {
	std::ofstream os("./parser_order_of_operations.milk");
	os
		<< "fn a(a: int, b: int): int = 1 + 2 + 3" << std::endl
		<< "fn b(a: int, b: int): int = 1 + 2 * 3" << std::endl
		<< "fn c(a: int, b: int): int = (1 + 2) * 3" << std::endl
		<< "fn d(): int = 1" << std::endl
		<< "fn e(a: int): int = 1" << std::endl;

	milk::file file("./parser_order_of_operations.milk");
	milk::lexer lexer(file);

	milk::ast_namespace root;
	milk::parse(root, lexer);

	ASSERT_EQ(1, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("a"))->body)->lhs)->lhs)->value);
	ASSERT_EQ(2, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("a"))->body)->lhs)->rhs)->value);
	ASSERT_EQ(3, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("a"))->body)->rhs)->value);

	ASSERT_EQ(1, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("b"))->body)->lhs)->value);
	ASSERT_EQ(2, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("b"))->body)->rhs)->lhs)->value);
	ASSERT_EQ(3, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("b"))->body)->rhs)->rhs)->value);

	ASSERT_EQ(1, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("c"))->body)->lhs)->lhs)->value);
	ASSERT_EQ(2, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("c"))->body)->lhs)->rhs)->value);
	ASSERT_EQ(3, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_bin_expr*>(dynamic_cast<milk::ast_func*>(root.find_child("c"))->body)->rhs)->value);
}

TEST(parser, var_refs) {
	const std::string fname("./parser_var_refs");
	std::ofstream os(fname);
	os
		<< "fn a(): int = b" << std::endl;

	milk::file file(fname);
	milk::lexer lexer(file);

	milk::ast_namespace root;
	milk::parse(root, lexer);

	ASSERT_EQ("b", dynamic_cast<milk::ast_var_ref*>(dynamic_cast<milk::ast_func*>(root.find_child("a"))->body)->var->path[0]);
}

TEST(parser, calls) {
	const std::string fname("./parser_calls");
	std::ofstream os(fname);
	os
		<< "fn a(): int = 1 + 2" << std::endl
		<< "fn b(foo: int): int = a() + foo" << std::endl
		<< "fn c(foo: int): int = b(foo) * foo" << std::endl
		<< "fn d(): int = b(5)" << std::endl;

	milk::file file(fname);
	milk::lexer lexer(file);

	milk::ast_namespace root;
	milk::parse(root, lexer);

	ASSERT_EQ(5, dynamic_cast<milk::ast_int_lit*>(dynamic_cast<milk::ast_call*>(dynamic_cast<milk::ast_func*>(root.find_child("d"))->body)->params[0])->value);
}
