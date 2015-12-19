
#pragma once

#include "../common/Common.hpp"
#include "../common/Rules.hpp"
#include "CellState.hpp"
#include "GameState.hpp"
#include <memory>

using namespace std;


class GameRules : public Rules {
public:
  
  GameRules(double exitReward, double deathReward, double tickReward);
  GameRules();

  virtual ~GameRules();

  bool isTerminalState(const State &state) const override;
  double getReward(const State &state) const override;

private:
  class GameRulesImpl;
  uptr<GameRulesImpl> impl;
};
