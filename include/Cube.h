#pragma once

#include "Move.h"

#include <array>
#include <cstddef>
#include <ostream>
#include <string>
#include <vector>

namespace rubiks {

class Cube {
public:
    Cube();

    void reset();
    bool isSolved() const;

    void applyMove(const Move& move);
    void applyMoves(const std::vector<Move>& moves);

    bool undo();
    void clearHistory();

    std::vector<Move> getHistory() const;

    bool operator==(const Cube& other) const;
    bool operator!=(const Cube& other) const;

    std::string toString() const;
    void print(std::ostream& os) const;

private:
    static constexpr std::size_t FaceCount = 6;
    static constexpr std::size_t FaceSize = 3;

    using FaceGrid = std::array<std::array<char, FaceSize>, FaceSize>;
    std::array<FaceGrid, FaceCount> cube_{};
    std::vector<Move> history_;

    enum FaceIndex : std::size_t {
        U = 0,
        D = 1,
        F = 2,
        B = 3,
        L = 4,
        R = 5
    };

    static std::size_t toIndex(Face face);

    void applyClockwise(Face face);
    void rotateFaceClockwise(std::size_t index);
};

std::vector<Move> generateScramble(std::size_t length);

} // namespace rubiks
