#include "Cube.h"
#include "Move.h"

#include <cstdlib>
#include <iostream>
#include <vector>

using rubiks::Cube;
using rubiks::Face;
using rubiks::Move;
using rubiks::Turn;

namespace {

bool check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "[FAIL] " << message << '\n';
        return false;
    }
    return true;
}

std::vector<Move> allBaseMoves() {
    return {
        {Face::U, Turn::Clockwise},
        {Face::D, Turn::Clockwise},
        {Face::L, Turn::Clockwise},
        {Face::R, Turn::Clockwise},
        {Face::F, Turn::Clockwise},
        {Face::B, Turn::Clockwise},
    };
}

} // namespace

int main() {
    bool ok = true;

    {
        Cube cube;
        ok &= check(cube.isSolved(), "New cube should be solved");
    }

    for (const Move& move : allBaseMoves()) {
        Cube a;
        Cube original = a;

        a.applyMove(move);
        a.applyMove(move.inverse());
        ok &= check(a == original, "Move followed by inverse must restore state");

        Cube b;
        for (int i = 0; i < 4; ++i) {
            b.applyMove(move);
        }
        ok &= check(b.isSolved(), "Applying same quarter-turn 4 times must solve cube");
    }

    {
        Cube cube;
        cube.applyMove(Move{Face::R, Turn::Clockwise});
        cube.applyMove(Move{Face::U, Turn::CounterClockwise});
        ok &= check(cube.undo(), "Undo should succeed when history exists");
        ok &= check(cube.undo(), "Second undo should succeed");
        ok &= check(!cube.undo(), "Undo should fail with empty history");
        ok &= check(cube.isSolved(), "Undoing all moves should restore solved state");
    }

    {
        for (int i = 0; i < 100; ++i) {
            Cube cube;
            const auto scramble = rubiks::generateScramble(25);
            cube.applyMoves(scramble);
            cube.applyMoves(rubiks::inverseSequence(scramble));
            ok &= check(cube.isSolved(), "Scramble plus inverse scramble must solve cube");
            if (!ok) {
                break;
            }
        }
    }

    if (!ok) {
        return EXIT_FAILURE;
    }

    std::cout << "All cube engine tests passed.\n";
    return EXIT_SUCCESS;
}
