#ifndef SE7_LEXER
#define SE7_LEXER

#include <iostream>
#include <fstream>
#include <string>
#include <cstdint>
#include <stdexcept>
#include <map>

#include "token.hpp"

class lexing_exception : public std::runtime_error {
public:
	lexing_exception();
};

extern std::map<std::string, token_type> types;
extern const std::map<std::string, token_type> modifiers;
extern const std::map<std::string, token_type> operators;
extern const std::map<std::string, token_type> protections;
extern const std::map<std::string, token_type> other_keywords;

class lexer {
private:
	std::fstream source;
	int current_char;
	int current_position;
	const std::uintmax_t file_size;
public:
	lexer(const std::string &filepath);
	lexer(lexer &&other) noexcept;

	void next_char();
	int peek();
	void abort();
	void skip_whitespace();
	void skip_comment();
	void skip_semicolon();
	token get_token();
	bool at_eof();
	~lexer();
};

#endif

