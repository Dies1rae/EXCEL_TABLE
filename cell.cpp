#include "cell.h"
#include "sheet.h"

#include <cassert>
#include <iostream>
#include <string>
#include <optional>
#include <stack>


Cell::Cell(Sheet& sheet, Position cellpos) : sheet_(sheet), pos_(cellpos), impl_(std::make_unique<EmptyImpl>()){}

Cell::~Cell() {}

void Cell::Set(std::string text) {
    if(text != this->impl_->GetText()){
        if(text.size() > 1 && text[0] == '=') {
            std::unique_ptr<FormulaImpl> tmp_new_formula;
            try {
                tmp_new_formula = std::make_unique<FormulaImpl>(this->sheet_, text.substr(1)); //!!!!
            } catch (...) {
                throw FormulaException("Sytnax Error");
            }
            std::vector<Position> tmp_depend = tmp_new_formula->GetReferencedCells();
            if(!this->IsDepend(tmp_depend)) {
                throw CircularDependencyException("Circular dependency");
            }

            this->UnregisterDependence();
            this->ClearCash();

            delete this->impl_.release();

            this->impl_ = std::move(tmp_new_formula);
            this->dependenceD_ = std::move(tmp_depend);

            this->RegisterDependence();
        } else {
            this->ClearCash();
            this->UnregisterDependence();
            this->dependenceD_.clear();
            delete this->impl_.release();

            this->impl_ = std::make_unique<TextImpl>(text);
        }
    }
}

void Cell::Clear() {
    delete this->impl_.release();
    this->impl_ = std::make_unique<EmptyImpl>();
}

Cell::Value Cell::GetValue() const {
    if(!this->cach_) {
        this->cach_ = this->impl_->GetValue();
    }
    return *(this->cach_);
}

std::string Cell::GetText() const {
    return this->impl_->GetText();
}

std::vector<Position> Cell::GetReferencedCells() const {
    return this->dependenceD_;
}

bool Cell::IsReferenced() const {
    return this->inheritanceU_.size() != 0;
}

void Cell::AddDepCell(const Position& pos) const {
    if(!pos.IsValid()){
        throw InvalidPositionException("Cell position error");
    }
    this->inheritanceU_.insert(pos);
}

void Cell::RemoveDepCell(const Position& pos) const {
    if(!pos.IsValid()){
        throw InvalidPositionException("Cell position error");
    }
    auto pos_iter = this->inheritanceU_.find(pos);
    if(pos_iter != this->inheritanceU_.end()) {
        this->inheritanceU_.erase(pos_iter);
    }
}

void Cell::ClearCash() const {
    this->cach_.reset();
    std::stack<Position> clear_cache;
    std::unordered_set<Position, PositionHasher> tmp_visited;
    for(auto position : this->inheritanceU_) {
        clear_cache.push(position);
    }
    while(!clear_cache.empty()){
        Position current = clear_cache.top();
        clear_cache.pop();
        tmp_visited.insert(current);
        Cell * cell_pos = dynamic_cast<Cell*>(this->sheet_.GetCell(current));
        if(cell_pos) {
            cell_pos->ClearCash();
        }
    }

}

void Cell::RegisterDependence() const {
    for(const auto position : this->dependenceD_) {
        Cell * cell_pos = dynamic_cast<Cell*>(this->sheet_.GetCell(position));
        if(cell_pos) {
            cell_pos->AddDepCell(this->pos_);
        } else {
            this->sheet_.SetCell(position, "");
            dynamic_cast<Cell*>(this->sheet_.GetCell(position))->AddDepCell(position);
        }
    }
}

void Cell::UnregisterDependence() const {
     for(const auto position : this->dependenceD_) {
        Cell * cell_pos = dynamic_cast<Cell*>(this->sheet_.GetCell(position));
        if(cell_pos) {
            cell_pos->RemoveDepCell(this->pos_);
        }
     }
}

bool Cell::IsDepend(const std::vector<Position>& cellpos) {
    std::stack<Position> graph_cache;
    std::unordered_set<Position, PositionHasher> tmp_visited;
    for(auto position : cellpos){
        graph_cache.push(position);
    }
    while(!graph_cache.empty()) {
        Position current = graph_cache.top();
        if(current == this->pos_) {
            return false;
        }
        graph_cache.pop();
        tmp_visited.insert(current);
        Cell * cell_pos = dynamic_cast<Cell*>(this->sheet_.GetCell(current));
        if(cell_pos){
            for(const auto& pos : cell_pos->GetReferencedCells()) {
                if(tmp_visited.count(pos) == 0) {
                    graph_cache.push(pos);
                }
            }
        }
    }
    return true;
}