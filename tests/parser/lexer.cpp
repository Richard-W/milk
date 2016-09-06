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

TEST(lexer, literals) {
	std::ofstream os("./lexer_literals.milk");
	os << "123 123.0 1291 \"abc\" \"\\\"\"" << std::endl;

	milk::file file("./lexer_literals.milk");
	milk::lexer lexer(file);

	ASSERT_EQ(milk::ttype::ILIT, lexer.get().type);
	ASSERT_EQ("123", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::FLIT, lexer.get().type);
	ASSERT_EQ("123.0", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::ILIT, lexer.get().type);
	ASSERT_EQ("1291", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::SLIT, lexer.get().type);
	ASSERT_EQ("abc", lexer.get().text);
	lexer.advance();

	ASSERT_EQ(milk::ttype::SLIT, lexer.get().type);
	ASSERT_EQ("\"", lexer.get().text);
	lexer.advance();
}
