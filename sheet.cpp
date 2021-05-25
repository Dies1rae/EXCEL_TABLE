#include "sheet.h"
#include "cell.h"
#include "common.h"

#include <algorithm>
#include <functional>
#include <iostream>
#include <optional>

using namespace std::literals;

Sheet::~Sheet() {}

void Sheet::SetCell(Position pos, std::string text) {
    if (!pos.IsValid()) {
        throw InvalidPositionException("Invelid cell position\n");
    }
    int tmpr = pos.row;
    int tmpc = pos.col;
    if (pos.row >= this->print_size_.rows || pos.col >= this->print_size_.cols) {
        if (pos.col >= this->print_size_.cols) {
            tmpc = pos.col + 1;
        } else {
            tmpc = this->print_size_.cols;
        }
        
        if (pos.row >= this->print_size_.rows) {
            tmpr = pos.row + 1;
        } else {
            tmpr = this->print_size_.rows;
        }
        
        this->ChSizeTable( {tmpr, tmpc} );
    }

    this->cell_field_[pos.row][pos.col] = std::make_unique<Cell>(*this, pos);
    this->cell_field_[pos.row][pos.col]->Set(text);
}

const CellInterface* Sheet::GetCell(Position pos) const {
    if (pos.IsValid()) {
        if (pos.row < this->print_size_.rows && pos.col < this->print_size_.cols) {
            return this->cell_field_[pos.row][pos.col].get();
        }
    } else {
        throw InvalidPositionException("Invelid cell position\n");
    }
    return nullptr;
}
CellInterface* Sheet::GetCell(Position pos) {
    if (pos.IsValid()) {
        if (pos.row < this->print_size_.rows && pos.col < this->print_size_.cols) {
            return this->cell_field_[pos.row][pos.col].get();
        }
    } else {
        throw InvalidPositionException("Invelid cell position\n");
    }
    return nullptr;
}

void Sheet::ClearCell(Position pos) {
    if (pos.IsValid()) {
        if (const auto * cell_ptr = this->GetCell(pos); cell_ptr) {
            this->cell_field_[pos.row][pos.col]->Clear();
            delete this->cell_field_[pos.row][pos.col].release();
            this->NormalizeTbl();
        }
    } else {
        throw InvalidPositionException("Error in cell position\n");
    }
}

Size Sheet::GetPrintableSize() const {
    return this->print_size_;
}

void Sheet::PrintValues(std::ostream& output) const {
    for (size_t p_r = 0; p_r < this->cell_field_.size(); p_r++) {
        for (size_t p_c = 0; p_c < this->cell_field_[p_r].size(); p_c++) {
            if (p_c > 0) {
                output << '\t';
            }
            if (this->cell_field_[p_r][p_c]) {
                auto cell_val = this->cell_field_[p_r][p_c]->GetValue();
                if (std::holds_alternative<double>(cell_val)) {
                    output << std::get<1>(cell_val);
                } else if (std::holds_alternative<std::string>(cell_val)) {
                    output << std::get<0>(cell_val);
                } else if (std::holds_alternative<FormulaError>(cell_val)) {
                    output << std::get<2>(cell_val);
                } else {
                    throw std::runtime_error("Vse slomalos((\n");
                }
            }
        }
        output << '\n';
    }
}
void Sheet::PrintTexts(std::ostream& output) const {
    for (size_t p_r = 0; p_r < this->cell_field_.size(); p_r++) {
        for (size_t p_c = 0; p_c < this->cell_field_[p_r].size(); p_c++) {
            if (p_c > 0){
                output << '\t';
            }
            if (this->cell_field_[p_r][p_c]){
                output << this->cell_field_[p_r][p_c]->GetText();
            }
        }
        output << '\n';
    }
}

std::unique_ptr<SheetInterface> CreateSheet() {
    return std::make_unique<Sheet>();
}

void Sheet::NormalizeTbl() {
    int rows = 0;
    int cols = 0;
    for (int p_row = 0; p_row < this->print_size_.rows; p_row++) {
        for (int p_col = 0; p_col < this->print_size_.cols; p_col++) {
            if (this->cell_field_[p_row][p_col]) {
                if (p_row >= rows) {
                    rows = p_row + 1;
                }
                if (p_col >= cols) {
                    cols = p_col + 1;
                }
            }
        }
    }
    this->ChSizeTable( { rows, cols } );
}
void Sheet::ChSizeTable(Size size) {
    this->cell_field_.resize(size.rows);
    for (auto& col : this->cell_field_) {
        col.resize(size.cols);
    }
    this->print_size_ = size;
}

std::unique_ptr<SheetInterface> NewTable() {
    return std::make_unique<Sheet>();
}