#pragma once

#include "cell.h"
#include "common.h"

#include <functional>

class Sheet : public SheetInterface {
public:
    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;
protected:
    void NormalizeTbl();
    void ChSizeTable(Size size);
private:
    std::vector<std::vector<std::unique_ptr<Cell>>> cell_field_;
	Size print_size_;
};

std::unique_ptr<SheetInterface> NewTable();