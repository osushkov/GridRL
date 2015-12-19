
#include "GameRules.hpp"
#include <cassert>


struct GameRules::GameRulesImpl {
  double exitReward;
  double deathReward;
  double tickReward;

  GameRulesImpl(double exitReward, double deathReward, double tickReward) :
      exitReward(exitReward), deathReward(deathReward), tickReward(tickReward) {}

  bool isTerminalState(const GameState &state) const {
    CellState cell = state.getPlayerPosCell();
    return cell == CellState::EXIT || cell == CellState::PIT;
  }

  double getReward(const GameState &state) const {
    CellState cell = state.getPlayerPosCell();
    if (cell == CellState::EXIT) {
      return exitReward;
    } else if (cell == CellState::PIT) {
      return deathReward;
    } else {
      return tickReward;
    }
  }

};

GameRules::GameRules(double exitReward, double deathReward, double tickReward) :
    impl(new GameRulesImpl(exitReward, deathReward, tickReward)) {}

GameRules::GameRules() : GameRules(0.0, 0.0, 0.0) {}

GameRules::~GameRules() = default;

bool GameRules::isTerminalState(const State &state) const {
  auto gs = static_cast<const GameState*>(&state);
  return impl->isTerminalState(*gs);
}

double GameRules::getReward(const State &state) const {
  auto gs = static_cast<const GameState*>(&state);
  return impl->getReward(*gs);
}
