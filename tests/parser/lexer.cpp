#include <gtest/gtest.h>

#include <milk.hpp>

#include <fstream>

TEST(lexer, key_id_comment) {
	std::ofstream os("./lexer_key_id_comment.milk");
	os
		<< "    " << std::endl
		<< "abc (// some identifier" << std::endl
		<< "def }/* some comment */ if ghi" << std::endl;

	milk::file file("./lexer_key_id_comment.milk");
	milk::lexer lexer(file);

	ASSERT_EQ(milk::ttype::ID, lexer.get().type);
	ASSERT_EQ("abc", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::LPAR, lexer.get().type);
	ASSERT_EQ("(", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::ID, lexer.get().type);
	ASSERT_EQ("def", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::RBRACE, lexer.get().type);
	ASSERT_EQ("}", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::IF, lexer.get().type);
	ASSERT_EQ("if", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::ID, lexer.get().type);
	ASSERT_EQ("ghi", lexer.get().text);
	lexer.advance();
}
