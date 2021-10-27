#include "lexer.hpp"
#include "log.hpp"
#include "token.hpp"

#include <filesystem>
#include <cstdlib>
#include <cctype>
#include <type_traits>

lexing_exception::lexing_exception() : 
	std::runtime_error("An error occurred whilst lexing the source file") 
{}

lexer::lexer(const std::string &filepath) : 
	source(filepath, std::ios_base::in),
	current_char(-1),
	current_position(-1),
	file_size(std::filesystem::file_size(filepath))
{
	if (!this->source.is_open()) {
		fatal("Could not open file");
		this->abort();
	}

	this->next_char();
}

lexer::lexer(lexer &&other) noexcept :
	source(std::move(other.source)),
	current_char(other.current_char),
	current_position(other.current_position),
	file_size(other.file_size) {}

void lexer::next_char() {
	this->current_position++;

	if (this->current_position > this->file_size) {
		this->current_char = std::fstream::traits_type::eof();
	} else {
		this->current_char = this->source.get();
	}
}

int lexer::peek() {
#pragma warning(disable:26451)
	if (this->current_position + 1 >= this->file_size) {
		return std::fstream::traits_type::eof();
	}
#pragma warning(restore:26451)

	return this->source.peek();
}

void lexer::abort() {
	throw lexing_exception();
}

bool is_whitespace(int c) {
	return c == ' ' ||
		c == '\t' ||
		c == '\r' ||
		c == '\n';
}

void lexer::skip_whitespace() {
	while (
		is_whitespace(this->current_char)
	) {
		this->next_char();
	}
}

void lexer::skip_comment() {
	if (this->current_char == '/') {
		int peek = this->source.peek();

		if (peek == '/') {
			while (this->current_char != '\n') {
				this->next_char();
			}

			this->next_char();
		} else if (peek == '*') {
			while (this->current_char != '*' && this->source.peek() != '/') {
				this->next_char();
			}

			this->next_char();
			this->next_char();
		}
	}
}

void lexer::skip_semicolon() {
	while (this->current_char == ';') {
		this->next_char();
	}
}

// Stores primitives and non - primitives
std::map<std::string, token_type> types = {
	// TODO: Swap keys and values
	{ "byte", token_type::byte_type },
	{ "bool", token_type::bool_type },
	{ "char", token_type::char_type },
	{ "wchar", token_type::wchar_type },
	{ "short", token_type::short_type },
	{ "int", token_type::int_type },
	{ "long", token_type::long_type },
	{ "long long", token_type::long_long_type },
	{ "float", token_type::float_type },
	{ "double", token_type::double_type },
	{ "string", token_type::string_type },
	{ "wstring", token_type::wstring_type },
	{ "thread", token_type::thread_type },
};

const std::map<std::string, token_type> modifiers = {
	{ "const", token_type::const_modifier },
	{ "static", token_type::static_modifier },
	{ "volatile", token_type::volatile_modifier },
	{ "unsigned", token_type::unsigned_modifier },
	{ "mutable", token_type::mutable_modifier },
	{ "abstract", token_type::abstract_modifier },
	{ "final", token_type::final_modifier },
	{ "virtual", token_type::virtual_modifier },
	{ "restrict", token_type::restrict_modifier },
	{ "generic", token_type::generic_modifier },
};

