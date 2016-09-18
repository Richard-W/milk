#include <milk/parser/lexer.hpp>

#include <deque>
#include <iostream>
#include <stdexcept>

#define pop \
buffer.pop_front(); \
++pos

namespace milk {

lexer::lexer(const file& file) {
	std::string content = file.get_contents();
	std::deque<char> buffer(content.begin(), content.end());
	size_t pos = 0;

	while (!buffer.empty()) {
		// Consume whitespace
		while (std::isspace(buffer[0])) {
			pop;
		}
		if (buffer.empty()) {
			break;
		}

		// Consume comment
		if (buffer[0] == '/') {
			if (buffer[1] == '/') {
				// Discard until end of line
				while (!buffer.empty()) {
					if (buffer[0] == '\n') {
						pop;
						break;
					}
					pop;
				}
				continue;
			} else if (buffer[1] == '*') {
				// Discard until end of comment
				while (!buffer.empty()) {
					if (buffer[0] == '*' && buffer[1] == '/') {
						pop;
						pop;
						break;
					}
					pop;
				}
				continue;
			}
		}
		if (buffer.empty()) {
			break;
		}

		// Identifier or keyword
		if (std::isalpha(buffer[0])) {
			token tok;
			size_t tpos = pos;
			while (!buffer.empty() && (std::isalnum(buffer[0]) || buffer[0] == '_')) {
				tok.text.push_back(buffer[0]);
				pop;
			}
			tok.ref = file_ref(file, tpos, tok.text.size());
			if (tok.text == "if") {
				tok.type = ttype::IF;
			} else if (tok.text == "else") {
				tok.type = ttype::ELSE;
			} else if (tok.text == "for") {
				tok.type = ttype::FOR;
			} else if (tok.text == "while") {
				tok.type = ttype::WHILE;
			} else if (tok.text == "namespace") {
				tok.type = ttype::NS;
			} else if (tok.text == "fn") {
				tok.type = ttype::FN;
			} else if (tok.text == "return") {
				tok.type = ttype::RET;
			} else {
				tok.type = ttype::ID;
			}
			m_tokens.emplace_back(std::move(tok));
			continue;
		}

		// Numeric literal
		if (std::isdigit(buffer[0])) {
			token tok;
			size_t tpos = pos;
			while (!buffer.empty() && std::isdigit(buffer[0])) {
				tok.text.push_back(buffer[0]);
				pop;
			}
			if (!buffer.empty() && buffer[0] == '.' && std::isdigit(buffer[1])) {
				tok.type = ttype::FLIT;
				tok.text.push_back(buffer[0]);
				pop;
				while (!buffer.empty() && std::isdigit(buffer[0])) {
					tok.text.push_back(buffer[0]);
					pop;
				}
			} else {
				tok.type = ttype::ILIT;
			}
			tok.ref = file_ref(file, tpos, tok.text.size());
			m_tokens.emplace_back(std::move(tok));
			continue;
		}

		// String literal
		if (buffer[0] == '"') {
			token tok;
			size_t tpos = pos;
			size_t length_offset = 2;
			pop;
			while (!buffer.empty() && buffer[0] != '"') {
				if (buffer[0] == '\\' && buffer.size() > 1) {
					switch (buffer[1]) {
					case 'n':
						tok.text.push_back('\n');
						++length_offset;
						break;
					case 't':
						tok.text.push_back('\t');
						++length_offset;
						break;
					case '\"':
						tok.text.push_back('\"');
						++length_offset;
						break;
					case '\\':
						tok.text.push_back('\\');
						++length_offset;
						break;
					default:
						tok.text.push_back(buffer[0]);
						tok.text.push_back(buffer[1]);
						break;
					}
					pop;
					pop;
				} else {
					tok.text.push_back(buffer[0]);
					pop;
				}
			}
			if (buffer.empty()) {
				throw std::runtime_error("unterminated string");
			}
			pop;
			tok.ref = file_ref(file, tpos, tok.text.size() + length_offset);
			tok.type = ttype::SLIT;
			m_tokens.emplace_back(std::move(tok));
			continue;
		}

		// Special characters
		if (buffer[0] == '(') {
			token tok;
			tok.text = "(";
			tok.type = ttype::LPAR;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == ')') {
			token tok;
			tok.text = ")";
			tok.type = ttype::RPAR;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '{') {
			token tok;
			tok.text = "{";
			tok.type = ttype::LBRACE;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '}') {
			token tok;
			tok.text = "}";
			tok.type = ttype::RBRACE;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '[') {
			token tok;
			tok.text = "[";
			tok.type = ttype::LBRACK;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == ']') {
			token tok;
			tok.text = "]";
			tok.type = ttype::RBRACK;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == ',') {
			token tok;
			tok.text = ",";
			tok.type = ttype::COMMA;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '=') {
			token tok;
			tok.text = "=";
			tok.type = ttype::ASSIGN;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '+') {
			token tok;
			tok.text = "+";
			tok.type = ttype::PLUS;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '-') {
			token tok;
			tok.text = "-";
			tok.type = ttype::MINUS;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '*') {
			token tok;
			tok.text = "*";
			tok.type = ttype::TIMES;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '/') {
			token tok;
			tok.text = "/";
			tok.type = ttype::DIV;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '^') {
			token tok;
			tok.text = "^";
			tok.type = ttype::POW;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		} else if (buffer[0] == '.') {
			token tok;
			tok.text = ".";
			tok.type = ttype::DOT;
			tok.ref = file_ref(file, pos, 1);
			m_tokens.emplace_back(std::move(tok));
			pop;
			continue;
		}

		if (buffer[0] == ':') {
			token tok;
			size_t tpos = pos;
			tok.text.push_back(buffer[0]);
			pop;
			if (!buffer.empty() && buffer[0] == ':') {
				tok.text.push_back(buffer[0]);
				pop;
				tok.type = ttype::DCOL;
			} else {
				tok.type = ttype::COL;
			}
			tok.ref = file_ref(file, tpos, tok.text.size());
			m_tokens.emplace_back(std::move(tok));
			continue;
		}

		throw std::runtime_error("Unrecognized char");
	}
}

token
lexer::get(size_t index) {
	if (index >= m_tokens.size()) {
		token tok;
		tok.type = ttype::EOS;
		// FIXME: tok.ref
		return tok;
	} else {
		return m_tokens[index];
	}
}

token
lexer::expect(ttype type, size_t index) {
	token tok = get(index);
	if (tok.type != type) {
		std::cerr << tok.ref.pretty_string() << std::endl;
		throw std::runtime_error("lexer expectation failed");
	}
	return tok;
}

void
lexer::advance(size_t steps) {
	for (size_t i = 0; i < steps; ++i) {
		if (m_tokens.empty()) break;
		m_tokens.pop_front();
	}
}

} // namespace milk
