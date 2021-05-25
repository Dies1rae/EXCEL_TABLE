#pragma once

#include "common.h"
#include "formula.h"

#include <functional>
#include <unordered_set>
#include <optional>

class Sheet;

class Cell : public CellInterface {
public:
    Cell(Sheet& sheet, Position cellpos);
    ~Cell();

    void Set(std::string text);

    void Clear();

    Value GetValue() const override;

    std::string GetText() const override;

    std::vector<Position> GetReferencedCells() const override;

    bool IsReferenced() const;

    void RemoveDepCell(const Position& pos) const;

    void AddDepCell(const Position& pos) const;

    void ClearCash() const;
private:
    class Impl {
        public:
            using Value = std::variant<std::string, double, FormulaError>;

            virtual ~Impl() = default;

            virtual void Set(std::string text) = 0;

            virtual void Clear() = 0;

            virtual std::string GetText() const = 0;

            virtual Value GetValue() const = 0;
    };

    class EmptyImpl : public Impl {
        public:
            void Set(std::string text) override {}

            void Clear() override {}

            std::string GetText() const override {
                return "";
            }

            Value GetValue() const override {
                return "";
            }
    };

    class TextImpl : public Impl {
        public:
            TextImpl(std::string& text) : text_(std::move(text)) {}

            void Set(std::string text) override {
                this->Clear();
                this->text_ = std::move(text);
            }

            void Clear() override {
                this->text_.clear();
            }

            std::string GetText() const override {
                return this->text_;
            }

            Value GetValue() const override {
                Impl::Value tmp_ = this->text_;
                if(this->text_[0] == '\''){
                    tmp_ = this->text_.substr(1);
                }
                return tmp_;
            }
        private:
            std::string text_;
    };

    class FormulaImpl : public Impl {
        public:
            FormulaImpl(SheetInterface& sheet, std::string text) : sheet_(dynamic_cast<SheetInterface&>(sheet)), formula_(ParseFormula(text)){}

            void Set(std::string text) override {
                this->formula_ = ParseFormula(text);
            }

            void Clear() override {
                delete this->formula_.release();
            }

            std::string GetText() const override {
                return '=' + this->formula_->GetExpression();
            }

            Value GetValue() const override {
                auto res = this->formula_->Evaluate(this->sheet_);
                if(std::holds_alternative<double>(res)){
                    return std::get<double>(res);
                } else {
                    return std::get<FormulaError>(res);
                }
                return {};
            }

            std::vector<Position> GetReferencedCells() const {
                return formula_->GetReferencedCells();
            }
        private:
            SheetInterface& sheet_;
            std::unique_ptr<FormulaInterface> formula_;
    };

    void UnregisterDependence() const;
    void RegisterDependence() const;
    bool IsDepend(const std::vector<Position>& cellpos);

    Sheet& sheet_;
    Position pos_;
    std::unique_ptr<Impl> impl_;
    mutable std::optional<Value> cach_;
    mutable std::unordered_set<Position, PositionHasher> inheritanceU_;
    std::vector<Position> dependenceD_;
};