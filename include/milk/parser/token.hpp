#pragma once

#include "../util/header_guard.hpp"

#include "../io/file.hpp"
#include "../io/file_ref.hpp"

namespace milk {

enum class ttype {
	ID,
	IF,
	ELSE,
	FOR,
	WHILE,
	RET,
	EOS,
	LPAR,
	RPAR,
	LBRACE,
	RBRACE,
	LBRACK,
	RBRACK,
	ILIT,
	FLIT,
	SLIT,
	NS,
	DOT,
	COL,
	DCOL,
	FN,
	COMMA,
	ASSIGN,
	PLUS,
	MINUS,
	TIMES,
	DIV,
	POW,
};

struct token {
	ttype type;
	std::string text;
	file_ref ref;
};

}
