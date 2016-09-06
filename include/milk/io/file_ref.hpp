#pragma once

#include "file.hpp"

#include <cstddef>

namespace milk {

class file_ref {
public:
	file_ref() = default;
	file_ref(const file& file, size_t pos, size_t len);

	size_t line() const noexcept;
	size_t col() const noexcept;
	const std::string& string() const noexcept;

	std::string pretty_string() const;

private:
	file m_file;
	size_t m_pos;
	size_t m_len;

	mutable size_t m_line = 0;
	mutable size_t m_col = 0;
	mutable std::string m_line_str;

	void eval() const;
};

} // namespace milk
