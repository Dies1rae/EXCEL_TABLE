#include "common.h"
#include "test_runner_p.h"
#include "Position.h"
#include "sheet.h"

#include <string_view>
#include <string>
#include <iostream>

inline std::ostream& operator<<(std::ostream& output, Position pos) {
    return output << "(" << pos.row << ", " << pos.col << ")";
}

inline Position operator"" _pos(const char* str, std::size_t) {
    return Position::FromString(str);
}

inline std::ostream& operator<<(std::ostream& output, Size size) {
    return output << "(" << size.rows << ", " << size.cols << ")";
}

inline std::ostream& operator<<(std::ostream& output, const CellInterface::Value& value) {
    std::visit([&](const auto& x) {output << x;}, value);
    return output;
}

void Test_1() {
    auto sheet = NewTable();
    try {
        sheet->SetCell(Position{-1, 0}, "");
    } catch (const InvalidPositionException&) {}
    try {
        sheet->GetCell(Position{0, -2});
    } catch (const InvalidPositionException&) {}
    try {
        sheet->ClearCell(Position{Position::MAX_ROWS, 0});
    } catch (const InvalidPositionException&) {}
}

void Test_2() {
    auto sheet = CreateSheet();

    auto checkCell = [&](Position pos, std::string text) {
        sheet->SetCell(pos, text);
        CellInterface* cell = sheet->GetCell(pos);
        ASSERT(cell != nullptr);
        ASSERT_EQUAL(cell->GetText(), text);
        ASSERT_EQUAL(std::get<std::string>(cell->GetValue()), text);
    };

    checkCell("A1"_pos, "Hello");
    checkCell("A1"_pos, "World");
    checkCell("B2"_pos, "Purr");
    checkCell("A3"_pos, "Meow");

    const SheetInterface& constSheet = *sheet;
    ASSERT_EQUAL(constSheet.GetCell("B2"_pos)->GetText(), "Purr");

    sheet->SetCell("A3"_pos, "'=escaped");
    CellInterface* cell = sheet->GetCell("A3"_pos);
    ASSERT_EQUAL(cell->GetText(), "'=escaped");
    ASSERT_EQUAL(std::get<std::string>(cell->GetValue()), "=escaped");
}

void Test_3() {
    {
        auto sheet = CreateSheet();
        sheet->SetCell("A1"_pos, "1");
        try {
            sheet->SetCell("A2"_pos, "=A1+*");
            ASSERT(false);
        } catch (FormulaException& e) {}
    }
    {
        auto sheet = CreateSheet();
        try {
            sheet->SetCell("A1"_pos, "=ZZZ1+*");
            ASSERT(false);
        } catch (FormulaException& e) {}
    }
    {
        auto sheet = CreateSheet();
        try {
            sheet->SetCell("A1"_pos, "=A1");
            ASSERT(false);
        } catch (CircularDependencyException& e) {}
    }
    {
        auto sheet = CreateSheet();
        try {
            sheet->SetCell("A1"_pos, "=A1+100500");
            ASSERT(false);
        } catch (CircularDependencyException& e) {}
    }
    {
        auto sheet = CreateSheet();
        try {
            sheet->SetCell("A1"_pos, "=A2+1");
            sheet->SetCell("A2"_pos, "=A1+1");
            ASSERT(false);
        } catch (CircularDependencyException& e) {}
    }
    {
        auto sheet = CreateSheet();
        try {
            sheet->SetCell("A1"_pos, "=B1+B2");
            sheet->SetCell("B1"_pos, "=C1+C2+C3");
            sheet->SetCell("B2"_pos, "=C3+C4+C5");
            sheet->SetCell("C3"_pos, "=A1");
            ASSERT(false);
        } catch (CircularDependencyException& e) {}
    }
}

void Test_4() {
    auto sheet = CreateSheet();
    sheet->SetCell("A2"_pos, "meow");
    sheet->SetCell("B2"_pos, "=1+2");
    sheet->SetCell("A1"_pos, "=1/0");

    ASSERT_EQUAL(sheet->GetPrintableSize(), (Size{2, 2}));

    std::ostringstream texts;
    sheet->PrintTexts(texts);
    ASSERT_EQUAL(texts.str(), "=1/0\t\nmeow\t=1+2\n");

    std::ostringstream values;
    sheet->PrintValues(values);
    ASSERT_EQUAL(values.str(), "#DIV/0!\t\nmeow\t3\n");

    sheet->ClearCell("B2"_pos);
    ASSERT_EQUAL(sheet->GetPrintableSize(), (Size{2, 1}));
}

void AllTests() {
    Test_1();
    std::cout << "Test posiotion is OK" << std::endl;
    Test_2();
    std::cout << "Test text is OK" << std::endl;
    Test_3();
    std::cout << "Test errors is OK" << std::endl;
    Test_4();
    std::cout << "Test print is OK" << std::endl;
}

int main() {
    AllTests();

    return 0;
}