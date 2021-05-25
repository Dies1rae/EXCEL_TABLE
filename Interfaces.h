#pragma once

#include <iosfwd>
#include <memory>
#include <string>
#include <string_view>
#include <variant>
#include <vector>

class FormulaError;

class CellInterface {
public:
    using Value = std::variant<std::string, double, FormulaError>;

    virtual ~CellInterface() = default;

    virtual Value GetValue() const = 0;

    virtual std::string GetText() const = 0;

    virtual std::vector<Position> GetReferencedCells() const = 0;
};

class SheetInterface {
public:
    virtual ~SheetInterface() = default;

    virtual void SetCell(Position pos, std::string text) = 0;

    virtual const CellInterface* GetCell(Position pos) const = 0;
    virtual CellInterface* GetCell(Position pos) = 0;

    virtual void ClearCell(Position pos) = 0;

    virtual Size GetPrintableSize() const = 0;

    virtual void PrintValues(std::ostream& output) const = 0;
    virtual void PrintTexts(std::ostream& output) const = 0;
};

std::unique_ptr<SheetInterface> CreateSheet();
