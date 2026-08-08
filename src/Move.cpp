#include "Move.h"

#include <stdexcept>

namespace rubiks {

Move Move::inverse() const {
    if (turn == Turn::Double) {
        return *this;
    }

    return Move{
        face,
        turn == Turn::Clockwise ? Turn::CounterClockwise : Turn::Clockwise,
    };
}

std::string Move::toString() const {
    char faceChar = '?';
    switch (face) {
    case Face::U:
        faceChar = 'U';
        break;
    case Face::D:
        faceChar = 'D';
        break;
    case Face::L:
        faceChar = 'L';
        break;
    case Face::R:
        faceChar = 'R';
        break;
    case Face::F:
        faceChar = 'F';
        break;
    case Face::B:
        faceChar = 'B';
        break;
    }

    std::string value(1, faceChar);
    if (turn == Turn::CounterClockwise) {
        value.push_back('\'');
    } else if (turn == Turn::Double) {
        value.push_back('2');
    }
    return value;
}

Move Move::fromString(const std::string& notation) {
    if (notation.empty() || notation.size() > 2) {
        throw std::invalid_argument("Invalid move notation: " + notation);
    }

    Face parsedFace;
    switch (notation[0]) {
    case 'U':
        parsedFace = Face::U;
        break;
    case 'D':
        parsedFace = Face::D;
        break;
    case 'L':
        parsedFace = Face::L;
        break;
    case 'R':
        parsedFace = Face::R;
        break;
    case 'F':
        parsedFace = Face::F;
        break;
    case 'B':
        parsedFace = Face::B;
        break;
    default:
        throw std::invalid_argument("Invalid face in move notation: " + notation);
    }

    Turn parsedTurn = Turn::Clockwise;
    if (notation.size() == 2) {
        if (notation[1] == '\'') {
            parsedTurn = Turn::CounterClockwise;
        } else if (notation[1] == '2') {
            parsedTurn = Turn::Double;
        } else {
            throw std::invalid_argument("Invalid turn in move notation: " + notation);
        }
    }

    return Move{parsedFace, parsedTurn};
}

std::vector<Move> inverseSequence(const std::vector<Move>& moves) {
    std::vector<Move> inverse;
    inverse.reserve(moves.size());

    for (auto it = moves.rbegin(); it != moves.rend(); ++it) {
        inverse.push_back(it->inverse());
    }

    return inverse;
}

} // namespace rubiks
