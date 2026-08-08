#include "Cube.h"

#include <algorithm>
#include <array>
#include <ostream>
#include <random>
#include <sstream>
#include <stdexcept>

namespace rubiks {

namespace {

constexpr std::array<char, 6> kSolvedColors = {'W', 'Y', 'G', 'B', 'O', 'R'};

} // namespace

Cube::Cube() {
    reset();
}

void Cube::reset() {
    for (std::size_t face = 0; face < FaceCount; ++face) {
        for (std::size_t row = 0; row < FaceSize; ++row) {
            for (std::size_t col = 0; col < FaceSize; ++col) {
                cube_[face][row][col] = kSolvedColors[face];
            }
        }
    }
    history_.clear();
}

bool Cube::isSolved() const {
    for (std::size_t face = 0; face < FaceCount; ++face) {
        const char expected = cube_[face][1][1];
        for (std::size_t row = 0; row < FaceSize; ++row) {
            for (std::size_t col = 0; col < FaceSize; ++col) {
                if (cube_[face][row][col] != expected) {
                    return false;
                }
            }
        }
    }
    return true;
}

void Cube::applyMove(const Move& move) {
    switch (move.turn) {
    case Turn::Clockwise:
        applyClockwise(move.face);
        break;
    case Turn::CounterClockwise:
        applyClockwise(move.face);
        applyClockwise(move.face);
        applyClockwise(move.face);
        break;
    case Turn::Double:
        applyClockwise(move.face);
        applyClockwise(move.face);
        break;
    }

    history_.push_back(move);
}

void Cube::applyMoves(const std::vector<Move>& moves) {
    for (const Move& move : moves) {
        applyMove(move);
    }
}

bool Cube::undo() {
    if (history_.empty()) {
        return false;
    }

    const Move lastMove = history_.back();
    history_.pop_back();

    const Move inverse = lastMove.inverse();
    switch (inverse.turn) {
    case Turn::Clockwise:
        applyClockwise(inverse.face);
        break;
    case Turn::CounterClockwise:
        applyClockwise(inverse.face);
        applyClockwise(inverse.face);
        applyClockwise(inverse.face);
        break;
    case Turn::Double:
        applyClockwise(inverse.face);
        applyClockwise(inverse.face);
        break;
    }

    return true;
}

void Cube::clearHistory() {
    history_.clear();
}

std::vector<Move> Cube::getHistory() const {
    return history_;
}

bool Cube::operator==(const Cube& other) const {
    return cube_ == other.cube_;
}

bool Cube::operator!=(const Cube& other) const {
    return !(*this == other);
}

std::string Cube::toString() const {
    std::ostringstream os;
    print(os);
    return os.str();
}

void Cube::print(std::ostream& os) const {
    static constexpr std::array<const char*, FaceCount> faceNames = {"U", "D", "F", "B", "L", "R"};

    for (std::size_t face = 0; face < FaceCount; ++face) {
        os << faceNames[face] << ":\n";
        for (std::size_t row = 0; row < FaceSize; ++row) {
            for (std::size_t col = 0; col < FaceSize; ++col) {
                os << cube_[face][row][col];
                if (col + 1 < FaceSize) {
                    os << ' ';
                }
            }
            os << '\n';
        }
    }
}

std::size_t Cube::toIndex(Face face) {
    switch (face) {
    case Face::U:
        return U;
    case Face::D:
        return D;
    case Face::F:
        return F;
    case Face::B:
        return B;
    case Face::L:
        return L;
    case Face::R:
        return R;
    }

    throw std::logic_error("Unhandled face index conversion");
}

void Cube::rotateFaceClockwise(std::size_t index) {
    FaceGrid rotated = cube_[index];

    for (std::size_t row = 0; row < FaceSize; ++row) {
        for (std::size_t col = 0; col < FaceSize; ++col) {
            rotated[col][FaceSize - 1 - row] = cube_[index][row][col];
        }
    }

    cube_[index] = rotated;
}

void Cube::applyClockwise(Face face) {
    auto row = [this](std::size_t faceIndex, std::size_t r) {
        return cube_[faceIndex][r];
    };

    auto col = [this](std::size_t faceIndex, std::size_t c) {
        std::array<char, 3> values{};
        for (std::size_t i = 0; i < 3; ++i) {
            values[i] = cube_[faceIndex][i][c];
        }
        return values;
    };

    auto setRow = [this](std::size_t faceIndex, std::size_t r, const std::array<char, 3>& values) {
        cube_[faceIndex][r] = values;
    };

    auto setCol = [this](std::size_t faceIndex, std::size_t c, const std::array<char, 3>& values) {
        for (std::size_t i = 0; i < 3; ++i) {
            cube_[faceIndex][i][c] = values[i];
        }
    };

    auto reversed = [](std::array<char, 3> values) {
        std::reverse(values.begin(), values.end());
        return values;
    };

    switch (face) {
    case Face::U: {
        rotateFaceClockwise(U);
        const auto temp = row(F, 0);
        setRow(F, 0, row(L, 0));
        setRow(L, 0, row(B, 0));
        setRow(B, 0, row(R, 0));
        setRow(R, 0, temp);
        break;
    }
    case Face::D: {
        rotateFaceClockwise(D);
        const auto temp = row(F, 2);
        setRow(F, 2, row(R, 2));
        setRow(R, 2, row(B, 2));
        setRow(B, 2, row(L, 2));
        setRow(L, 2, temp);
        break;
    }
    case Face::R: {
        rotateFaceClockwise(R);
        const auto temp = col(U, 2);
        setCol(U, 2, col(F, 2));
        setCol(F, 2, col(D, 2));
        setCol(D, 2, reversed(col(B, 0)));
        setCol(B, 0, reversed(temp));
        break;
    }
    case Face::L: {
        rotateFaceClockwise(L);
        const auto temp = col(U, 0);
        setCol(U, 0, reversed(col(B, 2)));
        setCol(B, 2, reversed(col(D, 0)));
        setCol(D, 0, col(F, 0));
        setCol(F, 0, temp);
        break;
    }
    case Face::F: {
        rotateFaceClockwise(F);
        const auto temp = row(U, 2);
        setRow(U, 2, reversed(col(L, 2)));
        setCol(L, 2, row(D, 0));
        setRow(D, 0, reversed(col(R, 0)));
        setCol(R, 0, temp);
        break;
    }
    case Face::B: {
        rotateFaceClockwise(B);
        const auto temp = row(U, 0);
        setRow(U, 0, col(R, 2));
        setCol(R, 2, reversed(row(D, 2)));
        setRow(D, 2, col(L, 0));
        setCol(L, 0, reversed(temp));
        break;
    }
    }
}

std::vector<Move> generateScramble(std::size_t length) {
    if (length == 0) {
        return {};
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> faceDist(0, 5);
    std::uniform_int_distribution<int> turnDist(0, 2);

    std::vector<Move> scramble;
    scramble.reserve(length);

    Face previousFace = Face::U;
    bool hasPreviousFace = false;

    while (scramble.size() < length) {
        Face face = static_cast<Face>(faceDist(gen));
        if (hasPreviousFace && face == previousFace) {
            continue;
        }

        Turn turn = static_cast<Turn>(turnDist(gen));
        scramble.push_back(Move{face, turn});

        previousFace = face;
        hasPreviousFace = true;
    }

    return scramble;
}

} // namespace rubiks
