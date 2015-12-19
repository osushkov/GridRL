
#pragma once
#include <ostream>

enum class Direction {
  UP = 0, DOWN = 1, LEFT = 2, RIGHT = 3
};

inline std::ostream& operator<<(std::ostream& stream, const Direction& dir) {
  switch (dir) {
  case Direction::UP:
    stream << "up";
    break;
  case Direction::DOWN:
    stream << "down";
    break;
  case Direction::LEFT:
    stream << "left";
    break;
  case Direction::RIGHT:
    stream << "right";
    break;
  }
  return stream;
}
