#include <gtest/gtest.h>

#include <milk.hpp>

#include <fstream>

TEST(file_ref, init) {
	milk::file_ref ref1;
	milk::file_ref ref2(milk::file("/dev/null"), 0, 0);
}

TEST(file_ref, values) {
	std::ofstream os("./file_ref_values_testfile");
	os 
		<< "abc" << std::endl
		<< "hello world" << std::endl
		<< "foo bar" << std::endl;
	os.close();

	milk::file_ref ref(milk::file("./file_ref_values_testfile"), 10, 5);
	ASSERT_EQ(2, ref.line());
	ASSERT_EQ(7, ref.col());
	ASSERT_EQ("hello world", ref.string());
}
