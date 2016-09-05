#include <gtest/gtest.h>

#include <milk.hpp>

#include <fstream>

TEST(file, init) {
	milk::file f1;
	f1 = "/dev/null";

	milk::file f2("/dev/null");
}

TEST(file, read) {
	std::ofstream os("./file_read_testfile");
	os << "hello world";
	os.close();

	milk::file f("./file_read_testfile");
	ASSERT_EQ("hello world", f.get_contents());
}
