
#pragma once
#include <ostream>

enum class CellState {
  EMPTY = 0,
  WALL = 1,
  EXIT = 2,
  PIT = 3
};

inline std::ostream& operator<<(std::ostream& stream, const CellState& cs) {
  switch (cs) {
  case CellState::EMPTY:
    stream << ".";
    break;
  case CellState::WALL:
    stream << "#";
    break;
  case CellState::EXIT:
    stream << "X";
    break;
  case CellState::PIT:
    stream << "O";
    break;
  }
  return stream;
}
