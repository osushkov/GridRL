
#include "GameState.hpp"
#include "GameAction.hpp"
#include <cassert>
#include <cstdlib>


uptr<GameState> GameState::NewInitialGameState(void) {
    unsigned width = 5;
    unsigned height = 5;

    vector<CellState> cells(width*height, CellState::EMPTY);
    cells[1 + 1*width] = CellState::PIT;
    cells[2 + 1*width] = CellState::WALL;

    cells[1 + 1*width] = CellState::PIT;
    cells[4 + 4*width] = CellState::EXIT;

    cells[0 + 1*width] = CellState::WALL;
    cells[1 + 3*width] = CellState::WALL;
    cells[2 + 1*width] = CellState::WALL;
    cells[3 + 3*width] = CellState::WALL;
    cells[4 + 3*width] = CellState::WALL;

    auto playerPos = Vector2(rand()%width, rand()%height);
    while(cells[playerPos.x + playerPos.y*width] != CellState::EMPTY) {
      playerPos = Vector2(rand()%width, rand()%height);
    }

    return make_unique<GameState>(width, height, cells, playerPos);
}


struct GameState::GameStateImpl {

  int worldWidth;
  int worldHeight;
  vector<CellState> cells;
  Vector2 playerPos;


  GameStateImpl(int width, int height, const vector<CellState> &cells,
      const Vector2 &playerPos) :
          worldWidth(width), worldHeight(height), cells(cells), playerPos(playerPos) {

    assert(width > 0);
    assert(height > 0);
    assert(cells.size() == static_cast<unsigned>(width*height));
    assert(playerPos.x >= 0 && playerPos.y >= 0);
    assert(playerPos.x < worldWidth && playerPos.y < worldHeight);
  }

  int width(void) const {
    return worldWidth;
  }

  int height(void) const {
    return worldHeight;
  }

  bool movePlayer(Direction dir) {
    assert(playerPos.x >= 0 && playerPos.y >= 0);
    assert(playerPos.x < worldWidth && playerPos.y < worldHeight);

    bool result = false;
    switch (dir) {
    case Direction::UP:
      result = tryChangePlayerPos(0, 1);
      break;
    case Direction::DOWN:
      result = tryChangePlayerPos(0, -1);
      break;
    case Direction::LEFT:
      result = tryChangePlayerPos(-1, 0);
      break;
    case Direction::RIGHT:
      result = tryChangePlayerPos(1, 0);
      break;
    }

    assert(playerPos.x >= 0 && playerPos.y >= 0);
    assert(playerPos.x < worldWidth && playerPos.y < worldHeight);

    return result;
  }

  CellState getPlayerPosCell(void) const {
    return cells[playerPos.x + playerPos.y*worldWidth];
  }

  bool operator== (const GameStateImpl& other) const {
    if (worldWidth != other.worldWidth
        || worldHeight != other.worldHeight
        || cells.size() != other.cells.size()
        || playerPos != other.playerPos) {
      return false;
    }

    for (unsigned i = 0; i < cells.size(); i++) {
      if (cells[i] != other.cells[i]) {
        return false;
      }
    }

    return true;
  }

  size_t hashCode(void) const {
    static const size_t MUL_CONST = 71;

    size_t result = 0;
    result = result * MUL_CONST + playerPos.x;
    result = result * MUL_CONST + playerPos.y;

    for (auto& c : cells) {
      result = result * MUL_CONST + (int) c;
    }
    return result;
  }

  void output(std::ostream &out) const {
    for (int y = 0; y < worldHeight; y++) {
      for (int x = 0; x < worldWidth; x++) {
        if (x == playerPos.x && y == playerPos.y) {
          out << "P";
        } else {
          out << cells[x + y*worldWidth];
        }
      }
      out << endl;
    }
  }

  std::vector<unique_ptr<Action>> availableActions(void) const {
    vector<unique_ptr<Action>> result;

    result.emplace_back(new GameAction(Direction::UP));
    result.emplace_back(new GameAction(Direction::DOWN));
    result.emplace_back(new GameAction(Direction::LEFT));
    result.emplace_back(new GameAction(Direction::RIGHT));

    return result;
  }

  unique_ptr<GameState> successorState(const Action &action) const {
    const GameAction& ga = dynamic_cast<const GameAction&>(action);

    auto result = unique_ptr<GameState>(new GameState(worldWidth, worldHeight, cells, playerPos));
    ga.apply(*result);

    return move(result);
  }

  bool tryChangePlayerPos(int xOffset, int yOffset) {
    Vector2 newPlayerPos{playerPos.x + xOffset, playerPos.y + yOffset};

    if (newPlayerPos.x >= 0 && newPlayerPos.x < worldWidth &&
        newPlayerPos.y >= 0 && newPlayerPos.y < worldHeight &&
        cells[newPlayerPos.x + newPlayerPos.y * worldWidth] != CellState::WALL) {
      playerPos = newPlayerPos;
      return true;
    } else {
      return false;
    }
  }

};


GameState::GameState(
    int width, int height, const vector<CellState> &cells, const Vector2 &playerPos) :
        impl(new GameStateImpl(width, height, cells, playerPos)) {}

GameState::~GameState() = default;

int GameState::width(void) const {
  return impl->width();
}

int GameState::height(void) const {
  return impl->height();
}

bool GameState::movePlayer(Direction dir) {
  return impl->movePlayer(dir);
}

CellState GameState::getPlayerPosCell(void) const {
  return impl->getPlayerPosCell();
}

unique_ptr<State> GameState::clone(void) const {
  return make_unique<GameState>(impl->worldWidth, impl->worldHeight, impl->cells, impl->playerPos);
}

bool GameState::operator== (const State& obj) const {
  const GameState *gs = dynamic_cast<const GameState*>(&obj);
  if (gs == nullptr) {
    return false;
  }

  return *impl == *gs->impl;
}

size_t GameState::hashCode(void) const {
  return impl->hashCode();
}

void GameState::output(std::ostream &out) const {
  impl->output(out);
}

std::vector<unique_ptr<Action>> GameState::availableActions(void) const {
  return impl->availableActions();
}

unique_ptr<State> GameState::successorState(const Action &action) const {
  return impl->successorState(action);
}
