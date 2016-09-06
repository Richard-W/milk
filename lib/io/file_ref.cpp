#include <milk/io/file_ref.hpp>

#include <sstream>
#include <stdexcept>

namespace milk {

file_ref::file_ref(const file& file, size_t pos, size_t len):
	m_file(file),
	m_pos(pos),
	m_len(len) {
}

size_t
file_ref::line() const noexcept {
	if (m_line == 0) eval();
	return m_line;
}

size_t
file_ref::col() const noexcept {
	if (m_col == 0) eval();
	return m_col;
}

const std::string&
file_ref::string() const noexcept {
	if (m_line == 0) eval();
	return m_line_str;
}

std::string
file_ref::pretty_string() const {
	std::stringstream ss;
	ss << "Line " << line() << " column " << col() << std::endl;
	ss << string() << std::endl;

	for (size_t i = 1; i < col(); ++i) {
		ss << ' ';
	}
	for (size_t i = 0; i < m_len; ++i) {
		ss << '^';
	}
	ss << std::endl;

	return ss.str();
}

void
file_ref::eval() const {
	std::string contents = m_file.get_contents();
	++m_line;
	++m_col;

	size_t i = 0;
	for (auto ch: contents) {
		if (ch == '\n') {
			if (i > m_pos) {
				break;
			} else {
				++m_line;
				m_col = 1;
				m_line_str = "";
			}
		} else {
			if (i < m_pos) {
				++m_col;
			}
			m_line_str += ch;
		}
		++i;
	}
	if (i < m_pos + m_len) {
		throw std::runtime_error("file_ref: no such position");
	}
}

} // namespace milk
