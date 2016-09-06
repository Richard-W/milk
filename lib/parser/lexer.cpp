#include <milk/parser/lexer.hpp>

#include <deque>
#include <stdexcept>

#define pop \
buffer.pop_front(); \
++pos

#define chk_empty \

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
		if (std::isalnum(buffer[0])) {
			token tok;
			size_t tpos = pos;
			while ((std::isalnum(buffer[0]) || buffer[0] == '_') && !buffer.empty()) {
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
			} else {
				tok.type = ttype::ID;
			}
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
		}
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