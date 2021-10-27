#include "parser.hpp"
#include "log.hpp"

#include <type_traits>

parsing_exception::parsing_exception() : std::runtime_error(
	"An error occured whilst parsing the source file"
) {
}

parser::parser(lexer &&other_l) : 
	l(std::move(other_l)),
	current_token(l.get_token()),
	peek_token(l.get_token())
{}

bool parser::check_token(token_type type) {
	return this->current_token == type;
}

bool parser::check_peek(token_type type) {
	return this->peek_token == type;
}

bool parser::match(token_type type) {
	if (!this->check_token(type)) {
		this->abort();
	}

	this->next_token();

	return false;
}

void parser::next_token() {
	this->current_token = std::move(this->peek_token);
	this->peek_token = this->l.get_token();
}

void parser::abort() {
	throw parsing_exception();
}

void parser::program() {
	debug("program");

	while (!this->check_token(token_type::eof)) {
		this->expression();
	}
}

void parser::expression() {
	token_type t_type = this->current_token;

	switch (t_type) {
		case token_type::unknown:
			break;
		case token_type::eof:
			break;
		// case token_type::program: break;
		// case token_type::__operator: break;
		case token_type::plus:
			break;
		case token_type::minus:
			break;
		case token_type::star:
			break;
		case token_type::forward_slash:
			break;
		case token_type::backward_slash:
			break;
		case token_type::percent:
			break;
		case token_type::equals:
			break;
		case token_type::exclamation_mark:
			break;
		case token_type::ampersands:
			break;
		case token_type::bar:
			break;
		case token_type::tilde:
			break;
		case token_type::hat:
			break;
		case token_type::double_ampersands:
			break;
		case token_type::double_bar:
			break;
		case token_type::double_equals:
			break;
		case token_type::exclamation_equals:
			break;
		case token_type::plus_equals:
			break;
		case token_type::minus_equals:
			break;
		case token_type::star_equals:
			break;
		case token_type::forward_slash_equals:
			break;
		case token_type::backward_slash_equals:
			break;
		case token_type::percent_equals:
			break;
		case token_type::ampersands_equals:
			break;
		case token_type::bar_equals:
			break;
		case token_type::hat_equals:
			break;
		case token_type::double_plus:
			break;
		case token_type::double_minus:
			break;
		case token_type::double_star:
			break;
		case token_type::double_forward_slash:
			break;
		case token_type::double_backward_slash:
			break;
		case token_type::double_percent:
			break;
		case token_type::less:
			break;
		case token_type::less_equal:
			break;
		case token_type::greater:
			break;
		case token_type::greater_equal:
			break;
		case token_type::bit_left:
			break;
		case token_type::bit_left_equals:
			break;
		case token_type::bit_right:
			break;
		case token_type::bit_right_equals:
			break;
		case token_type::await:
			break;
		case token_type::thread_launch:
			break;
		case token_type::sleep:
			break;
		case token_type::join:
			break;
		case token_type::detach:
			break;
		case token_type::wait_for:
			break;
		case token_type::yield:
			break;
		case token_type::____asm:
			break;
		case token_type::dot:
			break;
		case token_type::scope:
			break;
		// case token_type::expression: break;
		// case token_type::literal: break;
		case token_type::bool_literal:
			break;
		case token_type::char_literal:
			break;
		case token_type::wide_char_literal:
			break;
		case token_type::byte_literal:
			break;
		case token_type::int_literal:
			break;
		case token_type::octal_literal:
			break;
		case token_type::hex_literal:
			break;
		case token_type::bin_literal:
			break;
		case token_type::string_literal:
			break;
		case token_type::wide_string_literal:
			break;
		case token_type::__new:
			break;
		case token_type::lambda:
			break;
		case token_type::identifier:
			break;
		case token_type::declaration:
			break;
		case token_type::definition:
			break;
		case token_type::keyword:
			break;
		// case token_type::modifier: break;
		case token_type::const_modifier:
			break;
		case token_type::static_modifier:
			break;
		case token_type::volatile_modifier:
			break;
		case token_type::unsigned_modifier:
			break;
		case token_type::mutable_modifier:
			break;
		case token_type::abstract_modifier:
			break;
		case token_type::final_modifier:
			break;
		case token_type::virtual_modifier:
			break;
		case token_type::restrict_modifier:
			break;
		case token_type::generic_modifier:
			break;
		case token_type::__module:
			break;
		case token_type::guarantees:
			break;
		case token_type::dependencies:
			break;
		case token_type::__import:
			break;
		case token_type::async:
			break;
		case token_type::sync:
			break;
		case token_type::type:
			break;
		// case token_type::primitive: break;
		case token_type::byte_type:
			break;
		case token_type::bool_type:
			break;
		case token_type::char_type:
			break;
		case token_type::wchar_type:
			break;
		case token_type::short_type:
			break;
		case token_type::int_type:
			break;
		case token_type::long_type:
			break;
		// case token_type::long_long_type: break;
		case token_type::float_type:
			break;
		case token_type::double_type:
			break;
		case token_type::string_type:
			break;
		case token_type::wstring_type:
			break;
		case token_type::thread_type:
			break;
		case token_type::function:
			break;
		case token_type::array:
			break;
		case token_type::string:
			break;
		case token_type::__struct:
			break;
		case token_type::__class:
			break;
		// case token_type::symbol: break;
		case token_type::open_parenthesis:
			break;
		case token_type::closed_parenthesis:
			break;
		case token_type::open_square_bracket:
			break;
		case token_type::closed_square_bracket:
			break;
		case token_type::open_curly_bracket:
			break;
		case token_type::closed_curly_bracket:
			break;
		// case token_type::protection: break;
		case token_type::protection_public:
			break;
		case token_type::protection_private:
			break;
		case token_type::protection_protected:
			break;
		// case token_type::control: break;
		case token_type::control_if:
			break;
		case token_type::control_while:
			break;
		case token_type::control_for_init_condition_increment:
			break;
		case token_type::control_for_item_in_element:
			break;
		case token_type::control_switch:
			break;
		case token_type::control_when:
			break;
		default:
			this->abort();
			break; // avoid warnings
	}
}
