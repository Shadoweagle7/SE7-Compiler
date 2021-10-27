#include "token.hpp"

#include <type_traits>

token::token(std::string_view text, token_type type) :
text(text), type(type)
{}

token::token(const token &other) :
text(other.text),
type(other.type)
{}

token::token(token &&other) noexcept :
text(std::move(other.text)),
type(other.type)
{}

token::operator std::string_view() const {
	return this->text;
}

token::operator token_type() const {
	return this->type;
}

token &token::operator=(const token &other) {
	this->text = other.text;
	this->type = other.type;

	return *this;
}
