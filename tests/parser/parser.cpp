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
