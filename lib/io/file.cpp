#include <milk/io/file.hpp>

#include <cerrno>
#include <cstdio>
#include <system_error>

namespace milk {

file::file(const std::string& path):
	m_path(path) {
}

file&
file::operator=(const std::string& path) {
	m_path = path;
	return *this;
}

const std::string&
file::path() const noexcept {
	return m_path;
}

std::string
file::get_contents() const {
	std::FILE* fp = std::fopen(m_path.c_str(), "r");
	if (!fp) {
		throw std::system_error(std::error_code(errno, std::system_category()));
	}

	std::string contents;
	std::fseek(fp, 0, SEEK_END);
	try {
		contents.resize(std::ftell(fp));
	} catch (...) {
		std::fclose(fp);
		std::rethrow_exception(std::current_exception());
	}
	std::rewind(fp);
	std::fread(&contents[0], 1, contents.size(), fp);
	std::fclose(fp);
	
	return contents;
}

}