const std::map<std::string, token_type> operators = {
	{ "+", token_type::plus },
	{ "-", token_type::minus },
	{ "*", token_type::star },
	{ "/", token_type::forward_slash },
	{ "\\", token_type::backward_slash },
	{ "%", token_type::percent },
	{ "=", token_type::equals },
	{ "!", token_type::exclamation_mark },
	{ "&", token_type::ampersands },
	{ "|", token_type::bar },
	{ "~", token_type::tilde },
	{ "^", token_type::hat },
	{ "&&", token_type::double_ampersands },
	{ "||", token_type::double_bar },
	{ "==", token_type::double_equals },
	{ "!=", token_type::exclamation_equals },
	{ "+=", token_type::plus_equals },
	{ "-=", token_type::minus_equals },
	{ "*=", token_type::star_equals },
	{ "/=", token_type::forward_slash_equals },
	{ "\\=", token_type::backward_slash_equals },
	{ "%=", token_type::percent_equals },
	{ "&=", token_type::ampersands_equals },
	{ "|=", token_type::bar_equals },
	{ "^=", token_type::hat_equals },
	{ "++", token_type::double_plus },
	{ "--", token_type::double_minus },
	{ "**", token_type::double_star },
	{ "//", token_type::double_forward_slash },
	{ "\\\\", token_type::double_backward_slash },
	{ "%%", token_type::double_percent },
	{ "<", token_type::less },
	{ "<=", token_type::less_equal },
	{ ">", token_type::greater },
	{ ">=", token_type::greater_equal },
	{ "<<", token_type::bit_left },
	{ "<<=", token_type::bit_left_equals },
	{ ">>", token_type::bit_right },
	{ ">>=", token_type::bit_right_equals },
	{ "await", token_type::await },
	{ "thread_launch", token_type::thread_launch },
	{ "sleep", token_type::sleep },
	{ "detach", token_type::detach },
	{ "wait_for", token_type::wait_for },
	{ "asm", token_type::____asm },
	{ ".", token_type::dot },
	{ "::", token_type::scope },
};

const std::map<std::string, token_type> protections = {
	{ "public", token_type::protection_public },
	{ "private", token_type::protection_private },
	{ "protected", token_type::protection_protected },
};

const std::map<std::string, token_type> other_keywords = {
	{ "class", token_type::__class },
	{ "struct", token_type::__struct },
	{ "module", token_type::__module },
	{ "guarantees", token_type::guarantees },
	{ "dependencies", token_type::dependencies },
	{ "import", token_type::__import },
	{ "async", token_type::async },
	{ "sync", token_type::sync }
};

