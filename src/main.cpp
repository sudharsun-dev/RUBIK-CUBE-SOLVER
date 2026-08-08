#include "Cube.h"

#include <iostream>

int main() {
    rubiks::Cube cube;
    std::cout << "3D Rubik's Cube Solver foundation initialized.\n";
    std::cout << "Cube solved: " << (cube.isSolved() ? "yes" : "no") << '\n';
    return 0;
}
