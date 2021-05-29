#include "formula.h"
#include "FormulaAST.h"

#include <algorithm>
#include <cassert>
#include <cctype>
#include <sstream>

using namespace std::literals;

std::ostream& operator<<(std::ostream& output, FormulaError fe) {
    return output << "#DIV/0!";
}

namespace {
class Formula : public FormulaInterface {
public:
    explicit Formula(std::string expression) : ast_(ParseFormulaAST(expression)) {}

    Value Evaluate(const SheetInterface& sheet) const override;

    std::string GetExpression() const override;

    std::vector<Position> GetReferencedCells() const override;

private:
    FormulaAST ast_;
};
}  // namespace

FormulaInterface::Value Formula::Evaluate(const SheetInterface& sheet) const {
    auto lambda_func = [&sheet](Position pos) {
        CellInterface::Value value = sheet.GetCell(pos)->GetValue();
        if(std::holds_alternative<double>(value)) {
            return std::get<1>(value);
        } else if (std::holds_alternative<std::string>(value)) {
            std::string val_str = sheet.GetCell(pos)->GetText();
            if(val_str[0] == '\'') {
                throw FormulaError(FormulaError::Category::Value);
            }
            try{
                return std::stod(val_str);
            } catch (...) {
                throw FormulaError(FormulaError::Category::Value);
            }
        }  else if(std::holds_alternative<FormulaError>(value)) {
            throw std::get<2>(value);
        } else {
            throw std::runtime_error("Something went wrong");
        }
    };
    Value tmp_;
    try{
        tmp_ = this->ast_.Execute(lambda_func);
    } catch (FormulaError& e) {
        tmp_ = e;
    }
    return tmp_;
}

std::string Formula::GetExpression() const {
    std::stringstream str;
    this->ast_.PrintFormula(str);
    return str.str();
}

std::vector<Position> Formula::GetReferencedCells() const {
    return { this->ast_.GetCells().begin(), this->ast_.GetCells().end() };
}

std::unique_ptr<FormulaInterface> ParseFormula(std::string expression) {
    return std::make_unique<Formula>(std::move(expression));
}
