#pragma once

#include <string>
#include <string_view>

struct Position {
    int row = 0;
    int col = 0;

    bool operator==(Position rhs) const;
    bool operator<(Position rhs) const;

    bool IsValid() const;
    bool IsValidString(std::string_view str) const;
    std::string ToString() const;

    static Position FromString(std::string_view str);

    static const int MAX_ROWS = 16384;
    static const int MAX_COLS = 16384;
    static const Position NONE;
    static const Position NONE_MAX;
};

struct PositionHasher {
    size_t operator()(Position pos) const {
        return ((pos.row * 195875) + (pos.col * 224934));
    }
};


struct Size {
    int rows = 0;
    int cols = 0;

    bool operator==(Size rhs) const;
};