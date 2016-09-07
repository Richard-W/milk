#pragma once

#include "../util/header_guard.hpp"

#include "token.hpp"

#include "../io/file.hpp"

#include <deque>

namespace milk {

class lexer {
public:
	lexer(const file& file);

	token get(size_t index = 0);
	token expect(ttype type, size_t index = 0);
	void advance(size_t steps = 1);

private:
	std::deque<token> m_tokens;
};

} // namespace milk
