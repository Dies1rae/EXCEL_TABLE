#include "common.h"

#include <cctype>
#include <sstream>
#include <utility>
#include <string>
#include <algorithm>
#include <math.h>

const int LETTERS = 26;
const int MAX_POSITION_LENGTH = 17;
const int MAX_POS_LETTER_COUNT = 3;
const Position Position::NONE = { -1, -1 };
const Position Position::NONE_MAX = { 16384, 16384 };

bool Position::operator==(const Position rhs) const {
	return this->col == rhs.col && this->row == rhs.row;
}

bool Position::operator<(const Position rhs) const {
	return this->col < rhs.col&& this->row < rhs.row;
}

bool Position::IsValid() const {
	if (this->col < 0 || this->row < 0 || this->col >= this->MAX_COLS || this->row >= this->MAX_ROWS) {
		return 0;
	}
	return 1;
}

bool Position::IsValidString(std::string_view str) const {
	if (str.empty() || std::isdigit(str[0])) {
		return 0;
	}
	int dig_ctr = 0;
	for (size_t ptr = 0; ptr < str.size(); ptr++) {
		if (std::isdigit(str[ptr])) {
			dig_ctr++;
		}
		if (!std::isdigit(str[ptr]) && (str[ptr] < 'A' || str[ptr] > 'Z')) {
			return 0;
		}
	}
	return dig_ctr ? 1 : 0;
}

std::string Position::ToString() const {
	if (!this->IsValid()) {
		return {};
	}
	std::string pos;
	int row_ = this->row;
	int col_ = this->col;
	while (col_ >= 26) {
		char tmp = (col_ % 26) + 65;
		pos += tmp;
		col_ /= 26;
		col_--;
	}
	pos += col_ + 65;
	std::reverse(pos.begin(), pos.end());
	pos += std::to_string(++row_);
	return pos;
}

Position Position::FromString(std::string_view str) {
	if (str.empty() || std::isdigit(str[0])) {
		return  Position::NONE;
	}
	int dig_ctr = 0;
	for (size_t ptr = 0; ptr < str.size(); ptr++) {
		if (std::isdigit(str[ptr]) && (str[ptr] - 48 > 0)) {
			dig_ctr++;
			if (ptr < str.size() - 1 && !std::isdigit(str[ptr + 1])) {
				return  Position::NONE;
			}
		}
		if (!std::isdigit(str[ptr]) && (str[ptr] < 'A' || str[ptr] > 'Z')) {
			return  Position::NONE;
		}
	}
	if (dig_ctr == 0) {
		return Position::NONE;
	}
	Position pos;
	std::string col;
	std::string row;
	for (size_t ptr = 0; ptr < str.size(); ptr++) {
		if (std::isdigit(str[ptr])) {
			row += str[ptr];
		}
		if (!std::isdigit(str[ptr])) {
			col += str[ptr];
		}
	}
	for (size_t ptr = 0; ptr < col.size(); ptr++) {
		pos.col += (col[ptr] - 64) * (std::pow(26, col.size() - (ptr + 1)));
	}
	pos.row = std::stod(row) - 1;
	pos.col -= 1;
	return pos.IsValid() ? pos : Position::NONE;
}

bool Size::operator==(Size rhs) const {
	return this->cols == rhs.cols && this->rows == rhs.rows;
}

FormulaError::FormulaError(FormulaError::Category category) : category_(category) {}

FormulaError::Category FormulaError::GetCategory() const {
	return category_;
}

bool FormulaError::operator==(FormulaError rhs) const {
	return category_ == rhs.category_;
}

std::string_view FormulaError::ToString() const {
	switch (category_) {
	case FormulaError::Category::Ref: return "#REF!"; break;
	case FormulaError::Category::Value: return "#VALUE!"; break;
	case FormulaError::Category::Div0: return "#DIV0!"; break;
	default: throw std::runtime_error("Something wrong");
	}
}