token lexer::get_token() {
	if (this->at_eof()) {
		return token("\0", token_type::eof);
	}
whitespace:
	this->skip_whitespace();
	this->skip_comment();
	this->skip_semicolon();

	switch (this->current_char) {
		// Math operators
		case '+':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '+':
					return token("++", token_type::double_plus);
				case '=':
					return token("+=", token_type::plus_equals);
			}

			return token("+", token_type::plus);
		}
		case '-':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '-':
					return token("--", token_type::double_minus);
				case '=':
					return token("-=", token_type::minus_equals);
			}

			return token("-", token_type::minus); \
		}
		case '*':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '*':
					return token("**", token_type::double_star);
				case '=':
					return token("*=", token_type::star_equals);
			}

			return token("*", token_type::star);
		}
		case '/':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '/':
					return token("//", token_type::double_forward_slash);
				case '=':
					return token("/=", token_type::forward_slash_equals);
			}

			return token("/", token_type::forward_slash);
		}
		case '\\':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '\\':
					return token("\\\\", token_type::double_backward_slash);
				case '=':
					return token("\\=", token_type::backward_slash_equals);
			}

			return token("\\", token_type::backward_slash);
		}
		case '%':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '%':
					return token("%%", token_type::double_percent);
				case '=':
					return token("%=", token_type::percent_equals);
			}

			return token("%", token_type::percent);
		}
		case '=':
		{
			int second_char = this->peek();

			this->next_char();

			if (second_char == '=') {
				return token("==", token_type::double_equals);
			}

			return token("=", token_type::equals);
		}
		case '!':
		{
			int second_char = this->peek();

			this->next_char();

			if (second_char == '=') {
				return token("!=", token_type::exclamation_equals);
			}

			return token("!", token_type::exclamation_mark);
		}
		case '&':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '&':
					return token("&&", token_type::double_ampersands);
				case '=':
					return token("&=", token_type::ampersands_equals);
			}

			return token("&", token_type::ampersands);
		}
		case '|':
		{
			int second_char = this->peek();

			this->next_char();

			switch (second_char) {
				case '|':
					return token("||", token_type::double_bar);
				case '=':
					return token("|=", token_type::bar_equals);
			}

			return token("|", token_type::bar);
		}
		case '^':
		{
			int second_char = this->peek();

			this->next_char();

			if (second_char == '=') {
				return token("^=", token_type::hat);
			}

			return token("^", token_type::star);
		}

		// Function type / Function call
		case '(': {
			this->next_char();
			return token("(", token_type::open_parenthesis);	  
		}
		case ')': {
			this->next_char();
			return token(")", token_type::closed_parenthesis);	  
		}
		case '{': {
			this->next_char();
			return token("{", token_type::open_curly_bracket);	  
		}
		case '}': {
			this->next_char();
			return token("}", token_type::closed_curly_bracket);  
		}
		case '[': {
			this->next_char();
			return token("[", token_type::open_square_bracket);	  
		}
		case ']': {
			this->next_char();
			return token("]", token_type::closed_square_bracket); 
		}
		
		// Strings and characters (empty character constant or too many characters error
		// to be handled in parser)
		case '\'':
		case '"':
		{
			this->next_char();

			std::string str = "";

			if (this->current_char == '"') {
				while (this->current_char != '"') {
					str += this->current_char;

					this->next_char();
				}

				return token(str, token_type::string_literal);
			} else if (this->current_char == '\'') {
				while (this->current_char != '\'') {
					str += this->current_char;

					this->next_char();
				}

				return token(str, token_type::char_literal);
			}

			break;
		}
		case 'w':
		case 'W':
		{
			if (this->source.peek() == '"') {
				this->next_char();
				this->next_char();

				std::string str = "";

				if (this->current_char == '"') {
					while (this->current_char != '"') {
						str += this->current_char;

						this->next_char();
					}

					return token(str, token_type::wide_string_literal);
				} else if (this->current_char == '\'') {
					while (this->current_char != '\'') {
						str += this->current_char;

						this->next_char();
					}

					return token(str, token_type::wide_char_literal);
				}
			}

			break;
		}

		case ' ':
		case '\n':
		case '\t':
		case '\r':
			goto whitespace;
		default:
		{
			if (std::isdigit(this->current_char)) {
				std::string number_str = "";
				token_type integral_type = token_type::int_literal;

				if (this->current_char == '0') {
					int peek = this->source.peek();

					if (std::isdigit(peek)) { // octal
						integral_type = token_type::octal_literal;
					} else if (peek == 'x') { // hex
						integral_type = token_type::hex_literal;
					} else if (peek == 'b') {
						integral_type = token_type::bin_literal;
					}
				}

				while (std::isdigit(this->current_char)) {
					number_str += this->current_char;

					this->next_char();
				}

				return token(number_str, integral_type);
			} else if (std::isalpha(this->current_char)) {
				std::string identifier = "";

				while (std::isalnum(this->current_char)) {
					identifier += this->current_char;

					this->next_char();
				}

				if (types.contains(identifier)) {
					return token(identifier, types.at(identifier));
				} else if (modifiers.contains(identifier)) {
					return token(identifier, modifiers.at(identifier));
				} else if (operators.contains(identifier)) {
					return token(identifier, operators.at(identifier));
				} else if (protections.contains(identifier)) {
					return token(identifier, protections.at(identifier));
				} else if (other_keywords.contains(identifier)) {
					return token(identifier, other_keywords.at(identifier));
				}

				return token(identifier, token_type::identifier);
			}

			this->abort();
		}
	}
}

bool lexer::at_eof() {
	return (
		this->current_char == std::fstream::traits_type::eof() ||
		this->current_position >= this->file_size ||
		this->peek() == std::fstream::traits_type::eof()
	);
}

lexer::~lexer() {
	this->source.close();
}
