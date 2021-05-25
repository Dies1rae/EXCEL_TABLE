#pragma once

#include "Position.h"
#include "Interfaces.h"

#include <iosfwd>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <variant>
#include <vector>
#include <unordered_set>


class FormulaError {
public:
    enum class Category {
        Ref, 
        Value, 
        Div0,
    };

    FormulaError(Category category);

    Category GetCategory() const;

    bool operator==(FormulaError rhs) const;

    std::string_view ToString() const;
private:
    Category category_;
};
std::ostream& operator<<(std::ostream& output, FormulaError fe);

class InvalidPositionException : public std::out_of_range {
public:
    using std::out_of_range::out_of_range;
};

class FormulaException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

class CircularDependencyException : public std::runtime_error {
public:
    using std::runtime_error::runtime_error;
};

inline constexpr char FORMULA_SIGN = '=';
inline constexpr char ESCAPE_SIGN = '\'';

