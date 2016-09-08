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

	while (lexer.get().type != milk::ttype::EOS) {
		milk::parse_symbol(root, lexer);
	}

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

	while (lexer.get().type != milk::ttype::EOS) {
		milk::parse_symbol(root, lexer);
	}

	ASSERT_EQ("foo", root.children[0]->name);
	ASSERT_EQ("add", root.children[0]->children[0]->name);
	ASSERT_EQ("mul", root.children[0]->children[1]->name);
	ASSERT_EQ("int", dynamic_cast<milk::ast_type_ref*>(dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->return_type)->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_type_ref*>(dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->return_type)->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_type_ref*>(dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[0]->type)->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_type_ref*>(dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[1]->type)->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_type_ref*>(dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[0]->type)->path[0]);
	ASSERT_EQ("int", dynamic_cast<milk::ast_type_ref*>(dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[1]->type)->path[0]);
	ASSERT_EQ("a", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[0]->name);
	ASSERT_EQ("b", dynamic_cast<milk::ast_func*>(root.children[0]->children[0])->args[1]->name);
	ASSERT_EQ("a", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[0]->name);
	ASSERT_EQ("b", dynamic_cast<milk::ast_func*>(root.children[0]->children[1])->args[1]->name);
}
