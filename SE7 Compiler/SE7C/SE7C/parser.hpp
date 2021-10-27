#ifndef SE7_PARSER
#define SE7_PARSER

#include "lexer.hpp"
#include "token.hpp"

#include <stdexcept>

class parsing_exception : std::runtime_error {
public:
	parsing_exception();
};

class parser {
private:
	lexer l;
	token current_token;
	token peek_token;
public:
	parser(lexer &&other_l);

	bool check_token(token_type type);
	bool check_peek(token_type type);
	bool match(token_type type);
	void next_token();
	void abort();
	void program();
	void expression();
};

#endif
