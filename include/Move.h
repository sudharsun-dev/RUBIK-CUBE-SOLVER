#pragma once

#include <string>
#include <vector>

namespace rubiks {

enum class Face {
    U,
    D,
    L,
    R,
    F,
    B
};

enum class Turn {
    Clockwise,
    CounterClockwise,
    Double
};

struct Move {
    Face face;
    Turn turn;

    Move inverse() const;
    std::string toString() const;

    static Move fromString(const std::string& notation);
};

std::vector<Move> inverseSequence(const std::vector<Move>& moves);

} // namespace rubiks
