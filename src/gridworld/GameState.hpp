
#pragma once

#include "../common/State.hpp"
#include "../common/Vector2.hpp"
#include "CellState.hpp"
#include "Direction.hpp"
#include <memory>
#include <vector>

using namespace std;


class GameState : public State {
public:

  static uptr<GameState> NewInitialGameState(void);

  GameState(int width, int height, const vector<CellState> &cells, const Vector2 &playerPos);
  virtual ~GameState();

  int width(void) const;
  int height(void) const;

  bool movePlayer(Direction dir);
  CellState getPlayerPosCell(void) const;

  unique_ptr<State> clone(void) const override;
  bool operator== (const State& obj) const override;
  size_t hashCode() const override;
  void output(std::ostream &out) const override;

  vector<uptr<Action>> availableActions(void) const override;
  uptr<State> successorState(const Action &action) const override;

private:
  struct GameStateImpl;
  uptr<GameStateImpl> impl;
};
