
#pragma once

struct Vector2 {
    int x, y;

    Vector2() : x(0), y(0) {}
    Vector2(int x, int y) : x(x), y(y) {}

    bool operator==(const Vector2 &other) const {
      return x == other.x && y == other.y;
    }

    bool operator!=(const Vector2 &other) const {
      return !(*this == other);
    }
};
